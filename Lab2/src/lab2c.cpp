#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
vector<pair<int, int>> circlePoints;

// Midpoint Circle Drawing Algorithm
void midpointCircle(int centerX, int centerY, int radius) {
    circlePoints.clear();
    
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;  // Decision parameter
    
    while (x <= y) {
        // Plot all 8 octants
        circlePoints.push_back({centerX + x, centerY 
            + y});
        circlePoints.push_back({centerX - x, centerY + y});
        circlePoints.push_back({centerX + x, centerY - y});
        circlePoints.push_back({centerX - x, centerY - y});
        circlePoints.push_back({centerX + y, centerY + x});
        circlePoints.push_back({centerX - y, centerY + x});
        circlePoints.push_back({centerX + y, centerY - x});
        circlePoints.push_back({centerX - y, centerY - x});
        
        //update decision parameter
        //lies inside circle
        if (d < 0) {
            d = d + 4 * x + 6;
        }
        //lies outside circle or on circle
        else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

// Display callback - renders the circle
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw axes
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_LINES);
    glVertex2f(WINDOW_WIDTH / 2, 0);
    glVertex2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
    glVertex2f(0, WINDOW_HEIGHT / 2);
    glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT / 2);
    glEnd();
    
    // Draw circle using Midpoint algorithm
    glColor3f(0.0f, 1.0f, 0.0f);  // Green
    glPointSize(3.0f);
    glBegin(GL_POINTS);
    for (const auto& p : circlePoints) {
        glVertex2f(p.first, p.second);
    }
    glEnd();
    
    // Draw center point
    glColor3f(1.0f, 1.0f, 1.0f);  // White
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(400, 300);
    glEnd();
    
    glFlush();
    glutSwapBuffers();
}

// Reshape callback
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Keyboard callback
void keyboard(unsigned char key, int x, int y) {
    if (key == 27) {  // ESC key
        exit(0);
    }
}

// Initialize OpenGL
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv) {
    cout << "Lab 2C - Midpoint Circle Drawing Algorithm" << endl;
    cout << "Draws a circle centered at (400, 300) with radius 150" << endl;
    cout << "Press ESC to exit" << endl;
    
    // Draw a single circle at center (400, 300) with radius 150
    midpointCircle(400, 300, 150);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lab 2C - Midpoint Circle Algorithm");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    init();
    glutMainLoop();
    
    return 0;
}
