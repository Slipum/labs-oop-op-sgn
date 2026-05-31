#include "file.h"

#include <algorithm>
#include <fstream>
#include <limits>
#include <stdexcept>
#include <sstream>

Scene FileReader::ReadScene(const std::string& path, const NormalizationParameters& params) {
    if (params.DxStep <= 0.0f || params.DyStep <= 0.0f) {
        throw std::runtime_error("Point step must be positive");
    }

    if (params.EnableNormalization && params.Min >= params.Max) {
        throw std::runtime_error("Normalization range must be ascending");
    }

    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file");
    }

    std::vector<std::vector<float>> grid;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string value;

        std::vector<float> row;

        while (std::getline(ss, value, ',')) {
            if (value.empty()) {
                throw std::runtime_error("CSV contains an empty value");
            }

            row.push_back(std::stof(value));
        }

        if (!row.empty()) {
            grid.push_back(row);
        }
    }

    if (grid.empty()) throw std::runtime_error("Empty file");

    size_t rows = grid.size();
    size_t cols = grid[0].size();

    for (const auto& row : grid) {
        if (row.size() != cols) {
            throw std::runtime_error("CSV rows must have the same number of columns");
        }
    }

    float sourceMin = std::numeric_limits<float>::max();
    float sourceMax = std::numeric_limits<float>::lowest();

    for (const auto& row : grid) {
        for (float value : row) {
            sourceMin = std::min(sourceMin, value);
            sourceMax = std::max(sourceMax, value);
        }
    }

    auto normalize = [&](float value) {
        if (!params.EnableNormalization) {
            return value;
        }

        if (sourceMin == sourceMax) {
            return (params.Min + params.Max) / 2.0f;
        }

        return params.Min
            + (value - sourceMin) / (sourceMax - sourceMin)
            * (params.Max - params.Min);
    };

    Figure figure;
    float xOrigin = static_cast<float>(cols - 1) * params.DxStep / 2.0f;
    float zOrigin = static_cast<float>(rows - 1) * params.DyStep / 2.0f;

    for (size_t y = 0; y < rows; y++) {
        for (size_t x = 0; x < cols; x++) {

            float xCoord = static_cast<float>(x) * params.DxStep - xOrigin;
            float yCoord = normalize(grid[y][x]);
            float zCoord = static_cast<float>(y) * params.DyStep - zOrigin;

            Vertex v(xCoord, yCoord, zCoord);
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
