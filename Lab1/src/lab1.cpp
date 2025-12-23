#include <GL/glut.h>
#include <iostream>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 400;

// Draw letter 'I'
void drawI(float x, float y, float width, float height) {
    float barWidth = width * 0.3f;
    float centerX = x + width / 2.0f;
    
    // Top horizontal bar
    glBegin(GL_POLYGON);
    glVertex2f(x, y + height);
    glVertex2f(x + width, y + height);
    glVertex2f(x + width, y + height - barWidth);
    glVertex2f(x, y + height - barWidth);
    glEnd();
    
    // Vertical bar (center)
    glBegin(GL_POLYGON);
    glVertex2f(centerX - barWidth/2, y + height - barWidth);
    glVertex2f(centerX + barWidth/2, y + height - barWidth);
    glVertex2f(centerX + barWidth/2, y + barWidth);
    glVertex2f(centerX - barWidth/2, y + barWidth);
    glEnd();
    
    // Bottom horizontal bar
    glBegin(GL_POLYGON);
    glVertex2f(x, y + barWidth);
    glVertex2f(x + width, y + barWidth);
    glVertex2f(x + width, y);
    glVertex2f(x, y);
    glEnd();
}

// Draw letter 'S'
void drawS(float x, float y, float width, float height) {
    float barWidth = width * 0.25f;
    float midHeight = height / 2.0f;
    
    // Top horizontal bar
    glBegin(GL_POLYGON);
    glVertex2f(x, y + height);
    glVertex2f(x + width, y + height);
    glVertex2f(x + width, y + height - barWidth);
    glVertex2f(x, y + height - barWidth);
    glEnd();
    
    // Left vertical bar (top half)
    glBegin(GL_POLYGON);
    glVertex2f(x, y + height - barWidth);
    glVertex2f(x + barWidth, y + height - barWidth);
    glVertex2f(x + barWidth, y + midHeight);
    glVertex2f(x, y + midHeight);
    glEnd();
    
    // Middle horizontal bar
    glBegin(GL_POLYGON);
    glVertex2f(x, y + midHeight);
    glVertex2f(x + width, y + midHeight);
    glVertex2f(x + width, y + midHeight - barWidth);
    glVertex2f(x, y + midHeight - barWidth);
    glEnd();
    
    // Right vertical bar (bottom half)
    glBegin(GL_POLYGON);
    glVertex2f(x + width - barWidth, y + midHeight - barWidth);
    glVertex2f(x + width, y + midHeight - barWidth);
    glVertex2f(x + width, y + barWidth);
    glVertex2f(x + width - barWidth, y + barWidth);
    glEnd();
    
    // Bottom horizontal bar
    glBegin(GL_POLYGON);
    glVertex2f(x, y + barWidth);
    glVertex2f(x + width, y + barWidth);
    glVertex2f(x + width, y);
    glVertex2f(x, y);
    glEnd();
}

// Draw letter 'H'
void drawH(float x, float y, float width, float height) {
    float barWidth = width * 0.25f;
    float midHeight = height / 2.0f;
    
    // Left vertical bar
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + barWidth, y);
    glVertex2f(x + barWidth, y + height);
    glVertex2f(x, y + height);
    glEnd();
    
    // Middle horizontal bar
    glBegin(GL_POLYGON);
    glVertex2f(x + barWidth, y + midHeight - barWidth/2);
    glVertex2f(x + width - barWidth, y + midHeight - barWidth/2);
    glVertex2f(x + width - barWidth, y + midHeight + barWidth/2);
    glVertex2f(x + barWidth, y + midHeight + barWidth/2);
    glEnd();
    
    // Right vertical bar
    glBegin(GL_POLYGON);
    glVertex2f(x + width - barWidth, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x + width - barWidth, y + height);
    glEnd();
}

// Draw letter 'A'
void drawA(float x, float y, float width, float height) {
    float barWidth = width * 0.25f;
    float midHeight = height * 0.4f;
    
    // Left diagonal bar
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + barWidth * 1.2f, y);
    glVertex2f(x + width/2.0f, y + height);
    glVertex2f(x + width/2.0f - barWidth * 0.6f, y + height);
    glEnd();
    
    // Right diagonal bar
    glBegin(GL_POLYGON);
    glVertex2f(x + width - barWidth * 1.2f, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width/2.0f + barWidth * 0.6f, y + height);
    glVertex2f(x + width/2.0f, y + height);
    glEnd();
    
    // Middle horizontal bar
    glBegin(GL_POLYGON);
    glVertex2f(x + width * 0.25f, y + midHeight);
    glVertex2f(x + width * 0.75f, y + midHeight);
    glVertex2f(x + width * 0.7f, y + midHeight - barWidth);
    glVertex2f(x + width * 0.3f, y + midHeight - barWidth);
    glEnd();
    
    // Top triangle fill (to close the top)
    glBegin(GL_POLYGON);
    glVertex2f(x + width/2.0f - barWidth * 0.6f, y + height);
    glVertex2f(x + width/2.0f, y + height);
    glVertex2f(x + width/2.0f + barWidth * 0.6f, y + height);
    glVertex2f(x + width * 0.75f, y + midHeight);
    glVertex2f(x + width * 0.7f, y + midHeight);
    glVertex2f(x + width/2.0f, y + height - barWidth);
    glVertex2f(x + width * 0.3f, y + midHeight);
    glVertex2f(x + width * 0.25f, y + midHeight);
    glEnd();
}

// Draw letter 'N'
void drawN(float x, float y, float width, float height) {
    float barWidth = width * 0.25f;
    
    // Left vertical bar
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + barWidth, y);
    glVertex2f(x + barWidth, y + height);
    glVertex2f(x, y + height);
    glEnd();
    
    // Diagonal bar
    glBegin(GL_POLYGON);
    glVertex2f(x + barWidth, y + height);
    glVertex2f(x + barWidth * 1.5f, y + height);
    glVertex2f(x + width - barWidth * 0.5f, y);
    glVertex2f(x + width - barWidth, y);
    glEnd();
    
    // Right vertical bar
    glBegin(GL_POLYGON);
    glVertex2f(x + width - barWidth, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x + width - barWidth, y + height);
    glEnd();
}

// Display callback - renders all graphics
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Set color to dark red (similar to the image)
    glColor3f(0.55f, 0.0f, 0.0f);
    
    // Letter dimensions and spacing
    float letterHeight = 180.0f;
    float letterWidth = 100.0f;
    float spacing = 20.0f;
    float startX = 70.0f;
    float startY = 110.0f;
    
    // Draw "ISHAN"
    drawI(startX, startY, letterWidth, letterHeight);
    drawS(startX + letterWidth + spacing, startY, letterWidth, letterHeight);
    drawH(startX + 2 * (letterWidth + spacing), startY, letterWidth, letterHeight);
    drawA(startX + 3 * (letterWidth + spacing), startY, letterWidth, letterHeight);
    drawN(startX + 4 * (letterWidth + spacing), startY, letterWidth, letterHeight);
    
    glFlush();
    glutSwapBuffers();
}

// Reshape callback - sets up coordinate system
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Initialize OpenGL settings
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Black background
}

int main(int argc, char** argv) {
    cout << "Lab 1 - Name Drawing with OpenGL" << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lab 1 - ISHAN");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    
    init();
    glutMainLoop();
    
    return 0;
}
