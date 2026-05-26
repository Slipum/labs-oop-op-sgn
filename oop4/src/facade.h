#ifndef OOP4_FACADE_H
#define OOP4_FACADE_H

#include <string>

#include "business/file.h"
#include "scene/scene.h"
#include "drawer/drawer.h"

class FacadeOperationResult {
public:
    FacadeOperationResult(bool success, std::string error = "")
        : _isSuccess(success), _errorMessage(std::move(error)) {}

    bool IsSuccess() const { return _isSuccess; }
    const std::string& GetErrorMessage() const { return _errorMessage; }

private:
    std::string _errorMessage;
    bool _isSuccess;
};
class Facade {
public:
    Facade(BaseFileReader& fileReader, Scene& scene)
        : _fileReader(fileReader), _scene(scene) {}

    void SetDrawer(SceneDrawerBase* drawer) { _sceneDrawer = drawer; }

    FacadeOperationResult DrawScene();
    FacadeOperationResult LoadScene(std::string path, NormalizationParameters parameters);

    FacadeOperationResult MoveScene(float x, float y, float z);
    FacadeOperationResult RotateScene(float x, float y, float z);
    FacadeOperationResult ScaleScene(float x, float y, float z);

private:
    BaseFileReader& _fileReader;
    SceneDrawerBase* _sceneDrawer;
    Scene& _scene;
};
#endif