#ifndef OOP4_EDGE_H
#define OOP4_EDGE_H
#include "vertex.h"
#include <memory>

class Edge {
public:
    Edge(std::shared_ptr<Vertex> begin, std::shared_ptr<Vertex> end)
        : _begin(begin), _end(end) {}

    const std::shared_ptr<Vertex>& GetBegin() const { return _begin; }
    const std::shared_ptr<Vertex>& GetEnd() const { return _end; }

private:
    std::shared_ptr<Vertex> _begin;
    std::shared_ptr<Vertex> _end;
};

#endif //OOP4_EDGE_H
