#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int GRID_WIDTH = 500;
const int GRID_HEIGHT = 500;


// Draws a line from (x0, y0) to (x1, y1) using incremental calculation
void drawLineDDA(float x0, float y0, float x1, float y1) {
    float dx = x1 - x0;
    float dy = y1 - y0;
    
    // Calculate number of steps (use the larger of dx or dy)
    int steps = (int)max(abs(dx), abs(dy));
    
    // Calculate increment for each step
    float x_inc = dx / steps;
    float y_inc = dy / steps;
    
    float x = x0;
    float y = y0;
    
    //plots one by one
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2f(round(x), round(y));  // Round to nearest pixel
        x += x_inc;
        y += y_inc;
    }
    glEnd();
}

// Display callback - renders all graphics
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    glVertex2f(250, 250);
    glEnd();
    
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(GRID_WIDTH, 0);
    glEnd();
    
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(0, GRID_HEIGHT);
    glEnd();
    
    // Draw test lines using DDA algorithm
 
    glColor3f(1.0f, 0.0f, 1.0f);  // Magenta
    drawLineDDA(250, 50, 250, 450);
    
   
    
    glFlush();
    glutSwapBuffers();
}

// Reshape callback - sets up coordinate system
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, GRID_WIDTH, 0, GRID_HEIGHT);  // Set 2D orthographic view (0-500 on both axes)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



// Initialize OpenGL settings
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Black background
    glPointSize(2.0f);  // Set point size for pixels
    glLineWidth(1.0f);
}

int main(int argc, char** argv) {
    cout << "DDA Line Drawing Algorithm" << endl;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lab 2A - DDA Line Algorithm");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
   

    init();
    glutMainLoop();
    
    return 0;
}
