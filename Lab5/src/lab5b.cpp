// Lab5b: 3D Rotation (Homogeneous) — FreeGLUT + OpenGL

#include <GL/freeglut.h>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Window size
static int WIN_W = 900;
static int WIN_H = 600;

// Cube position (fixed at origin for rotation demo)
static float pos[3] = { 0.0f, 0.0f, -3.0f };

// Current rotation angle (degrees)
static float angle = 0.0f;

// Rotation axis: 1 = X-axis, 2 = Y-axis, 3 = Z-axis
static int rotationAxis = 2;  // Default: Y-axis

// Rotation speed (degrees per frame)
static const float ROTATION_SPEED = 0.5f;

// Pi constant
static const double PI = 3.14159265358979323846;

// Print rotation matrix to console
static void printRotationMatrix(float angleDeg, int axis) {
    double rad = angleDeg * PI / 180.0;
    double c = cos(rad);
    double s = sin(rad);
    
    cout << "Rotation Matrix (around ";
    if (axis == 1) cout << "X-axis";
    else if (axis == 2) cout << "Y-axis";
    else cout << "Z-axis";
    cout << " by " << fixed << setprecision(1) << angleDeg << " degrees):\n";
    
    cout << fixed << setprecision(3);
    
    if (axis == 1) {  // X-axis rotation
        cout << "[ 1.000  0.000  0.000  0.000 ]\n";
        cout << "[ 0.000 " << setw(6) << c << " " << setw(6) << -s << "  0.000 ]\n";
        cout << "[ 0.000 " << setw(6) << s << " " << setw(6) << c << "  0.000 ]\n";
        cout << "[ 0.000  0.000  0.000  1.000 ]\n";
    }
    else if (axis == 2) {  // Y-axis rotation
        cout << "[ " << setw(6) << c << "  0.000 " << setw(6) << s << "  0.000 ]\n";
        cout << "[ 0.000  1.000  0.000  0.000 ]\n";
        cout << "[ " << setw(6) << -s << "  0.000 " << setw(6) << c << "  0.000 ]\n";
        cout << "[ 0.000  0.000  0.000  1.000 ]\n";
    }
    else {  // Z-axis rotation
        cout << "[ " << setw(6) << c << " " << setw(6) << -s << "  0.000  0.000 ]\n";
        cout << "[ " << setw(6) << s << " " << setw(6) << c << "  0.000  0.000 ]\n";
        cout << "[ 0.000  0.000  1.000  0.000 ]\n";
        cout << "[ 0.000  0.000  0.000  1.000 ]\n";
    }
    cout << "\n";
}
static void tick(int) {
    angle += ROTATION_SPEED;

    if (angle >= 360.0f) {
        angle -= 360.0f;
    }
    
    glutPostRedisplay();
    glutTimerFunc(10, tick, 0);  
}


// Draw a simple colored cube
static void drawCube() {
    const float s = 0.5f;  // half-size of cube
    
    glBegin(GL_QUADS);
    
    // Front face (yellow) - matches reference image
    glColor3f(1.0f, 1.0f, 0.0f);
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
    
    // Right face (red) - matches reference image
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f( s, -s, -s);
    glVertex3f( s,  s, -s);
    glVertex3f( s,  s,  s);
    glVertex3f( s, -s,  s);
    
    // Left face (green)
    glColor3f(0.0f, 1.0f, 0.0f);
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
    
    // Set up camera looking at origin from a distance
    gluLookAt(0.0, 0.0, 0.0,    // eye position
              0.0, 0.0, -3.0,   // look at point
              0.0, 1.0, 0.0);   // up vector
    
    // Move cube to position
    glTranslatef(pos[0], pos[1], pos[2]);
    
    // Apply rotation based on selected axis
    if (rotationAxis == 1) {
        glRotatef(angle, 1.0f, 0.0f, 0.0f);  // X-axis
    }
    else if (rotationAxis == 2) {
        glRotatef(angle, 0.0f, 1.0f, 0.0f);  // Y-axis
    }
    else {
        glRotatef(angle, 0.0f, 0.0f, 1.0f);  // Z-axis
    }
    
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
        case '1':
            rotationAxis = 1;
            cout << "Switched to X-axis rotation\n";
            printRotationMatrix(angle, rotationAxis);
            break;
        case '2':
            rotationAxis = 2;
            cout << "Switched to Y-axis rotation\n";
            printRotationMatrix(angle, rotationAxis);
            break;
        case '3':
            rotationAxis = 3;
            cout << "Switched to Z-axis rotation\n";
            printRotationMatrix(angle, rotationAxis);
            break;
        case 27:  // ESC key
            glutLeaveMainLoop();
            break;
    }
}

int main(int argc, char** argv) {
    // Print menu
    cout << "=== Lab5b: 3D Rotation (Homogeneous) ===\n\n";
    cout << "Choose rotation axis:\n";
    cout << "1: X-axis\n";
    cout << "2: Y-axis\n";
    cout << "3: Z-axis\n\n";
    cout << "Enter 1, 2, or 3: ";
    
    int choice;
    cin >> choice;
    
    if (choice == 1) {
        rotationAxis = 1;
        cout << "\nSelected: X-axis rotation\n";
    }
    else if (choice == 3) {
        rotationAxis = 3;
        cout << "\nSelected: Z-axis rotation\n";
    }
    else {
        rotationAxis = 2;  // Default to Y-axis
        cout << "\nSelected: Y-axis rotation (default)\n";
    }
    
    cout << "\nStarting Position: [" << pos[0] << ", " << pos[1] << ", " << pos[2] << "]\n";
    cout << "Initial angle: " << angle << " degrees\n\n";
    
    printRotationMatrix(0.0f, rotationAxis);
    
    cout << "Controls:\n";
    cout << "  Press 1, 2, 3 to change rotation axis\n";
    cout << "  Press ESC to exit\n\n";
    
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIN_W, WIN_H);
    glutCreateWindow("Lab5b - 3D Rotation (Homogeneous)");
    
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
