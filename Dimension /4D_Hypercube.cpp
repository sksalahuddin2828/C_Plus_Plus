#include <iostream>
#include <GL/glut.h>

// Define tesseract vertices
GLfloat vertices[][4] = {
    {-1, -1, -1, -1},
    {-1, -1, -1, 1},
    {-1, -1, 1, -1},
    {-1, -1, 1, 1},
    {-1, 1, -1, -1},
    {-1, 1, -1, 1},
    {-1, 1, 1, -1},
    {-1, 1, 1, 1},
    {1, -1, -1, -1},
    {1, -1, -1, 1},
    {1, -1, 1, -1},
    {1, -1, 1, 1},
    {1, 1, -1, -1},
    {1, 1, -1, 1},
    {1, 1, 1, -1},
    {1, 1, 1, 1},
    {1, 1, 1, 1} // Second dimension vertex
};

// Define edges of the tesseract
GLint edges[][2] = {
    {0, 1}, {0, 2}, {0, 4}, {1, 3}, {1, 5}, {2, 3}, {2, 6}, {3, 7},
    {4, 5}, {4, 6}, {5, 7}, {6, 7}, {8, 9}, {8, 10}, {8, 12}, {9, 11},
    {9, 13}, {10, 11}, {10, 14}, {11, 15}, {12, 13}, {12, 14}, {13, 15},
    {14, 15}, {0, 8}, {1, 9}, {2, 10}, {3, 11}, {4, 12}, {5, 13}, {6, 14},
    {7, 15}
};

// Display the tesseract
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Project vertices onto 3D space (select the first three components)
    GLfloat projectedVertices[16][3];
    for (int i = 0; i < 16; i++)
    {
        projectedVertices[i][0] = vertices[i][0];
        projectedVertices[i][1] = vertices[i][1];
        projectedVertices[i][2] = vertices[i][2];
    }

    // Plot the tesseract edges
    glBegin(GL_LINES);
    glColor3f(0.5, 0.5, 0.5);
    for (int i = 0; i < 32; i++)
    {
        glVertex3fv(projectedVertices[edges[i][0]]);
        glVertex3fv(projectedVertices[edges[i][1]]);
    }
    glEnd();

    // Swap buffers
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    // Initialize GLUT and create a window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Tesseract Projection");

    // Set the projection and viewing transformation
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -10, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set the background color and enable depth testing
    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);

    // Register the display callback function
    glutDisplayFunc(display);

    // Start the main loop
    glutMainLoop();

    return 0;
}
