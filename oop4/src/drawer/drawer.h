#ifndef OOP4_DRAWER_H
#define OOP4_DRAWER_H
#include "scene/scene.h"

class SceneDrawerBase {
public:
    virtual ~SceneDrawerBase() = default;

    virtual void DrawScene(const Scene& scene) = 0;
};



class FakeDrawer : public SceneDrawerBase {
public:
    bool called = false;

    void DrawScene(const Scene&) override {
        called = true;
    }
};

#endif //OOP4_DRAWER_H
