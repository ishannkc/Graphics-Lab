#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int PADDING = 80;

// Sample data points for the line graph
vector<float> dataPoints = {50, 100, 80, 150, 120, 180, 140, 200, 170, 160};

// DDA Line Drawing Algorithm
void drawLineDDA(float x0, float y0, float x1, float y1) {
    float dx = x1 - x0;
    float dy = y1 - y0;
    int steps = (int)max(abs(dx), abs(dy));
    
    float x_inc = dx / steps;
    float y_inc = dy / steps;
    
    float x = x0;
    float y = y0;
    
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2f(round(x), round(y));
        x += x_inc;
        y += y_inc;
    }
    glEnd();
}

// Display callback - renders the line graph
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Calculate scaling factors
    float graphWidth = WINDOW_WIDTH - 2 * PADDING;
    float graphHeight = WINDOW_HEIGHT - 2 * PADDING;
    float maxDataValue = 200.0f;
    
    // Draw line graph using DDA
    glColor3f(0.0f, 1.0f, 1.0f);  // Cyan
    glPointSize(2.0f);
    
    for (int i = 0; i < dataPoints.size() - 1; i++) {
        // Calculate screen coordinates
        float x0 = PADDING + (i * graphWidth) / (dataPoints.size() - 1);
        float y0 = PADDING + (dataPoints[i] / maxDataValue) * graphHeight;
        
        float x1 = PADDING + ((i + 1) * graphWidth) / (dataPoints.size() - 1);
        float y1 = PADDING + (dataPoints[i + 1] / maxDataValue) * graphHeight;
        
        // Draw line using DDA
        drawLineDDA(x0, y0, x1, y1);
    }
    
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
    cout << "Lab 2D - Line Graph using DDA Algorithm" << endl;
    cout << "Displays a line graph of sample data points" << endl;
    cout << "Data: ";
    for (int i = 0; i < dataPoints.size(); i++) {
        cout << dataPoints[i];
        if (i < dataPoints.size() - 1) cout << ", ";
    }
    cout << endl;
    cout << "Press ESC to exit" << endl;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lab 2D - Line Graph using DDA");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    
    init();
    glutMainLoop();
    
    return 0;
}
