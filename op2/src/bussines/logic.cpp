#include "logic.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <qstringalgorithms.h>

int countOfCols(char* buffer) {
    int result = 0;
    for (int k = 0; buffer[k]; ++k) if (buffer[k] == ',') result++;
    return result;
}

int validChar(char a, int type) {
    const char *str;
    switch (type) {
    case YEAR:
        str = "0123456789";
        break;
    case REGION:
        return 0;
    default:
        str = "0123456789.+-";
        break;
    }
    for (int i = 0; str[i]; i++) if (str[i] == a) return 0;
    return 1;
}

int validLine(Row* str) {
    if (!str->year || !str->region || !str->population || !str->birth_rate
        || !str->death_rate || !str->demographic || !str->urbanization) return 1;
    if (str->year) for (int i = 0; i < str->year[i]; i++) if (validChar(str->year[i], YEAR)) return 1;
    if (str->region) if (str->region[0] == ' ') return 1;
    if (str->population) for (int i = 0; i < str->population[i]; i++) if (validChar(str->population[i], POPULATION)) return 1;
    if (str->birth_rate) for (int i = 0; i < str->birth_rate[i]; i++) if (validChar(str->birth_rate[i], BIRTH_RATE)) return 1;
    if (str->death_rate) for (int i = 0; i < str->death_rate[i]; i++) if (validChar(str->death_rate[i], DEATH_RATE)) return 1;
    if (str->demographic) for (int i = 0; i < str->demographic[i]; i++) if (validChar(str->demographic[i], DEMOGRAPHIC)) return 1;
    if (str->urbanization) for (int i = 0; i < str->urbanization[i]; i++) if (validChar(str->urbanization[i], URBANIZATION)) return 1;
    return 0;
}

void freeRow(Row* row) {
    if (!row) return;
    if (row->year) free(row->year);
    if (row->region) free(row->region);
    if (row->population) free(row->population);
    if (row->birth_rate) free(row->birth_rate);
    if (row->death_rate) free(row->death_rate);
    if (row->demographic) free(row->demographic);
    if (row->urbanization) free(row->urbanization);
    free(row);
    row = nullptr;
}

void freeTable(Row** table, int rows) {
    if (!table) return;
    for (int i = 0; i < rows; i++) {
        freeRow(table[i]);
    }
    free(table);
    table = nullptr;
}

Row* getLine(char* buffer) {
    int cols = countOfCols(buffer);
    if (cols != COLS_COUNT - 1) return nullptr;

    Row* line = (Row*)malloc(sizeof(Row));
    if (!line) return nullptr;

    char buffer_copy[BUFFER_SIZE];
    strncpy(buffer_copy, buffer, BUFFER_SIZE - 1);
    buffer_copy[BUFFER_SIZE - 1] = '\0';

    char* str = strtok(buffer_copy, ",");
    int col = 0;
    while (str && col < COLS_COUNT) {
        str[strcspn(str, "\n")] = 0;
        switch (col) {
        case YEAR: line->year = strdup(str); break;
        case REGION: line->region = strdup(str); break;
        case POPULATION: line->population = strdup(str); break;
        case BIRTH_RATE: line->birth_rate = strdup(str); break;
        case DEATH_RATE: line->death_rate = strdup(str); break;
        case DEMOGRAPHIC: line->demographic = strdup(str); break;
        case URBANIZATION: line->urbanization = strdup(str); break;
        }
        str = strtok(nullptr, ",");
        col++;
    }
    if (col != COLS_COUNT || validLine(line)) {
        freeRow(line);
        return nullptr;
    }
    return line;
}

Row** getTable(FILE* f, AppContext* context) {
    Row** table = (Row**)calloc(context->rows, sizeof(Row*));
    if (!table) return nullptr;

    int valid_rows = 0;
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), f) && valid_rows < context->rows) {
        Row* line = getLine(buffer);
        if (line == nullptr) continue;

        table[valid_rows++] = line;
    }

    context->rows = valid_rows;
    return table;
}

int getRows(FILE* f) {
    int rows = 0;
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), f)) rows++;
    return rows;
}

void filterTable(AppContext* context, Row** table) {
    if (!context || !table || !context->region) return;
    if (strlen(context->region) == 0) return;

    int i = 0;
    for (int rows = 0; rows < context->rows; ++rows) {
        Row* row = table[rows];
        if (!row || !row->region) continue;
        if (strcmp(row->region, context->region) == 0) {
            if (i != rows) {
                table[i] = table[rows];
                table[rows] = nullptr;
            }
            i++;
        }
    }
    context->rows = i;
}

