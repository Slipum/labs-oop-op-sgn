#ifndef OOP4_QTSCENE_H
#define OOP4_QTSCENE_H
#include "drawer/drawer.h"
#include <QPainter>

class QtSceneDrawer : public SceneDrawerBase {
public:
    QtSceneDrawer(QPainter& painter) : painter(painter) {};

    void DrawScene(const Scene& scene) override;
private:
    QPainter& painter;
};

#endif //OOP4_QTSCENE_H
