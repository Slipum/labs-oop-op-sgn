#ifndef OP2_APPCONTEXT_H
#define OP2_APPCONTEXT_H

#define COLS_COUNT 7

enum Errors {
    INVALID_PATH = -1,
    INVALID_COLUMN = -2,
    INVALID_FILE = -3,
    INVALID_REGION = -4,
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

struct AppContext {
    char* filePath = nullptr;
    int colum;
    float* metrics = nullptr;

    char* region = nullptr;
    char** regions = nullptr;
    int uniqueRegionCount = 0;

    Row** outputMetrics = nullptr;
    int rows;
    int realRows;
    int error = 0;
};

#endif //OP2_APPCONTEXT_H
