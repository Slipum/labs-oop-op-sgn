#ifndef OOP4_SCENE_H
#define OOP4_SCENE_H
#include <QWidget>
#include <vector>

#include "object/object.h"

class Scene {
public:
    Scene() = default;
    Scene(std::vector<Figure> figures) : _figures(figures) {};

    std::vector<Figure>& GetFigures() { return _figures; };
    void TransformFigures(TransformMatrix matrix);
private:
    std::vector<Figure> _figures;
};



class SceneDrawerBase {
public:
    virtual void DrawScene(Scene& scene) = 0;
};

class QtSceneDrawer : public SceneDrawerBase {
public:
    QtSceneDrawer(QWidget* widget) : _widget(widget) {};

    void DrawScene(Scene& scene) override;
private:
    QWidget* _widget;
};

#endif //OOP4_SCENE_H
