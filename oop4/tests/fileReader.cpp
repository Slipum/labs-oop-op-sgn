#include <gtest/gtest.h>
#include "../src/business/file.h"

TEST(FileReaderTest, LoadSimpleCSV) {
    FileReader reader;
    NormalizationParameters params{};
    Scene scene = reader.ReadScene("../schools_exams.csv", params);

    EXPECT_EQ(scene.GetFigures().size(), 1);
    const auto& fig = scene.GetFigures()[0];
    EXPECT_GT(fig.GetVertices().size(), 0);
}

TEST(FileReaderTest, VertexCountIsCorrect) {
    FileReader reader;

    Scene scene = reader.ReadScene("../schools_exams.csv", {});

    const auto& fig = scene.GetFigures()[0];

    EXPECT_EQ(fig.GetVertices().size(), 400);
}

TEST(FileReaderTest, FirstVertexCorrect) {
    FileReader reader;

    Scene scene = reader.ReadScene("../schools_exams.csv", {});

    const auto& v = scene.GetFigures()[0].GetVertices()[0];

    EXPECT_FLOAT_EQ(v.GetPosition().x, -9.5f);
    EXPECT_FLOAT_EQ(v.GetPosition().y, 27);
    EXPECT_FLOAT_EQ(v.GetPosition().z, -9.5f);
}

TEST(FileReaderTest, AppliesStepAndNormalization) {
    FileReader reader;

    Scene scene = reader.ReadScene("../schools_exams.csv", {0.0f, 1.0f, 2.0f, 3.0f, true});

    const auto& fig = scene.GetFigures()[0];

    EXPECT_FLOAT_EQ(fig.GetVertices()[0].GetPosition().x, -19.0f);
    EXPECT_FLOAT_EQ(fig.GetVertices()[0].GetPosition().y, 1.0f);
    EXPECT_FLOAT_EQ(fig.GetVertices()[0].GetPosition().z, -28.5f);
}

TEST(FileReaderTest, EdgeCountCorrect) {
    FileReader reader;

    Scene scene = reader.ReadScene("../schools_exams.csv", {});

    const auto& fig = scene.GetFigures()[0];

    size_t rows = 20;
    size_t cols = 20;

    size_t expectedEdges = rows * (cols - 1) + cols * (rows - 1);

    EXPECT_EQ(fig.GetEdges().size(), expectedEdges);
}

TEST(FileReaderTest, EmptyFileThrows) {
    FileReader reader;

    EXPECT_THROW({
        reader.ReadScene("../empty.csv", {});
    }, std::runtime_error);
}

TEST(FileReaderTest, MissingFileThrows) {
    FileReader reader;

    EXPECT_THROW({
        reader.ReadScene("not_exists.csv", {});
    }, std::runtime_error);
}
