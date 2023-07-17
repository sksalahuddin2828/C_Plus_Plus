#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

int main() {
    // Define tesseract vertices
    std::vector<std::vector<double>> vertices = {{-1, -1, -1, -1, -1},
                                                 {-1, -1, -1, -1, 1},
                                                 {-1, -1, -1, 1, -1},
                                                 {-1, -1, -1, 1, 1},
                                                 {-1, -1, 1, -1, -1},
                                                 {-1, -1, 1, -1, 1},
                                                 {-1, -1, 1, 1, -1},
                                                 {-1, -1, 1, 1, 1},
                                                 {-1, 1, -1, -1, -1},
                                                 {-1, 1, -1, -1, 1},
                                                 {-1, 1, -1, 1, -1},
                                                 {-1, 1, -1, 1, 1},
                                                 {-1, 1, 1, -1, -1},
                                                 {-1, 1, 1, -1, 1},
                                                 {-1, 1, 1, 1, -1},
                                                 {-1, 1, 1, 1, 1},
                                                 {1, -1, -1, -1, -1},
                                                 {1, -1, -1, -1, 1},
                                                 {1, -1, -1, 1, -1},
                                                 {1, -1, -1, 1, 1},
                                                 {1, -1, 1, -1, -1},
                                                 {1, -1, 1, -1, 1},
                                                 {1, -1, 1, 1, -1},
                                                 {1, -1, 1, 1, 1},
                                                 {1, 1, -1, -1, -1},
                                                 {1, 1, -1, -1, 1},
                                                 {1, 1, -1, 1, -1},
                                                 {1, 1, -1, 1, 1},
                                                 {1, 1, 1, -1, -1},
                                                 {1, 1, 1, -1, 1},
                                                 {1, 1, 1, 1, -1},
                                                 {1, 1, 1, 1, 1}};

    // Define edges of the tesseract
    std::vector<std::pair<int, int>> edges = {{0, 1},  {0, 2},  {0, 4},  {1, 3},  {1, 5},  {2, 3},
                                              {2, 6},  {3, 7},  {4, 5},  {4, 6},  {5, 7},  {6, 7},
                                              {8, 9},  {8, 10}, {8, 12}, {9, 11}, {9, 13}, {10, 11},
                                              {10, 14}, {11, 15}, {12, 13}, {12, 14}, {13, 15}, {14, 15},
                                              {0, 8},  {1, 9},  {2, 10}, {3, 11}, {4, 12}, {5, 13},
                                              {6, 14}, {7, 15}};

    // Create a figure and axis
    plt::figure_size(800, 800);
    plt::axis("off");

    // Plot the tesseract edges
    for (const auto& edge : edges) {
        std::vector<double> x = {vertices[edge.first][0], vertices[edge.second][0]};
        std::vector<double> y = {vertices[edge.first][1], vertices[edge.second][1]};
        std::vector<double> z = {vertices[edge.first][2], vertices[edge.second][2]};
        plt::plot3d(x, y, z, "black");
    }

    // Define rotation matrix
    double angle = M_PI / 4.0;
    std::vector<std::vector<double>> rotation_matrix = {{cos(angle), 0, -sin(angle), 0, 0},
                                                        {0, cos(angle), 0, -sin(angle), 0},
                                                        {sin(angle), 0, cos(angle), 0, 0},
                                                        {0, sin(angle), 0, cos(angle), 0},
                                                        {0, 0, 0, 0, 1}};

    // Project vertices onto 3D space
    std::vector<std::vector<double>> projected_vertices;
    for (const auto& vertex : vertices) {
        std::vector<double> projected_vertex;
        for (size_t i = 0; i < rotation_matrix.size(); ++i) {
            double sum = 0.0;
            for (size_t j = 0; j < rotation_matrix[i].size(); ++j) {
                sum += rotation_matrix[i][j] * vertex[j];
            }
            projected_vertex.push_back(sum);
        }
        projected_vertices.push_back(projected_vertex);
    }

    // Plot projected vertices with labels
    std::vector<std::string> labels;
    for (const auto& vertex : vertices) {
        std::string label;
        for (const auto& v : vertex) {
            label += std::to_string(v);
        }
        labels.push_back(label);
    }

    std::vector<double> projected_x, projected_y, projected_z;
    for (const auto& vertex : projected_vertices) {
        projected_x.push_back(vertex[0]);
        projected_y.push_back(vertex[1]);
        projected_z.push_back(vertex[2]);
    }

    plt::scatter3d(projected_x, projected_y, projected_z, 100, vertices[0], "viridis");

    for (size_t i = 0; i < projected_vertices.size(); ++i) {
        plt::text3d(projected_x[i], projected_y[i], projected_z[i], labels[i], 8);
    }

    // Create illusion lines connecting projected vertices
    for (size_t i = 0; i < projected_vertices.size(); ++i) {
        for (size_t j = i + 1; j < projected_vertices.size(); ++j) {
            std::vector<double> x = {projected_vertices[i][0], projected_vertices[j][0]};
            std::vector<double> y = {projected_vertices[i][1], projected_vertices[j][1]};
            std::vector<double> z = {projected_vertices[i][2], projected_vertices[j][2]};
            plt::plot3d(x, y, z, "k--");
        }
    }

    // Add a color bar
    plt::colorbar();

    // Display the plot
    plt::show();

    return 0;
}
