#ifndef OOP4_FIGURE_H
#define OOP4_FIGURE_H
#include <vector>

#include "edge.h"
#include "vertex.h"
#include "../object.h"

class Figure : public SceneObject {
public:
    const std::vector<Vertex>& GetVertices() const{ return _vertices; };
    const std::vector<Edge>& GetEdges() const { return _edges; };

    void AddVertex(const Vertex& v);
    void AddEdge(const Edge& e);

    void Transform(const TransformMatrix& matrix) override;
private:
    std::vector<Vertex> _vertices;
    std::vector<Edge> _edges;
};

#endif //OOP4_FIGURE_H
