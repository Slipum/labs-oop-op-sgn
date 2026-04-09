#ifndef OP2_LOGIC_H
#define OP2_LOGIC_H

#include <cstdio>

#include "../entrypoint/appcontext.h"

#define BUFFER_SIZE 256
#define COLS_SIZE 64

int countOfCols(char* buffer);

int validChar(char a, int type);
int validLine(Row* str);

void freeRow(Row* row);
void freeTable(Row** table, int rows);

Row* getLine(char* buffer);
Row** getTable(FILE* f, AppContext* context);

int getRows(FILE* f);
const char* getFieldByColumn(Row* row, int column, AppContext* context);

Row** createTable(AppContext* context);
void filterTable(AppContext* context, Row** table);

char** getUniqueStrings(Row** strings, AppContext* context);
void getMetrics(AppContext* context);
void getMediana(AppContext* context);

void quickSort(Row** table, int rows, int colum, AppContext* context);
void getValSort(Row** table, int low, int high, int colum, AppContext* context);
int iter(Row** table, int low, int high, int colum, AppContext* context);
int compareRows(Row* a, Row* b, int colum, AppContext* context);

#endif //OP2_LOGIC_H
