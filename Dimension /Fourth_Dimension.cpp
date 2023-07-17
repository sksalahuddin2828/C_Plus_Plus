#include <iostream>
#include <cmath>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

int main() {
    // Define tesseract vertices
    std::vector<std::vector<double>> vertices = {{-1, -1, -1, -1},
                                                 {-1, -1, -1,  1},
                                                 {-1, -1,  1, -1},
                                                 {-1, -1,  1,  1},
                                                 {-1,  1, -1, -1},
                                                 {-1,  1, -1,  1},
                                                 {-1,  1,  1, -1},
                                                 {-1,  1,  1,  1},
                                                 { 1, -1, -1, -1},
                                                 { 1, -1, -1,  1},
                                                 { 1, -1,  1, -1},
                                                 { 1, -1,  1,  1},
                                                 { 1,  1, -1, -1},
                                                 { 1,  1, -1,  1},
                                                 { 1,  1,  1, -1},
                                                 { 1,  1,  1,  1}};

    // Define edges of the tesseract
    std::vector<std::pair<int, int>> edges = {{0, 1}, {0, 2}, {0, 4}, {1, 3}, {1, 5}, {2, 3}, {2, 6}, {3, 7},
                                              {4, 5}, {4, 6}, {5, 7}, {6, 7}, {8, 9}, {8, 10}, {8, 12}, {9, 11},
                                              {9, 13}, {10, 11}, {10, 14}, {11, 15}, {12, 13}, {12, 14}, {13, 15},
                                              {14, 15}, {0, 8}, {1, 9}, {2, 10}, {3, 11}, {4, 12}, {5, 13}, {6, 14},
                                              {7, 15}};

    // Create a figure and axis
    plt::figure_size(800, 800);
    plt::axis("off");

    // Plot the tesseract edges
    for (const auto& edge : edges) {
        plt::plot({vertices[edge.first][0], vertices[edge.second][0]},
                  {vertices[edge.first][1], vertices[edge.second][1]},
                  {vertices[edge.first][2], vertices[edge.second][2]}, "k-");
    }

    // Define rotation matrix
    double angle = M_PI / 4;
    std::vector<std::vector<double>> rotation_matrix = {{std::cos(angle), 0, -std::sin(angle), 0},
                                                        {0, std::cos(angle), 0, -std::sin(angle)},
                                                        {std::sin(angle), 0, std::cos(angle), 0},
                                                        {0, std::sin(angle), 0, std::cos(angle)}};

    // Project vertices onto 3D space
    std::vector<std::vector<double>> projected_vertices;
    for (const auto& vertex : vertices) {
        std::vector<double> projected_vertex(3, 0);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                projected_vertex[i] += vertex[j] * rotation_matrix[i][j];
            }
        }
        projected_vertices.push_back(projected_vertex);
    }

    // Plot projected vertices with labels
    std::vector<std::string> labels;
    for (const auto& vertex : vertices) {
        std::string label;
        for (int i = 0; i < 4; i++) {
            label += std::to_string(vertex[i]);
        }
        labels.push_back(label);
    }
    for (size_t i = 0; i < projected_vertices.size(); i++) {
        plt::text(projected_vertices[i][0], projected_vertices[i][1], labels[i],
                  "fontsize=8, ha='center', va='center'");
    }

    // Create illusion lines connecting projected vertices
    for (size_t i = 0; i < projected_vertices.size(); i++) {
        for (size_t j = i + 1; j < projected_vertices.size(); j++) {
            plt::plot({projected_vertices[i][0], projected_vertices[j][0]},
                      {projected_vertices[i][1], projected_vertices[j][1]},
                      {projected_vertices[i][2], projected_vertices[j][2]}, "k--");
        }
    }

    // Add a color bar
    plt::colorbar();
    plt::colorbar_label("Fourth Dimension");

    // Display the plot
    plt::show();

    return 0;
}
