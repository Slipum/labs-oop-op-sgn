#ifndef OOP4_OBJECT_H
#define OOP4_OBJECT_H

#include <vector>

#include "../../transform/transform.h"

class SceneObject {
public:
    virtual ~SceneObject() = default;

    virtual void Transform(TransformMatrix matrix) = 0;
};



class Vertex : public SceneObject {
public:
    Vertex(Point3D& position) : _position(position) {};

    Point3D& GetPosition() { return _position; };
    void Transform(TransformMatrix matrix) override;
private:
    Point3D _position;
};



class Edge {
public:
    Edge(Vertex& begin, Vertex& end) : _begin(begin), _end(end) {};

    Vertex GetBegin() { return this->_begin; }
    Vertex GetEnd() { return this->_end; }
private:
    Vertex& _begin;
    Vertex& _end;
};

class Figure : public SceneObject {
public:
    Figure(std::vector<Vertex> vertices, std::vector<Edge> edges)
    : _vertices(vertices), _edges(edges) {};

    std::vector<Vertex> GetVertices() { return _vertices; };

    std::vector<Edge> GetEdges() { return _edges; };

    void Transform(TransformMatrix matrix) override;
private:
    std::vector<Vertex> _vertices;
    std::vector<Edge> _edges;
};

#endif //OOP4_OBJECT_H
