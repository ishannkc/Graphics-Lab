// Lab3fx: 2D Shearing (X-shear) - FreeGLUT
// Simple: print matrices like the sample and draw original + sheared rectangle

#include <GL/freeglut.h>
#include <iostream>
#include <iomanip>
using namespace std;

static int winW = 1000;
static int winH = 600;

// Rectangle as 3x4 homogeneous matrix: columns are points
// [ x1 x2 x3 x4 ; y1 y2 y3 y4 ; 1 1 1 1 ]
static double P[3][4];    // original rectangle
static double Sh[3][3];   // X-shear matrix
static double PS[3][4];   // sheared rectangle = Sh x P

static void printMat34(const char* title, const double M[3][4]) {
    cout << title << "\n";
    cout << scientific << setprecision(8);
    cout << "[[" << M[0][0] << " " << M[0][1] << " " << M[0][2] << " " << M[0][3] << "]\n";
    cout << " [" << M[1][0] << " " << M[1][1] << " " << M[1][2] << " " << M[1][3] << "]\n";
    cout << " [" << M[2][0] << " " << M[2][1] << " " << M[2][2] << " " << M[2][3] << "]]\n\n";
}

static void printMat33(const char* title, const double M[3][3]) {
    cout << title << "\n";
    cout << scientific << setprecision(8);
    cout << "[[" << M[0][0] << " " << M[0][1] << " " << M[0][2] << "]\n";
    cout << " [" << M[1][0] << " " << M[1][1] << " " << M[1][2] << "]\n";
    cout << " [" << M[2][0] << " " << M[2][1] << " " << M[2][2] << "]]\n\n";
}

static void multiply3x3_3x4(const double A[3][3], const double B[3][4], double C[3][4]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            C[i][j] = 0.0;
            for (int k = 0; k < 3; ++k) C[i][j] += A[i][k] * B[k][j];
        }
    }
}

static void drawQuadFilled(const double M[3][4]) {
    glBegin(GL_QUADS);
    for (int j = 0; j < 4; ++j) glVertex2d(M[0][j], M[1][j]);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Original rectangle in blue
    glColor3f(0.2f, 0.2f, 1.0f);
    drawQuadFilled(P);

    // Sheared rectangle in red (overlay)
    glColor3f(1.0f, 0.2f, 0.2f);
    drawQuadFilled(PS);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    winW = w; winH = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // View centered at origin, plenty of room for shear
    gluOrtho2D(-2.0, 6.0, -1.5, 4.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int, int) {
    if (key == 27 /* ESC */) glutLeaveMainLoop();
}

int main(int argc, char** argv) {
    // Original rectangle with points: (0,0), (2,0), (2,1), (0,1)
    P[0][0] = 0.0; P[1][0] = 0.0; P[2][0] = 1.0;
    P[0][1] = 2.0; P[1][1] = 0.0; P[2][1] = 1.0;
    P[0][2] = 2.0; P[1][2] = 1.0; P[2][2] = 1.0;
    P[0][3] = 0.0; P[1][3] = 1.0; P[2][3] = 1.0;

    // X-shear: x' = x + shx * y, y' = y
    double shx = 1.0; // visible shear similar to sample
    Sh[0][0] = 1.0; Sh[0][1] = shx; Sh[0][2] = 0.0;
    Sh[1][0] = 0.0; Sh[1][1] = 1.0; Sh[1][2] = 0.0;
    Sh[2][0] = 0.0; Sh[2][1] = 0.0; Sh[2][2] = 1.0;

    multiply3x3_3x4(Sh, P, PS);

    // Terminal output in the requested style
    printMat34("Original Rectangle Points (Homogeneous):", P);
    printMat33("Shear Matrix (X-shear):", Sh);
    printMat34("Sheared Rectangle Points = Shear × P:", PS);

    // GLUT window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("Lab3fx - 2D Shearing (X)");

    glClearColor(0.f, 0.f, 0.f, 1.f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
