#include "facade.h"

#include <cmath>

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

FacadeOperationResult Facade::MoveSceneLocal(float x, float y, float z) {
    try {
        const auto& rotation = _scene.GetObjectRotation();
        auto matrix = TransformMatrixBuilder::CreateRotationMatrix(
            rotation.x,
            rotation.y,
            rotation.z
        );
        auto delta = matrix.TransformPoint({x, y, z});

        return MoveScene(delta.x, delta.y, delta.z);
    }
    catch (const std::exception& e) {
        return FacadeOperationResult(false, e.what());
    }
}

FacadeOperationResult Facade::MoveSceneRelative(float x, float z) {
    try {
        const auto& rotation = _scene.GetCamera().GetRotation();
        auto matrix = TransformMatrixBuilder::CreateRotationMatrix(
            rotation.x,
            rotation.y,
            rotation.z
        );
        auto delta = matrix.TransformPoint({x, 0.0f, z});

        float requestedLength = std::sqrt(x * x + z * z);
        float horizontalLength = std::sqrt(delta.x * delta.x + delta.z * delta.z);

        if (horizontalLength > 0.0001f && requestedLength > 0.0001f) {
            float k = requestedLength / horizontalLength;
            delta.x *= k;
            delta.z *= k;
        }

        return MoveScene(delta.x, 0.0f, delta.z);
    }
    catch (const std::exception& e) {
        return FacadeOperationResult(false, e.what());
    }
}

FacadeOperationResult Facade::RotateScene(float x, float y, float z)
{
    try {
        auto center = _scene.GetCenter();
        auto toOrigin = TransformMatrixBuilder::CreateMoveMatrix(-center.x, -center.y, -center.z);
        auto rotation = TransformMatrixBuilder::CreateRotationMatrix(x, y, z);
        auto fromOrigin = TransformMatrixBuilder::CreateMoveMatrix(center.x, center.y, center.z);
        auto matrix = fromOrigin * rotation * toOrigin;

        _scene.Transform(matrix);
        _scene.AddObjectRotation(x, y, z);
        return FacadeOperationResult(true);
    }
    catch (const std::exception& e) {
        return FacadeOperationResult(false, e.what());
    }
}

FacadeOperationResult Facade::ScaleScene(float x, float y, float z)
{
    try {
        auto center = _scene.GetCenter();
        auto toOrigin = TransformMatrixBuilder::CreateMoveMatrix(-center.x, -center.y, -center.z);
        auto scale = TransformMatrixBuilder::CreateScaleMatrix(x, y, z);
        auto fromOrigin = TransformMatrixBuilder::CreateMoveMatrix(center.x, center.y, center.z);
        auto matrix = fromOrigin * scale * toOrigin;

        _scene.Transform(matrix);
        return FacadeOperationResult(true);
    }
    catch (const std::exception& e) {
        return FacadeOperationResult(false, e.what());
    }
}
