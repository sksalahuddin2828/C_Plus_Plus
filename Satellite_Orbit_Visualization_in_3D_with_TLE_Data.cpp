#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <GL/glut.h>

#include <OrekitHeaders.hpp>

using namespace std;
using namespace Orekit;

// Define satellite data struct
struct SatelliteData {
    string name;
    string line1;
    string line2;
    float color[3];
};

vector<SatelliteData> satelliteDataList;

void readTLEData(const string& tleFile) {
    ifstream file(tleFile);
    string line;
    while (getline(file, line)) {
        SatelliteData satelliteData;
        satelliteData.name = line;
        getline(file, satelliteData.line1);
        getline(file, satelliteData.line2);
        satelliteData.color[0] = 0.0f;  // Set default color to black
        satelliteData.color[1] = 0.0f;
        satelliteData.color[2] = 0.0f;
        satelliteDataList.push_back(satelliteData);
    }
    file.close();
}

void drawSphere(GLfloat radius, GLint slices, GLint stacks) {
    GLUquadricObj* quadric = gluNewQuadric();
    gluSphere(quadric, radius, slices, stacks);
    gluDeleteQuadric(quadric);
}

void drawCylinder(GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks) {
    GLUquadricObj* quadric = gluNewQuadric();
    gluCylinder(quadric, base, top, height, slices, stacks);
    gluDeleteQuadric(quadric);
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Draw Earth
    glColor3f(0.0f, 0.0f, 1.0f);
    drawSphere(1.0f, 32, 32);

    // Draw satellite paths
    for (const SatelliteData& satelliteData : satelliteDataList) {
        glColor3fv(satelliteData.color);

        stringstream line1Stream(satelliteData.line1);
        stringstream line2Stream(satelliteData.line2);
        TLE tle("", line1Stream.str(), line2Stream.str());
        Orbit orbit = tle.getOrbit();
        double t = 0.0;
        double dt = 5.0;
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < 72; i++) {
            AbsoluteDate date = AbsoluteDate::J2000_EPOCH().shiftedBy(t);
            PVCoordinates pvCoordinates = orbit.getPVCoordinates(date);
            double x = pvCoordinates.getPosition().getX() / 1000.0;
            double y = pvCoordinates.getPosition().getY() / 1000.0;
            double z = pvCoordinates.getPosition().getZ() / 1000.0;
            glVertex3d(x, y, z);
            t += dt;
        }
        glEnd();
    }

    glFlush();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

int main(int argc, char** argv) {
    // Initialize Orekit
    try {
        string orekitData = "<PATH_TO_OREKIT_DATA>";  // Set the path to Orekit data
        Orekit::init(orekitData);
    } catch (exception& e) {
        cerr << "Failed to initialize Orekit: " << e.what() << endl;
        return 1;
    }

    // Read TLE data from a file
    string tleFile = "tle_data.txt";  // Path to the TLE file
    readTLEData(tleFile);

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Satellite Orbits");

    // Set GLUT callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshape);

    // Initialize OpenGL
    initGL();

    // Start the main GLUT loop
    glutMainLoop();

    return 0;
}
