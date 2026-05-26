#ifndef OOP4_FACADE_H
#define OOP4_FACADE_H

#include "scene/scene.h"
#include "operations/operations.h"

class Facade {
public:
    Facade(BaseFileReader* fileReader, SceneDrawerBase* sceneDrawer)
        : _fileReader(fileReader), _sceneDrawer(sceneDrawer) {};
    ~Facade() {
        delete _fileReader;
        delete _sceneDrawer;
    };

    FacadeOperationResult DrawScene();

    FacadeOperationResult LoadScene(std::string path, NormalizationParameters parameters);

    FacadeOperationResult MoveScene(float x, float y, float z);

    FacadeOperationResult RotateScene(float x, float y, float z);

    FacadeOperationResult ScaleScene(float x, float y, float z);
private:
    BaseFileReader* _fileReader;
    SceneDrawerBase* _sceneDrawer;
    Scene _scene;
};

#endif //OOP4_FACADE_H
