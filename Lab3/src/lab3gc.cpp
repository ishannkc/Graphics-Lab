// Lab3gc: Composite Transformation (Rotation + Scaling) - FreeGLUT

#include <GL/freeglut.h>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

static int winW = 900;
static int winH = 500;

// Triangle as 3x3 homogeneous matrix: columns are points
static double P[3][3];    // original
static double Rm[3][3];   // rotation
static double Sm[3][3];   // scaling
static double Cmp[3][3];  // composite = Sm x Rm
static double Pc[3][3];   // transformed = Cmp x P

static void printMat33(const char* title, const double M[3][3]) {
    cout << title << "\n";
    cout << fixed << setprecision(7);
    cout << "[[" << M[0][0] << "  " << M[0][1] << "  " << M[0][2] << "]\n";
    cout << " [" << M[1][0] << "  " << M[1][1] << "  " << M[1][2] << "]\n";
    cout << " [" << M[2][0] << "  " << M[2][1] << "  " << M[2][2] << "]]\n\n";
}

static void multiply3x3(const double A[3][3], const double B[3][3], double C[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            C[i][j] = 0.0;
            for (int k = 0; k < 3; ++k) C[i][j] += A[i][k] * B[k][j];
        }
    }
}

static void drawTriangle(const double M[3][3]) {
    glBegin(GL_TRIANGLES);
    for (int j = 0; j < 3; ++j) glVertex2d(M[0][j], M[1][j]);
    glEnd();
}

static void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Large blue triangle (original)
    glColor3f(0.2f, 0.2f, 1.0f);
    drawTriangle(P);

    // Small red triangle (rotated then scaled)
    glColor3f(1.0f, 0.2f, 0.2f);
    drawTriangle(Pc);

    glutSwapBuffers();
}

static void reshape(int w, int h) {
    winW = w; winH = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Room for slight negative x after rotation
    gluOrtho2D(-0.7, 1.7, -0.2, 1.2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    // Original triangle: (0,0), (1,0), (0.5,1)
    P[0][0] = 0.0; P[1][0] = 0.0; P[2][0] = 1.0;
    P[0][1] = 1.0; P[1][1] = 0.0; P[2][1] = 1.0;
    P[0][2] = 0.5; P[1][2] = 1.0; P[2][2] = 1.0;

    // Rotation: 60 degrees anticlockwise
    const double deg = 60.0;
    const double rad = deg * 3.14159265358979323846 / 180.0;
    const double c = cos(rad);
    const double s = sin(rad);
    Rm[0][0] =  c;  Rm[0][1] = -s; Rm[0][2] = 0.0;
    Rm[1][0] =  s;  Rm[1][1] =  c; Rm[1][2] = 0.0;
    Rm[2][0] = 0.0; Rm[2][1] = 0.0; Rm[2][2] = 1.0;

    // Scaling: 0.5 (uniform)
    const double sc = 0.5;
    Sm[0][0] = sc;  Sm[0][1] = 0.0; Sm[0][2] = 0.0;
    Sm[1][0] = 0.0; Sm[1][1] = sc;  Sm[1][2] = 0.0;
    Sm[2][0] = 0.0; Sm[2][1] = 0.0; Sm[2][2] = 1.0;

    // Composite = S × R (apply rotation first, then scaling)
    multiply3x3(Sm, Rm, Cmp);
    multiply3x3(Cmp, P, Pc);

    // Console output styled like the sample
    printMat33("Original Triangle Points (Homogeneous):", P);
    printMat33("Rotation Matrix (60\u00B0 anticlockwise):", Rm);
    printMat33("Scaling Matrix (0.5):", Sm);
    printMat33("Composite Matrix = S \u00D7 R:", Cmp);
    printMat33("Transformed Triangle Points = Composite \u00D7 P:", Pc);

    // GLUT window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("Lab3gc - Composite Transformation (R + S)");

    glClearColor(0.f, 0.f, 0.f, 1.f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
