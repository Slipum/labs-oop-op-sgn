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

    for (int i = 0; str->year[i] != '\0'; i++)
        if (validChar(str->year[i], YEAR)) return 1;

    if (str->region[0] == ' ') return 1;

    for (int i = 0; str->population[i] != '\0'; i++)
        if (validChar(str->population[i], POPULATION)) return 1;

    for (int i = 0; str->birth_rate[i] != '\0'; i++)
        if (validChar(str->birth_rate[i], BIRTH_RATE)) return 1;

    for (int i = 0; str->death_rate[i] != '\0'; i++)
        if (validChar(str->death_rate[i], DEATH_RATE)) return 1;

    for (int i = 0; str->demographic[i] != '\0'; i++)
        if (validChar(str->demographic[i], DEMOGRAPHIC)) return 1;

    for (int i = 0; str->urbanization[i] != '\0'; i++)
        if (validChar(str->urbanization[i], URBANIZATION)) return 1;

    return 0;
}


void freeRow(Row* row) {
    if (row  == nullptr) return;
    if (row->year != nullptr) {
        free(row->year);
        row->year = nullptr;
    }
    if (row->region != nullptr) {
        free(row->region);
        row->region = nullptr;
    }
    if (row->population != nullptr) {
        free(row->population);
        row->population = nullptr;
    }
    if (row->birth_rate != nullptr) {
        free(row->birth_rate);
        row->birth_rate = nullptr;
    }
    if (row->death_rate != nullptr) {
        free(row->death_rate);
        row->death_rate = nullptr;
    }
    if (row->demographic != nullptr) {
        free(row->demographic);
        row->demographic = nullptr;
    }
    if (row->urbanization != nullptr) {
        free(row->urbanization);
        row->urbanization = nullptr;
    }
    free(row);
}

void freeTable(Row** table, int rows) {
    if (!table) return;
    for (int i = 0; i < rows; i++) {
        freeRow(table[i]);
        table[i] = nullptr;
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
    if (context->rows == 0) return nullptr;
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

void filterTable(AppContext* context, Row** table, char* region) {
    if (!context || !table || !region) return;
    if (strlen(region) == 0) return;

    int i = 0;
    for (int rows = 0; rows < context->rows; ++rows) {
        Row* row = table[rows];
        if (!row || !row->region) continue;
        if (strcmp(row->region, region) == 0) {
            if (i != rows) {
                table[i] = table[rows];
                table[rows] = nullptr;
            }
            i++;
        }
    }
    context->rows = i;
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

void getMetrics(AppContext* context, int colum) {
    if (!context || !context->outputMetrics || context->error) return;
    if (context->metrics) {
        free(context->metrics);
        context->metrics = nullptr;
    }
    context->metrics = (float*)calloc(MEDIANA+1, sizeof(float));

    quickSort(context->outputMetrics, context->rows, colum, context);
    if (context->rows == 0) {
        context->error = INVALID_FILE;
        return;
    }
    int mid = context->rows / 2;
    if (context->rows % 2 == 1) {
        context->metrics[MEDIANA] = atof(getFieldByColumn(context->outputMetrics[mid], colum, context));
    } else {
        float val1 = atof(getFieldByColumn(context->outputMetrics[mid-1], colum, context));
        float val2 = atof(getFieldByColumn(context->outputMetrics[mid], colum, context));
        context->metrics[MEDIANA] = (val1 + val2) / 2.0f;
    }
    context->metrics[MINIMUM] = atof(getFieldByColumn(context->outputMetrics[0], colum, context));
    context->metrics[MAXIMUM] = atof(getFieldByColumn(context->outputMetrics[context->rows-1], colum, context));
}

char** getUniqueStrings(Row** strings, AppContext* context) {
    if (context->uniqueRegionCount != 0) {
        for (int i = 0; i < context->uniqueRegionCount; i++) {
            free(context->regions[i]);
            context->regions[i] = nullptr;
        }
        free(context->regions);
        context->regions = nullptr;
        context->uniqueRegionCount = 0;
    }
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

Row** createTable(AppContext* context, char* filePath, char* region) {
    FILE *f = fopen(filePath, "r");

    if (f == nullptr) return nullptr;
    if (context->outputMetrics != nullptr) freeTable(context->outputMetrics, context->realRows);

    int realRows = getRows(f);
    context->rows = realRows;
    context->realRows = realRows;
    rewind(f);
    Row** table = getTable(f, context);
    context->regions = getUniqueStrings(table, context);

    if (region) filterTable(context, table, region);

    if (context->realRows == 0) context->error = INVALID_FILE;

    fclose(f);
    return table;
}