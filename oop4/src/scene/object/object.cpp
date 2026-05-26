#include "object.h"

void Figure::Transform(TransformMatrix matrix) {
    for (auto vertex : _vertices) {
        vertex.Transform(matrix);
    }
}

void Vertex::Transform(TransformMatrix matrix) {
    _position = matrix.TransformPoint(_position);
}
