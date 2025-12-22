#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
vector<pair<int, int>> linePoints;

// Bresenham Line Drawing Algorithm - handles both slopes
void bresenhamLine(int x0, int y0, int x1, int y1) {
    linePoints.clear();
    
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = (dx > dy) ? (dx / 2) : (-dy / 2);
    
    int x = x0;
    int y = y0;
    
    while (true) {
        linePoints.push_back({x, y});
        
        if (x == x1 && y == y1) break;
        
        int e2 = err;
        if (e2 > -dx) {
            err -= dy;
            x += sx;
        }
        if (e2 < dy) {
            err += dx;
            y += sy;
        }
    }
}

// Display callback - renders the line
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw grid
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    for (int i = 0; i <= WINDOW_WIDTH; i += 50) {
        glVertex2f(i, 0);
        glVertex2f(i, WINDOW_HEIGHT);
    }
    for (int i = 0; i <= WINDOW_HEIGHT; i += 50) {
        glVertex2f(0, i);
        glVertex2f(WINDOW_WIDTH, i);
    }
    glEnd();
    
    // Draw axes
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_LINES);
    glVertex2f(0, WINDOW_HEIGHT / 2);
    glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT / 2);
    glVertex2f(WINDOW_WIDTH / 2, 0);
    glVertex2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
    glEnd();
    
    // Draw line using Bresenham points
    glColor3f(1.0f, 0.0f, 0.0f);  // Red
    glPointSize(3.0f);
    glBegin(GL_POINTS);
    for (const auto& p : linePoints) {
        glVertex2f(p.first, p.second);
    }
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


// Initialize OpenGL
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv) {
    cout << "Lab 2B - Bresenham Line Drawing Algorithm" << endl;
    cout << "Supports both |m| < 1 and |m| >= 1 slopes" << endl;
    
    
    // Draw a single line from (100, 100) to (700, 500)
    bresenhamLine(100, 100, 700, 500);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lab 2B - Bresenham Line Algorithm");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    
    init();
    glutMainLoop();
    
    return 0;
}
