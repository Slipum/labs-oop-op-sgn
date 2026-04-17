#include "logic_graph.h"

#include <cstdlib>

void getLimits(AppContext* context, int colum, double* xMin, double* xMax, double* yMin, double* yMax, bool* allPositiveY) {
    for (int i = 0; i < context->rows; i++) {
        if (!context->outputMetrics[i]) continue;

        Row* row = context->outputMetrics[i];

        double dataX = atof(row->year);
        double dataY = atof(getFieldByColumn(row, colum, context));

        *xMin = (*xMin < dataX) ? *xMin : dataX;
        *yMin = (*yMin < dataY) ? *yMin : dataY;
        *xMax = (*xMax > dataX) ? *xMax : dataX;
        *yMax = (*yMax > dataY) ? *yMax : dataY;

        if (dataY < 0) *allPositiveY = false;
    }
}
