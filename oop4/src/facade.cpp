#include "facade.h"

FacadeOperationResult Facade::LoadScene(std::string path, NormalizationParameters parameters) {
    try {
        _scene = _fileReader.ReadScene(path, parameters);
        return FacadeOperationResult(true);
    }
    catch (const std::exception& e) {
        return FacadeOperationResult(false, e.what());
    }
}

FacadeOperationResult Facade::DrawScene() {
    if (!_sceneDrawer) return {false, "No drawer set"};

    try {
        _sceneDrawer->DrawScene(_scene);
        return FacadeOperationResult(true);
    }
    catch (const std::exception& e) {
        return FacadeOperationResult(false, e.what());
    }
}

FacadeOperationResult Facade::MoveScene(float x, float y, float z) {
    try {
        auto matrix = TransformMatrixBuilder::CreateMoveMatrix(x, y, z);
        _scene.Transform(matrix);
        return FacadeOperationResult(true);
    }
    catch (const std::exception& e) {
        return FacadeOperationResult(false, e.what());
    }
}

FacadeOperationResult Facade::RotateScene(float x, float y, float z)
{
    try {
        auto matrix = TransformMatrixBuilder::CreateRotationMatrix(x, y, z);
        _scene.Transform(matrix);
        return FacadeOperationResult(true);
    }
    catch (const std::exception& e) {
        return FacadeOperationResult(false, e.what());
    }
}

FacadeOperationResult Facade::ScaleScene(float x, float y, float z)
{
    try {
        auto matrix = TransformMatrixBuilder::CreateScaleMatrix(x, y, z);
        _scene.Transform(matrix);
        return FacadeOperationResult(true);
    }
    catch (const std::exception& e) {
        return FacadeOperationResult(false, e.what());
    }
}