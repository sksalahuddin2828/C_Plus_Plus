#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <Eigen/Core>
#include <Eigen/StdVector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

typedef Eigen::Matrix<float, 3, 1> Vector3f;
typedef Eigen::Matrix<float, 4, 1> Vector4f;
typedef Eigen::Matrix<float, 4, 4> Matrix4f;

void createRotationMatrix(Matrix4f& matrix, float angle, const Vector3f& axis)
{
    float cosTheta = std::cos(angle);
    float sinTheta = std::sin(angle);
    float oneMinusCosTheta = 1 - cosTheta;

    float ux = axis(0);
    float uy = axis(1);
    float uz = axis(2);

    matrix << cosTheta + ux * ux * oneMinusCosTheta,
              ux * uy * oneMinusCosTheta - uz * sinTheta,
              ux * uz * oneMinusCosTheta + uy * sinTheta,
              0,

              uy * ux * oneMinusCosTheta + uz * sinTheta,
              cosTheta + uy * uy * oneMinusCosTheta,
              uy * uz * oneMinusCosTheta - ux * sinTheta,
              0,

              uz * ux * oneMinusCosTheta - uy * sinTheta,
              uz * uy * oneMinusCosTheta + ux * sinTheta,
              cosTheta + uz * uz * oneMinusCosTheta,
              0,

              0, 0, 0, 1;
}

void projectVerticesTo3D(const std::vector<Vector4f>& vertices, const Matrix4f& rotationMatrix, std::vector<Vector3f>& projectedVertices)
{
    projectedVertices.resize(vertices.size());

    for (size_t i = 0; i < vertices.size(); i++)
    {
        projectedVertices[i] = rotationMatrix.topLeftCorner<3, 3>() * vertices[i].head<3>();
    }
}

void projectVerticesTo456(const std::vector<Vector3f>& projectedVertices, const Matrix4f& rotationMatrix, std::vector<Vector3f>& projectedVertices456)
{
    projectedVertices456.resize(projectedVertices.size());

    for (size_t i = 0; i < projectedVertices.size(); i++)
    {
        projectedVertices456[i] = rotationMatrix.topLeftCorner<3, 3>() * projectedVertices[i];
    }
}

int main()
{
    std::vector<Vector4f> vertices = {
        Vector4f(-1, -1, -1, -1),
        Vector4f(-1, -1, -1, 1),
        Vector4f(-1, -1, 1, -1),
        Vector4f(-1, -1, 1, 1),
        Vector4f(-1, 1, -1, -1),
        Vector4f(-1, 1, -1, 1),
        Vector4f(-1, 1, 1, -1),
        Vector4f(-1, 1, 1, 1),
        Vector4f(1, -1, -1, -1),
        Vector4f(1, -1, -1, 1),
        Vector4f(1, -1, 1, -1),
        Vector4f(1, -1, 1, 1),
        Vector4f(1, 1, -1, -1),
        Vector4f(1, 1, -1, 1),
        Vector4f(1, 1, 1, -1),
        Vector4f(1, 1, 1, 1)
    };

    std::vector<std::pair<int, int>> edges = {
        {0, 1}, {0, 2}, {0, 4}, {1, 3}, {1, 5}, {2, 3}, {2, 6}, {3, 7},
        {4, 5}, {4, 6}, {5, 7}, {6, 7}, {8, 9}, {8, 10}, {8, 12}, {9, 11},
        {9, 13}, {10, 11}, {10, 14}, {11, 15}, {12, 13}, {12, 14}, {13, 15},
        {14, 15}, {0, 8}, {1, 9}, {2, 10}, {3, 11}, {4, 12}, {5, 13}, {6, 14},
        {7, 15}
    };

    float angle = M_PI / 4;

    Matrix4f rotationMatrix3D;
    createRotationMatrix(rotationMatrix3D, angle, Vector3f(0, 1, 0));

    std::vector<Vector3f> projectedVertices3D;
    projectVerticesTo3D(vertices, rotationMatrix3D, projectedVertices3D);

    Matrix4f rotationMatrix456;
    createRotationMatrix(rotationMatrix456, angle, Vector3f(1, 0, 0));

    std::vector<Vector3f> projectedVertices456;
    projectVerticesTo456(projectedVertices3D, rotationMatrix456, projectedVertices456);

    cv::Mat image(800, 800, CV_8UC3, cv::Scalar(255, 255, 255));

    for (const auto& edge : edges)
    {
        const Vector3f& v0 = projectedVertices3D[edge.first];
        const Vector3f& v1 = projectedVertices3D[edge.second];

        cv::line(image, cv::Point(v0(0) * 100 + 400, v0(1) * 100 + 400), cv::Point(v1(0) * 100 + 400, v1(1) * 100 + 400), cv::Scalar(0, 0, 0), 1);
    }

    for (size_t i = 0; i < vertices.size(); i++)
    {
        const Vector3f& vertex = projectedVertices3D[i];
        const Vector3f& vertex456 = projectedVertices456[i];

        std::stringstream labelStream;
        labelStream << std::fixed << std::setprecision(1) << vertices[i].transpose();
        std::string label = labelStream.str();

        cv::circle(image, cv::Point(vertex(0) * 100 + 400, vertex(1) * 100 + 400), 3, cv::Scalar(0, 0, 0), cv::FILLED);
        cv::putText(image, label, cv::Point(vertex(0) * 100 + 400, vertex(1) * 100 + 400), cv::FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(0, 0, 0), 1, cv::LINE_AA);
    }

    cv::namedWindow("Tesseract Projection", cv::WINDOW_NORMAL);
    cv::imshow("Tesseract Projection", image);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
