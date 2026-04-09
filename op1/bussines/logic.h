#ifndef LOGIC_H
#define LOGIC_H

#include "../entrypoint/app_context.h"

enum Systems {
    BINARY = 2,
    OCTAL = 8,
    DECIMAL = 10,
};

char* whichError(int* error, long long n);
char* toPositive(AppContext* context, long long n);
char* toNegative(AppContext* context, long long n);
char* fromNegative(AppContext* context);

void validConvert(AppContext* context);
int correctChar(char a, int system);
int isCorrect(AppContext* context);

long long toDec(int system, const char* str, int outputSystem);
char* reverseStr(char* originStr, int len);
char* convert(AppContext* context);

#define INIT_STR 40
#define MAX_UINT32 4294967295LL
#define INIT_BINARY_STR 32

#endif // LOGIC_H
