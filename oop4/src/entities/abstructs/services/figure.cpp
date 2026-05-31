#include "../figure.h"

#include <unordered_set>

void Figure::Transform(const TransformMatrix& matrix) {
    for (auto& vertex : _vertices) {
        vertex.Transform(matrix);
    }

    std::unordered_set<Vertex*> transformedEdgeVertices;

    auto transformEdgeVertex = [&](const std::shared_ptr<Vertex>& vertex) {
        if (vertex && transformedEdgeVertices.insert(vertex.get()).second) {
            vertex->Transform(matrix);
        }
    };

    for (const auto& edge : _edges) {
        transformEdgeVertex(edge.GetBegin());
        transformEdgeVertex(edge.GetEnd());
    }
}

void Figure::AddVertex(const Vertex& v) {
    _vertices.push_back(v);
}

void Figure::AddEdge(const Edge& e) {
    _edges.push_back(e);
}
