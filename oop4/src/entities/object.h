#ifndef OOP4_OBJECT_H
#define OOP4_OBJECT_H
#include "../math/transform.h"

class SceneObject {
public:
    virtual ~SceneObject() = default;

    virtual void Transform(const TransformMatrix& matrix) = 0;
};

#endif //OOP4_OBJECT_H
