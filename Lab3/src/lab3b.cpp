// Lab3b: 2D Translation (FreeGLUT)
// Very simple demo that prints the math and draws two squares

#include <GL/freeglut.h>
#include <iostream>
#include <iomanip>
using namespace std;

static int winW = 800;
static int winH = 600;

struct Vec3 { double x, y, w; };

static Vec3 P;      // original point (homogeneous)
static Vec3 P2;     // translated point (homogeneous)
static double T[3][3];

static void printVector(const Vec3 &v) {
    // Format similar to the reference image
    cout << "[[" << setw(2) << (int)v.x << "]\n";
    cout << "[" << setw(2) << (int)v.y << "]\n";
    cout << "[" << setw(2) << (int)v.w << "]]\n\n";
}

static void printMatrix(const double M[3][3]) {
    cout << "[[" << (int)M[0][0] << ' ' << (int)M[0][1] << ' ' << (int)M[0][2] << "]\n";
    cout << "["  << (int)M[1][0] << ' ' << (int)M[1][1] << ' ' << (int)M[1][2] << "]\n";
    cout << "["  << (int)M[2][0] << ' ' << (int)M[2][1] << ' ' << (int)M[2][2] << "]]\n\n";
}

static Vec3 applyTranslation(const double M[3][3], const Vec3 &v) {
    Vec3 r{};
    r.x = M[0][0]*v.x + M[0][1]*v.y + M[0][2]*v.w;
    r.y = M[1][0]*v.x + M[1][1]*v.y + M[1][2]*v.w;
    r.w = M[2][0]*v.x + M[2][1]*v.y + M[2][2]*v.w;
    return r;
}

static void drawSquare(double cx, double cy, double half) {
    glBegin(GL_QUADS);
    glVertex2d(cx - half, cy - half);
    glVertex2d(cx + half, cy - half);
    glVertex2d(cx + half, cy + half);
    glVertex2d(cx - half, cy + half);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // original (blue)
    glColor3f(0.1f, 0.2f, 1.0f);
    drawSquare(P.x, P.y, 1.5);

    // translated (green)
    glColor3f(0.2f, 1.0f, 0.2f);
    drawSquare(P2.x, P2.y, 1.5);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    winW = w; winH = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // World coords: simple range that shows -10..10 on both axes
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int main(int argc, char** argv) {
    // Example from the reference output
    P = {0, -3, 1};

    // Translation by (tx, ty) = (0, 5)
    T[0][0]=1; T[0][1]=0; T[0][2]=0;
    T[1][0]=0; T[1][1]=1; T[1][2]=5;
    T[2][0]=0; T[2][1]=0; T[2][2]=1;

    P2 = applyTranslation(T, P);

    // Print to terminal like the sample
    cout << "Original Position (Homogeneous):\n";
    printVector(P);

    cout << "Translation Matrix:\n";
    printMatrix(T);

    cout << "Translated Position = Translation \u00D7 Original:\n"; // × sign
    printVector(P2);

    // Setup GLUT window and draw squares at those positions
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("Lab3b - 2D Translation");

    glClearColor(0.f, 0.f, 0.f, 1.f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
