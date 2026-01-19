// Lab5c: 3D Scaling (Homogeneous) — FreeGLUT + OpenGL

#include <GL/freeglut.h>
#include <iostream>
#include <iomanip>
using namespace std;

// Window size
static int WIN_W = 900;
static int WIN_H = 600;

// Cube position
static float pos[3] = { 0.0f, 0.0f, -3.0f };

// Current scale factor (starts at 1.0)
static float scaleFactor = 1.0f;

// Scale change per frame
static const float SCALE_SPEED = 0.005f;

// Maximum scale factor (stop before touching window edges)
static const float MAX_SCALE = 1.5f;

// Print scaling matrix to console
static void printScalingMatrix(float sx, float sy, float sz) {
    cout << "Scaling Matrix (3D Homogeneous):\n";
    cout << fixed << setprecision(3);
    cout << "[ " << setw(6) << sx << "  0.000  0.000  0.000 ]\n";
    cout << "[ 0.000  " << setw(6) << sy << "  0.000  0.000 ]\n";
    cout << "[ 0.000  0.000  " << setw(6) << sz << "  0.000 ]\n";
    cout << "[ 0.000  0.000  0.000  1.000 ]\n\n";
}

static void tick(int) {
    if (scaleFactor < MAX_SCALE) {
        scaleFactor += SCALE_SPEED;
        if (scaleFactor > MAX_SCALE) {
            scaleFactor = MAX_SCALE;
        }
    }
    
    glutPostRedisplay();
    glutTimerFunc(10, tick, 0);
}


// Draw a simple wireframe cube (like in reference images)
static void drawCube() {
    const float s = 0.5f;  // half-size of cube
    
    // Draw cube as wireframe (GL_LINE style)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glBegin(GL_QUADS);
    
    // Front face (red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-s, -s,  s);
    glVertex3f( s, -s,  s);
    glVertex3f( s,  s,  s);
    glVertex3f(-s,  s,  s);
    
    // Back face (cyan)
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-s, -s, -s);
    glVertex3f(-s,  s, -s);
    glVertex3f( s,  s, -s);
    glVertex3f( s, -s, -s);
    
    // Right face (green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f( s, -s, -s);
    glVertex3f( s,  s, -s);
    glVertex3f( s,  s,  s);
    glVertex3f( s, -s,  s);
    
    // Left face (yellow)
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-s, -s, -s);
    glVertex3f(-s, -s,  s);
    glVertex3f(-s,  s,  s);
    glVertex3f(-s,  s, -s);
    
    // Top face (blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-s,  s, -s);
    glVertex3f(-s,  s,  s);
    glVertex3f( s,  s,  s);
    glVertex3f( s,  s, -s);
    
    // Bottom face (magenta)
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-s, -s, -s);
    glVertex3f( s, -s, -s);
    glVertex3f( s, -s,  s);
    glVertex3f(-s, -s,  s);
    
    glEnd();
}

static void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Set up camera
    gluLookAt(0.0, 0.0, 0.0,    // eye position
              0.0, 0.0, -3.0,   // look at point
              0.0, 1.0, 0.0);   // up vector
    
    // Move cube to position
    glTranslatef(pos[0], pos[1], pos[2]);
    
    // Apply uniform scaling
    glScalef(scaleFactor, scaleFactor, scaleFactor);
    
    drawCube();
    
    glutSwapBuffers();
}

static void reshape(int w, int h) {
    WIN_W = w;
    WIN_H = h;
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double aspect = (h == 0) ? 1.0 : (double)w / (double)h;
    gluPerspective(45.0, aspect, 0.1, 10.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


static void keyboard(unsigned char key, int, int) {
    switch (key) {
        case 'p':
        case 'P':
            // Print current scaling matrix
            printScalingMatrix(scaleFactor, scaleFactor, scaleFactor);
            break;
        case 'r':
        case 'R':
            // Reset scale
            scaleFactor = 1.0f;
            cout << "Scale reset to 1.0\n\n";
            break;
        case 27:  // ESC key
            glutLeaveMainLoop();
            break;
    }
}

int main(int argc, char** argv) {
    // Print header
    cout << "=== Lab5c: 3D Scaling (Homogeneous) ===\n\n";
    cout << "Starting Position: [" << pos[0] << ", " << pos[1] << ", " << pos[2] << "]\n";
    cout << "Initial Scale Factor: " << scaleFactor << "\n\n";
    
    // Print initial scaling matrix
    printScalingMatrix(scaleFactor, scaleFactor, scaleFactor);
    
    cout << "Controls:\n";
    cout << "  Press P to print current scaling matrix\n";
    cout << "  Press R to reset scale\n";
    cout << "  Press ESC to exit\n\n";
    
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIN_W, WIN_H);
    glutCreateWindow("3D Scaling Homogeneous");
    
    // Set background color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    // Register callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(10, tick, 0);
    
    // Start main loop
    glutMainLoop();
    
    return 0;
}
