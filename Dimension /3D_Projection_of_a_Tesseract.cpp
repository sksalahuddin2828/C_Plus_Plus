//C++ using OpenGL and GLUT

#include <GL/glut.h>

// Define tesseract vertices
GLfloat vertices[17][5] = {
    {-1, -1, -1, -1, -1},
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
    {1, 1, 1, 1, 1} // Second dimension vertex
};

// Define edges of the tesseract
int edges[32][2] = {
    {0, 1}, {0, 2}, {0, 4}, {1, 3}, {1, 5}, {2, 3}, {2, 6}, {3, 7},
    {4, 5}, {4, 6}, {5, 7}, {6, 7}, {8, 9}, {8, 10}, {8, 12}, {9, 11},
    {9, 13}, {10, 11}, {10, 14}, {11, 15}, {12, 13}, {12, 14}, {13, 15},
    {14, 15}, {0, 8}, {1, 9}, {2, 10}, {3, 11}, {4, 12}, {5, 13}, {6, 14},
    {7, 15}
};

void drawTesseract()
{
    // Project vertices onto 3D space (select the first three components)
    GLfloat projectedVertices[17][3];
    for (int i = 0; i < 17; i++)
    {
        projectedVertices[i][0] = vertices[i][0];
        projectedVertices[i][1] = vertices[i][1];
        projectedVertices[i][2] = vertices[i][2];
    }

    // Draw the tesseract edges
    glBegin(GL_LINES);
    glColor3f(0.5f, 0.5f, 0.5f);
    for (int i = 0; i < 32; i++)
    {
        glVertex3fv(projectedVertices[edges[i][0]]);
        glVertex3fv(projectedVertices[edges[i][1]]);
    }
    glEnd();

    // Draw projected vertices with labels
    glPointSize(5.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < 17; i++)
    {
        glRasterPos3fv(projectedVertices[i]);
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0' + i);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    drawTesseract();
    glFlush();
}

void reshape(int width, int height)
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)width / (GLfloat)height, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D Projection of a Tesseract (4D Hypercube)");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
