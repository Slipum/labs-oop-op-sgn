#include "logic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int correctChar(char a, int system) {
    const char *str;
    switch (system) {
        case BINARY:
            str = "01";
            break;
        case OCTAL:
            str = "01234567";
            break;
        case DECIMAL:
            str = "0123456789";
            break;
    }
    for (int i = 0; i < system; i++) if (a == str[i]) return 1;
    return 0;
}

long long toDec(int system, const char* str, int outputSystem) {
    int len = strlen(str);
    switch (system) {
        case BINARY:
            if (*str != '-' && len > 32) return INVALID_ERROR;
            break;
        case OCTAL:
            if (*str != '-' && len > 11) return OUTRANGE_ERROR;
            break;
        case DECIMAL:
            if (*str == '-' && len > 12) return OUTRANGE_ERROR;
            else if (len > 10) return OUTRANGE_ERROR;
            break;
    }
    long long n = 0;
    int i = *str == '-' ? 1 : 0;
    if (*str == '-' && len == 1) return INVALID_ERROR;
    for (; i < len; i++) {
        if (!correctChar(str[i], system)) return INVALID_ERROR;
        n = n * system + (str[i] - '0');
        if (n > MAX_UINT32) return OUTRANGE_ERROR;
    }
    if (*str == '-' && outputSystem != DECIMAL) n--;
    return n;
}

char* reverseStr(char* originStr, int len) {
    char* result = (char*)malloc(len + 1);
    for (int i = 0; i < len; i++) {
        result[i] = originStr[len - i - 1];
    }
    result[len] = '\0';
    return result;
}

int isCorrect(AppContext* context) {
    if (*(context->input) == '0') {
        return 1;
    }
    switch (context->inputSys) {
    case BINARY:
        if (strlen(context->input) == 32) return 0;
        break;
    case OCTAL:
        if (strlen(context->input) == 11) return 0;
        break;
    }
    return 1;
}

char* fromNegative(AppContext* context) {
    char* binary = context->input;
    if (context->inputSys == BINARY) {
        for (size_t i = 0;i < strlen(context->input); i++) {
            if (binary[i] == '1') binary[i] = '0';
            else binary[i] = '1';
        }
        return binary;
    } else {
        AppContext temp = {8,2,binary,0};
        binary = convert(&temp);
        AppContext temp2 = {2,10,binary,0};
        return fromNegative(&temp2);
    }
}

char* toNegative(AppContext* context, long long n) {
    char* result;
    char str[INIT_STR];
    int i = 0;
    while (n > 0) {
        str[i++] = (n % BINARY) + '0';
        n /= BINARY;
    }
    result = str;

    char binary[] = "11111111111111111111111111111111";
    for (size_t i = 0; i < strlen(result); i++) {
        if (result[i] == '1') binary[i] = '0';
    }
    char* tmp2 = reverseStr(binary, INIT_BINARY_STR);
    result = tmp2;
    if (context->outputSys == OCTAL) {
        AppContext temp = {2,8,result,0};
        context->error = 0;
        return convert(&temp);
    }
    return result;
}

char* toPositive(AppContext* context, long long n) {
    if (*(context->input) == '-' && context->inputSys != DECIMAL) {
        context->error = INVALID_ERROR;
        return NULL;
    }
    if (context->error == NEGATIVE) {
        n++;
    }
    if (n==0) {
        char* res = (char*)malloc(sizeof(char) * 2);
        res[0] = '0';
        res[1] = '\0';
        context->error = 0;
        return res;
    }
    char str[INIT_STR];
    int i = 0;
    while (n > 0) {
        str[i++] = (n % context->outputSys) + '0';
        n /= context->outputSys;
    }

    if ((context->outputSys == DECIMAL && *(context->input) == '-')) {str[i++] = '-';}
    if (context->error == NEGATIVE) {
        context->error = 0;
        str[i++] = '-';
    }
    return reverseStr(str, i);
}

void validConvert(AppContext* context) {
    if (context->outputSys == DECIMAL && !isCorrect(context)) {
        printf("%s\n", context->input);
        context->input = fromNegative(context);
        context->inputSys = BINARY;
        printf("%s\n", context->input);
        context->error = NEGATIVE;
    }
    if (*(context->input) == '+') if (strlen(context->input) > 1) *(context->input) = '0';
}

char* whichError(int* error, long long n) {
    switch (n) {
    case INVALID_ERROR:
        *error = INVALID_ERROR;
        break;
    case OUTRANGE_ERROR:
        *error = OUTRANGE_ERROR;
        break;
    default:
        break;
    }
    return NULL;
}

char* convert(AppContext* context) {
    validConvert(context);
    long long n = toDec(context->inputSys, context->input, context->outputSys);
    if (n < 0) return whichError(&context->error, n);

    char* result;
    if (*(context->input) == '-' && context->outputSys != DECIMAL) {
        result = toNegative(context, n);
    } else {
        result = toPositive(context, n);
    }

    context->error = 0;
    return result;
}
