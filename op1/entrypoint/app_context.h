#ifndef APP_CONTEXT_H
#define APP_CONTEXT_H

#define INVALID_INPUT "Введено неверное значение"
#define OUTRANGE_INPUT "Введеное значение выходит за 4 байта"
#define ERROR_INPUT "Ошибка!"

enum ERROR {
    OUTRANGE_ERROR = -1,
    INVALID_ERROR = -2,
    NEGATIVE = -3,
    CONTINUE = -4,
};

struct AppContext {
    int inputSys;
    int outputSys;
    char* input;
    int error = 0;
};

#endif //APP_CONTEXT_H
