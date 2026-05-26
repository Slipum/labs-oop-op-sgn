#include "../figure.h"

void Figure::Transform(const TransformMatrix& matrix) {
    for (auto& vertex : _vertices) {
        vertex.Transform(matrix);
    }
}

void Figure::AddVertex(const Vertex& v) {
    _vertices.push_back(v);
}

void Figure::AddEdge(const Edge& e) {
    _edges.push_back(e);
}