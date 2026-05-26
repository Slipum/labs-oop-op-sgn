#ifndef OOP4_FILE_H
#define OOP4_FILE_H
#include "normalization.h"
#include "scene/scene.h"

class BaseFileReader {
public:
    virtual Scene ReadScene(const std::string& path, const NormalizationParameters& params) = 0;
};

class FileReader : public BaseFileReader {
public:
    Scene ReadScene(const std::string& path, const NormalizationParameters& params) override;
};

class FakeFileReader : public BaseFileReader {
public:
    Scene ReadScene(const std::string& path, const NormalizationParameters& params) override {
        Figure f;
        f.AddVertex(Vertex(0, 0, 0));
        f.AddVertex(Vertex(1, 0, 0));
        f.AddVertex(Vertex(0, 1, 0));

        Scene scene = Scene(std::vector<Figure>{f});

        return scene;
    }
};

#endif //OOP4_FILE_H
