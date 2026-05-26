#include "operations.h"

#include <fstream>
#include <iostream>

Scene&& FileReader::ReadScene(std::string path, NormalizationParameters parameters) {
    std::vector<std::vector<int>> matrix;
    std::ifstream f(path);

    if (!f.is_open()) throw std::runtime_error("File could not be opened!");

    std::string line;

    while (std::getline(f, line)) {
        std::vector<int> row;

        std::stringstream ss(line);
        std::string number;

        while (std::getline(ss, number, ','))row.push_back(std::stoi(number));

        matrix.push_back(row);
    }
    f.close();

    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
    for (size_t x = 0; x < matrix.size(); x++) {
        for (size_t y = 0; y < matrix[x].size(); y++) {
            Point3D point(x, y, matrix[x][y]);
            Vertex vertex(point);

            vertices.push_back(vertex);

            if (vertices.size() > 1) {
                Edge edge(vertices[vertices.size() - 2], vertices[vertices.size() - 1]);
                edges.push_back(edge);
            }
        }
    }
    Edge edge(vertices[0], vertices[vertices.size() - 1]);
    edges.push_back(edge);

    Figure figure(vertices, edges);

    std::vector<Figure> figures;
    figures.push_back(figure);

    Scene scene(figures);
    return std::move(scene);
}
