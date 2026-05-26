#include "file.h"

#include <fstream>
#include <sstream>

Scene FileReader::ReadScene(const std::string& path, const NormalizationParameters& params) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file");
    }

    std::vector<std::vector<float>> grid;
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string value;

        std::vector<float> row;

        while (std::getline(ss, value, ',')) {
            row.push_back(std::stof(value));
        }

        grid.push_back(row);
    }

    if (grid.empty()) throw std::runtime_error("Empty file");

    Figure figure;

    size_t rows = grid.size();
    size_t cols = grid[0].size();

    for (size_t y = 0; y < rows; y++) {
        for (size_t x = 0; x < cols; x++) {

            float z = grid[y][x];

            Vertex v(x, y, z);
            figure.AddVertex(v);
        }
    }

    auto index = [&](size_t x, size_t y) {
        return y * cols + x;
    };

    for (size_t y = 0; y < rows; y++) {
        for (size_t x = 0; x < cols; x++) {

            if (x + 1 < cols) {
                figure.AddEdge(Edge(
                    std::make_shared<Vertex>(
                        figure.GetVertices()[index(x, y)]
                    ),
                    std::make_shared<Vertex>(
                        figure.GetVertices()[index(x + 1, y)]
                    )
                ));
            }

            if (y + 1 < rows) {
                figure.AddEdge(Edge(
                    std::make_shared<Vertex>(
                        figure.GetVertices()[index(x, y)]
                    ),
                    std::make_shared<Vertex>(
                        figure.GetVertices()[index(x, y + 1)]
                    )
                ));
            }
        }
    }

    Scene scene(std::vector<Figure> {figure});

    return scene;
}