void getMetrics(AppContext* context) {
    if (!context || context->rows == 0 || !context->outputMetrics) return;

    if (context->metrics) {
        free(context->metrics);
        context->metrics = nullptr;
    }
    context->metrics = (float*)calloc(MEDIANA+1, sizeof(float));
    float min_val = INT16_MAX, max_val = INT16_MIN;
    for (int i = 0; i < context->rows; i++) {
        const char* row = getFieldByColumn(context->outputMetrics[i], context->colum, context);
        if (context->outputMetrics[i] && row) {
            float val = atof(row);
            if (val < min_val) min_val = val;
            if (val > max_val) max_val = val;
        }
    }

    context->metrics[MINIMUM] = min_val;
    context->metrics[MAXIMUM] = max_val;
}

const char* getFieldByColumn(Row* row, int column, AppContext* context) {
    switch (column) {
    case YEAR: return row->year;
    case REGION: return row->region;
    case POPULATION: return row->population;
    case BIRTH_RATE: return row->birth_rate;
    case DEATH_RATE: return row->death_rate;
    case DEMOGRAPHIC: return row->demographic;
    case URBANIZATION: return row->urbanization;
    default: {
        context->error = INVALID_COLUMN;
        return nullptr;
    }
    }
}

int compareRows(Row* a, Row* b, int colum, AppContext* context) {
    const char* valA = getFieldByColumn(a, colum, context);
    const char* valB = getFieldByColumn(b, colum, context);
    if (!valA && !valB) return 0;
    if (!valA) return -1;
    if (!valB) return 1;

    float numA = atof(valA);
    float numB = atof(valB);
    if (numA < numB) return -1;
    if (numA > numB) return 1;
    return 0;
}

int iter(Row** table, int low, int high, int colum, AppContext* context) {
    if (low >= high) return low;

    const char* pivotStr = getFieldByColumn(table[high], colum, context);
    float pivotVal = pivotStr ? atof(pivotStr) : 0.0f;

    int i = low - 1;

    for (int j = low; j < high; j++) {
        const char* columStr = getFieldByColumn(table[j], colum, context);
        float currVal = columStr ? atof(columStr) : 0.0f;

        if (currVal <= pivotVal) {
            i++;
            std::swap(table[i], table[j]);
        }
    }

    std::swap(table[i + 1], table[high]);

    return i + 1;
}

void getValSort(Row** table, int low, int high, int colum, AppContext* context) {
    if (low < high) {
        int ptri = iter(table, low, high, colum, context);
        getValSort(table, low, ptri - 1, colum, context);
        getValSort(table, ptri + 1, high, colum, context);
    }
}

void quickSort(Row** table, int rows, int colum, AppContext* context) {
    getValSort(table, 0, rows - 1, colum, context);
}

void getMediana(AppContext* context) {
    if (!context || !context->outputMetrics || context->error) return;

    quickSort(context->outputMetrics, context->rows, context->colum, context);

    int mid = context->rows / 2;
    if (context->rows % 2 == 1) {
        context->metrics[MEDIANA] = atof(getFieldByColumn(context->outputMetrics[mid], context->colum, context));
    } else {
        float val1 = atof(getFieldByColumn(context->outputMetrics[mid-1], context->colum, context));
        float val2 = atof(getFieldByColumn(context->outputMetrics[mid], context->colum, context));
        context->metrics[MEDIANA] = (val1 + val2) / 2.0f;
    }
}

char** getUniqueStrings(Row** strings, AppContext* context) {
    char** unique = (char**)malloc(sizeof(char*) * context->realRows);

    for (int i = 0; i < context->realRows; i++) {
        if (!strings[i]) continue;

        int isUnique = 1;

        for (int j = 0; j < context->uniqueRegionCount; j++) {
            if (strcmp(strings[i]->region, unique[j]) == 0) {
                isUnique = 0;
                break;
            }
        }

        if (isUnique) {
            unique[context->uniqueRegionCount] = strdup(strings[i]->region);
            context->uniqueRegionCount++;
        }
    }

    unique = (char**)realloc(unique, sizeof(char*) * context->uniqueRegionCount);
    if (!unique) {
        free(unique);
        context->uniqueRegionCount = 0;
        return nullptr;
    }
    return unique;
}

Row** createTable(AppContext* context) {
    FILE *f = fopen(context->filePath, "r");

    if (f == nullptr) return nullptr;
    if (context->outputMetrics != nullptr) freeTable(context->outputMetrics, context->realRows);

    int realRows = getRows(f);
    context->rows = realRows;
    context->realRows = realRows;
    rewind(f);
    Row** table = getTable(f, context);
    if (context->regions == nullptr) context->regions = getUniqueStrings(table, context);

    if (context->region) filterTable(context, table);

    if (context->realRows == 0) context->error = INVALID_FILE;

    fclose(f);
    return table;
}