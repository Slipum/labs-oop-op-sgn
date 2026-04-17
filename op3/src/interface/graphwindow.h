#ifndef OP3_GRAPHWINDOW_H
#define OP3_GRAPHWINDOW_H

#include <QWidget>
#include "../entrypoint/appcontext.h"
#include "../bussines/logic_graph.h"

#define LEFT_MARGIN 50
#define RIGHT_MARGIN 50

#define POSITIVE_MARGIN 80
#define NEGATIVE_MARGIN 60

class GraphWindow: public QWidget {
    Q_OBJECT
    AppContext *context;
    AppParams *app;

public:
    GraphWindow(AppContext *context, AppParams *app, QWidget *parent = nullptr);
    ~GraphWindow() = default;

protected:
    void paintEvent(QPaintEvent *event) override;
private:
    void createGraph(QPainter* painter, int plotX0, int plotY0, double xMin, double yMin, double scaleX, double scaleY, int plotHeight);
    void getFont(QPainter* painter);
    char* getColumnName(Row* row, int column);
    void addingPadding(double* yMin, double* yMax);

    void infoY(QPainter* painter, int plotX0, int plotY0, double yMin, double yMax, double scaleY, int plotHeight);
    void infoX(QPainter* painter, int plotX0, int oxY_screen, double xMin, double xMax, double scaleX);

    int createOX(QPainter* painter, int plotX0, int plotY0, double plotHeight, double plotWidth, double scaleY, double yMin, bool allPositiveY);
    void createOY(QPainter* painter, int plotX0, int plotY0, double xMin, double scaleX, int plotHeight);
};

#endif //OP3_GRAPHWINDOW_H
