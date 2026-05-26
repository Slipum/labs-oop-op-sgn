#ifndef OOP4_SCENE_H
#define OOP4_SCENE_H
#include <vector>
#include "entities/abstructs/figure.h"

class Scene {
public:
    Scene() = default;
    Scene(std::vector<Figure> figures)
    : _figures(std::move(figures)) {}

    const std::vector<Figure>& GetFigures() const { return _figures;};
    void Transform(const TransformMatrix& matrix);
private:
    std::vector<Figure> _figures;
};

#endif //OOP4_SCENE_H
