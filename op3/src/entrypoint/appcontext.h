#ifndef OP2_APPCONTEXT_H
#define OP2_APPCONTEXT_H

#define COLS_COUNT 7

enum Errors {
    INVALID_PATH = -1,
    INVALID_COLUMN = -2,
    INVALID_FILE = -3,
    INVALID_REGION = -4,
    INVALID_GRAPH = -5,
    INVALID_CLOSE = -6,
};

enum Metrics {
    MINIMUM = 0,
    MAXIMUM,
    MEDIANA,
};

enum Colums {
    YEAR = 0,
    REGION,
    POPULATION,
    BIRTH_RATE,
    DEATH_RATE,
    DEMOGRAPHIC,
    URBANIZATION,
};

struct Row {
    char* year = nullptr;
    char* region = nullptr;
    char* population = nullptr;
    char* birth_rate = nullptr;
    char* death_rate = nullptr;
    char* demographic = nullptr;
    char* urbanization = nullptr;
};

typedef struct {
    char* filePath = nullptr;
    char* region = nullptr;
    int colum;
} AppParams;

typedef struct {
    float* metrics = nullptr;
    char** regions = nullptr;
    int uniqueRegionCount = 0;

    Row** outputMetrics = nullptr;
    int rows;
    int realRows;
    int error = 0;
} AppContext;

#endif //OP2_APPCONTEXT_H
