#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PI = 3.14159265f;

// Pie chart data structure
struct SliceData {
    float value;
    float r, g, b;  // RGB color
    const char* label;
};

// Sample pie chart data
vector<SliceData> slices = {
    {30, 1.0f, 0.0f, 0.0f, "Slice 1"},  // Red - 30%
    {25, 0.0f, 1.0f, 0.0f, "Slice 2"},  // Green - 25%
    {20, 0.0f, 0.0f, 1.0f, "Slice 3"},  // Blue - 20%
    {15, 1.0f, 1.0f, 0.0f, "Slice 4"},  // Yellow - 15%
    {10, 1.0f, 0.0f, 1.0f, "Slice 5"}   // Magenta - 10%
};

// Draw a pie slice
void drawPieSlice(float centerX, float centerY, float radius, 
                  float startAngle, float endAngle, 
                  float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    
    // Center point
    glVertex2f(centerX, centerY);
    
    // Draw vertices from start angle to end angle
    int numSegments = 50;
    for (int i = 0; i <= numSegments; i++) {
        float angle = startAngle + (endAngle - startAngle) * i / numSegments;
        float x = centerX + radius * cos(angle * PI / 180.0f);
        float y = centerY + radius * sin(angle * PI / 180.0f);
        glVertex2f(x, y);
    }
    
    glEnd();
}

// Draw pie chart
void drawPieChart() {
    float centerX = WINDOW_WIDTH / 2;
    float centerY = WINDOW_HEIGHT / 2;
    float radius = 150.0f;
    
    // Calculate total value
    float totalValue = 0;
    for (const auto& slice : slices) {
        totalValue += slice.value;
    }
    
    // Draw each slice
    float currentAngle = 0;
    for (const auto& slice : slices) {
        float sliceAngle = (slice.value / totalValue) * 360.0f;
        drawPieSlice(centerX, centerY, radius, currentAngle, 
                     currentAngle + sliceAngle, slice.r, slice.g, slice.b);
        currentAngle += sliceAngle;
    }
    
    // Draw pie chart border
    glColor3f(1.0f, 1.0f, 1.0f);  // White
    glBegin(GL_LINE_LOOP);
    int numSegments = 100;
    for (int i = 0; i < numSegments; i++) {
        float angle = (360.0f / numSegments) * i;
        float x = centerX + radius * cos(angle * PI / 180.0f);
        float y = centerY + radius * sin(angle * PI / 180.0f);
        glVertex2f(x, y);
    }
    glEnd();
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw pie chart
    drawPieChart();
    
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
    cout << "Lab 2E - Pie Chart Visualization" << endl;
    cout << "Displaying pie chart with 5 slices:" << endl;
    for (const auto& slice : slices) {
        cout << "  " << slice.label << ": " << slice.value << "%" << endl;
    }
   
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lab 2E - Pie Chart");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
   
    
    init();
    glutMainLoop();
    
    return 0;
}
