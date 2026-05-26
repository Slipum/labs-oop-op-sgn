#include "facade.h"

#include "transform/transform.h"

FacadeOperationResult Facade::DrawScene() {
    try {
        _sceneDrawer->DrawScene(_scene);
    } catch (std::exception &e) {
        return FacadeOperationResult(e.what(), false);
    }
    return FacadeOperationResult("", true);
}

FacadeOperationResult Facade::LoadScene(std::string path, NormalizationParameters parameters) {
    try {
        _scene = _fileReader->ReadScene(path, parameters);
    } catch (std::exception &e) {
        return FacadeOperationResult(e.what(), false);
    }
    return FacadeOperationResult("", true);
}

FacadeOperationResult Facade::MoveScene(float x, float y, float z) {
    try {
        _scene.TransformFigures(TransformMatrixBuilder::CreateMoveMatrix(x, y, z));
    } catch (std::exception &e) {
        return FacadeOperationResult(e.what(), false);
    }
    return FacadeOperationResult("", true);
}

FacadeOperationResult Facade::RotateScene(float x, float y, float z) {
    try {
        _scene.TransformFigures(TransformMatrixBuilder::CreateRotationMatrix(x, y, z));
    } catch (std::exception &e) {
        return FacadeOperationResult(e.what(), false);
    }
    return FacadeOperationResult("", true);
}

FacadeOperationResult Facade::ScaleScene(float x, float y, float z) {
    try {
        _scene.TransformFigures(TransformMatrixBuilder::CreateScaleMatrix(x, y, z));
    } catch (std::exception &e) {
        return FacadeOperationResult(e.what(), false);
    }
    return FacadeOperationResult("", true);
}