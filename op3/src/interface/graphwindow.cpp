#include "graphwindow.h"

#include <QPainter>

GraphWindow::GraphWindow(AppContext *context, AppParams* app, QWidget *parent) : context(context), app(app), QWidget(parent) {
    resize(1000, 800);
    setWindowTitle("Graph Window");

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::white);

    setPalette(palette);
    setAutoFillBackground(true);
}

void GraphWindow::paintEvent(QPaintEvent* event) {
    QPainter* painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing); // добавил для сглаживания

    // Границы по X и Y
    double xMin = std::numeric_limits<double>::max(), xMax = std::numeric_limits<double>::lowest();
    double yMin = std::numeric_limits<double>::max(), yMax = std::numeric_limits<double>::lowest();
    bool allPositiveY = true;
    getLimits(context, app->colum, &xMin, &xMax, &yMin, &yMax, &allPositiveY);
    if (xMin == std::numeric_limits<double>::max()
        || yMin == std::numeric_limits<double>::max())
        return;
    addingPadding(&yMin, &yMax);

    int bottomMargin = allPositiveY ? POSITIVE_MARGIN : NEGATIVE_MARGIN;
    int plotX0 = LEFT_MARGIN, plotY0 = RIGHT_MARGIN;
    int plotWidth = width() - LEFT_MARGIN - RIGHT_MARGIN;
    int plotHeight = height() - bottomMargin - RIGHT_MARGIN;

    double scaleX = (xMax > xMin) ? static_cast<double>(plotWidth) / (xMax - xMin) : 1.0;
    double scaleY = (yMax > yMin) ? static_cast<double>(plotHeight) / (yMax - yMin) : 1.0;

    int oxY_screen = createOX(painter, plotX0, plotY0, plotHeight, plotWidth, scaleY, yMin, allPositiveY);
    createOY(painter, plotX0, plotY0, xMin, scaleX, plotHeight);

    getFont(painter);
    infoX(painter, plotX0, oxY_screen, xMin, xMax, scaleX);
    infoY(painter, plotX0, plotY0, yMin, yMax, scaleY, plotHeight);

    createGraph(painter, plotX0, plotY0, xMin, yMin, scaleX, scaleY, plotHeight);
    painter->end();
}

void GraphWindow::addingPadding(double* yMin, double* yMax) {
    double range = *yMax - *yMin;
    double yPadding = range * 0.1;
    if (yPadding == 0) yPadding = 1.0;

    if (*yMin >= 0) {
        double extraPadding = *yMax * 0.05;
        *yMin -= extraPadding;
        *yMax += yPadding;
    } else if (*yMax <= 0) {
        double extraPadding = (-*yMin) * 0.05;
        *yMax = 0.0 + extraPadding;
        *yMin -= yPadding;
    } else {
        *yMin -= yPadding;
        *yMax += yPadding;
    }
}

void GraphWindow::createOY(QPainter* painter, int plotX0, int plotY0, double xMin, double scaleX, int plotHeight) {
    double zeroX_screen = plotX0 + (0.0 - xMin) * scaleX;
    painter->drawLine(static_cast<int>(zeroX_screen), plotY0,
                     static_cast<int>(zeroX_screen), plotY0 + plotHeight);
}

int GraphWindow::createOX(QPainter* painter, int plotX0, int plotY0, double plotHeight, double plotWidth, double scaleY, double yMin, bool allPositiveY) {
    int oxY_screen;
    if (allPositiveY && yMin >= 0) {
        oxY_screen = plotY0 + plotHeight + 5;
    } else {
        oxY_screen = plotY0 + plotHeight - (0.0 - yMin) * scaleY;
    }
    painter->setPen(QPen(Qt::black, 2));
    painter->drawLine(plotX0, oxY_screen, plotX0 + plotWidth, oxY_screen);
    return oxY_screen;
}

void GraphWindow::getFont(QPainter* painter) {
    QFont font = painter->font();
    font.setPixelSize(10);
    painter->setFont(font);
    painter->setPen(Qt::darkGray);
};

void GraphWindow::infoX(QPainter* painter, int plotX0, int oxY_screen, double xMin, double xMax, double scaleX) {
    int numTicksX = 10;
    for (int i = 0; i <= numTicksX; ++i) {
        double dataX = xMin + (xMax - xMin) * i / numTicksX;
        float screenX = plotX0 + (dataX - xMin) * scaleX;
        int screenY = oxY_screen + 18;

        QString label = QString::number(static_cast<int>(std::round(dataX)));
        painter->drawText(static_cast<int>(screenX) - 25, screenY, 50, 20, Qt::AlignCenter, label);
        painter->drawLine(static_cast<int>(screenX), oxY_screen - 5, static_cast<int>(screenX), oxY_screen);
    }
}

void GraphWindow::infoY(QPainter* painter, int plotX0, int plotY0, double yMin, double yMax, double scaleY, int plotHeight) {
    int numTicksY = 11;
    for (int i = 0; i <= numTicksY; ++i) {
        double dataY = yMin + (yMax - yMin) * i / numTicksY;
        float screenY = plotY0 + plotHeight - (dataY - yMin) * scaleY;

        int labelX = plotX0 - 45;
        QString label = QString::number(dataY, 'f', 1);
        painter->drawText(labelX, static_cast<int>(screenY) - 10, 40, 20,
                         Qt::AlignRight | Qt::AlignVCenter, label);
        painter->drawLine(plotX0, static_cast<int>(screenY), plotX0 + 5, static_cast<int>(screenY));
    }
}

void GraphWindow::createGraph(QPainter* painter, int plotX0, int plotY0, double xMin, double yMin, double scaleX, double scaleY, int plotHeight) {
    painter->setPen(QPen(Qt::red, 3));
    QVector<QPointF> points;

    for (int i = 0; i < context->rows; i++) {
        if (!context->outputMetrics[i]) continue;

        Row* row = context->outputMetrics[i];

        double dataX = QString::fromUtf8(row->year).toDouble();   // год
        double dataY = QString::fromUtf8(getColumnName(row, app->colum)).toDouble();

        float screenX = plotX0 + (dataX - xMin) * scaleX;
        float screenY = plotY0 + plotHeight - (dataY - yMin) * scaleY;

        points.append(QPointF(screenX, screenY));
    }

    if (points.size() > 1) {
        painter->drawPolyline(points);
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::blue);
        for (const QPointF& p : points) {
            painter->drawEllipse(p, 4, 4);
        }
    }
}

char* GraphWindow::getColumnName(Row* row, int column) {
    switch (column) {
    case YEAR: return row->year;
    case REGION: return row->region;
    case POPULATION: return row->population;
    case BIRTH_RATE: return row->birth_rate;
    case DEATH_RATE: return row->death_rate;
    case DEMOGRAPHIC: return row->demographic;
    case URBANIZATION: return row->urbanization;
    default: return nullptr;
    }
}