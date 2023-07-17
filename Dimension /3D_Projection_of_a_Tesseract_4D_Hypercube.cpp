// OpenGL Utility Toolkit header
#include <GL/glut.h> 

// GLM header for vector and matrix operations
#include <glm/glm.hpp> 

using namespace glm;

// Define the vertices of a unit tesseract in 4D space
vec4 vertices[] = {
    vec4(-0.5f, -0.5f, -0.5f, -0.5f),
    vec4(0.5f, -0.5f, -0.5f, -0.5f),
    vec4(0.5f, 0.5f, -0.5f, -0.5f),
    vec4(-0.5f, 0.5f, -0.5f, -0.5f),
    vec4(-0.5f, -0.5f, 0.5f, -0.5f),
    vec4(0.5f, -0.5f, 0.5f, -0.5f),
    vec4(0.5f, 0.5f, 0.5f, -0.5f),
    vec4(-0.5f, 0.5f, 0.5f, -0.5f),
    vec4(-0.5f, -0.5f, -0.5f, 0.5f),
    vec4(0.5f, -0.5f, -0.5f, 0.5f),
    vec4(0.5f, 0.5f, -0.5f, 0.5f),
    vec4(-0.5f, 0.5f, -0.5f, 0.5f),
    vec4(-0.5f, -0.5f, 0.5f, 0.5f),
    vec4(0.5f, -0.5f, 0.5f, 0.5f),
    vec4(0.5f, 0.5f, 0.5f, 0.5f),
    vec4(-0.5f, 0.5f, 0.5f, 0.5f)
};

// Define the edges of the tesseract
int edges[][2] = {
    {0, 1}, {1, 2}, {2, 3}, {3, 0},
    {4, 5}, {5, 6}, {6, 7}, {7, 4},
    {0, 4}, {1, 5}, {2, 6}, {3, 7},
    {8, 9}, {9, 10}, {10, 11}, {11, 8},
    {12, 13}, {13, 14}, {14, 15}, {15, 12},
    {8, 12}, {9, 13}, {10, 14}, {11, 15},
    {0, 8}, {1, 9}, {2, 10}, {3, 11},
    {4, 12}, {5, 13}, {6, 14}, {7, 15}
};

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.5, 1.5, -1.5, 1.5, -1.5, 1.5);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Project the tesseract's vertices to 3D space
    vec3 projection_3d[16];
    for (int i = 0; i < 16; i++)
    {
        projection_3d[i] = vec3((vertices[i].x + vertices[i].y) / 2.0f,
                                (vertices[i].z + vertices[i].w) / 2.0f,
                                (vertices[i].x + vertices[i].z) / 2.0f);
    }

    // Draw the edges
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 1.0f);
    for (int i = 0; i < 32; i++)
    {
        glVertex3f(projection_3d[edges[i][0]].x, projection_3d[edges[i][0]].y, projection_3d[edges[i][0]].z);
        glVertex3f(projection_3d[edges[i][1]].x, projection_3d[edges[i][1]].y, projection_3d[edges[i][1]].z);
    }
    glEnd();

    // Draw the faces of the tesseract
    glBegin(GL_QUADS);
    glColor4f(0.0f, 1.0f, 1.0f, 0.25f);
    for (int i = 0; i < 6; i++)
    {
        int a = i * 4;
        glVertex3f(projection_3d[a].x, projection_3d[a].y, projection_3d[a].z);
        glVertex3f(projection_3d[a + 1].x, projection_3d[a + 1].y, projection_3d[a + 1].z);
        glVertex3f(projection_3d[a + 2].x, projection_3d[a + 2].y, projection_3d[a + 2].z);
        glVertex3f(projection_3d[a + 3].x, projection_3d[a + 3].y, projection_3d[a + 3].z);
    }
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("3D Projection of a Tesseract (4D Hypercube)");

    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}
