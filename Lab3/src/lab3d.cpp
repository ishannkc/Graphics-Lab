// Lab3d: 2D Scaling (FreeGLUT)
// Simple program that prints scaling math and draws original + scaled square

#include <GL/freeglut.h>
#include <iostream>
#include <iomanip>
using namespace std;

static int winW = 1000;
static int winH = 600;

// Square as 3x4 homogeneous matrix: columns are points
// [ x1 x2 x3 x4 ; y1 y2 y3 y4 ; 1 1 1 1 ]
static double P[3][4];    // original square
static double S[3][3];    // scaling matrix
static double PS[3][4];   // scaled square = S x P

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

static void drawSquareFilled(const double M[3][4]) {
    glBegin(GL_QUADS);
    for (int j = 0; j < 4; ++j) {
        glVertex2d(M[0][j], M[1][j]);
    }
    glEnd();
}

static void drawSquareOutline(const double M[3][4]) {
    glBegin(GL_LINE_LOOP);
    for (int j = 0; j < 4; ++j) {
        glVertex2d(M[0][j], M[1][j]);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw at the same position (no translation):
    // original as blue outline, scaled as filled green
    glLineWidth(3.0f);
    glColor3f(0.2f, 0.2f, 1.0f);
    drawSquareOutline(P);

    glColor3f(0.2f, 1.0f, 0.2f);
    drawSquareFilled(PS);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    winW = w; winH = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // View centered at origin, fits original + scaled square comfortably
    gluOrtho2D(-10.0, 10.0, -8.0, 8.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



int main(int argc, char** argv) {
    // Define a square centered at origin for pure scaling (no translation)
    // Order: (-2,-2), (2,-2), (2,2), (-2,2)
    P[0][0] = -2.0; P[1][0] = -2.0; P[2][0] = 1.0;
    P[0][1] =  2.0; P[1][1] = -2.0; P[2][1] = 1.0;
    P[0][2] =  2.0; P[1][2] =  2.0; P[2][2] = 1.0;
    P[0][3] = -2.0; P[1][3] =  2.0; P[2][3] = 1.0;

    // Scaling factors (clearly visible): sx = 1.5, sy = 0.7
    double sx = 1.5, sy = 0.7;
    S[0][0] = sx; S[0][1] = 0.0; S[0][2] = 0.0;
    S[1][0] = 0.0; S[1][1] = sy; S[1][2] = 0.0;
    S[2][0] = 0.0; S[2][1] = 0.0; S[2][2] = 1.0;

    multiply3x3_3x4(S, P, PS);

    // Terminal output similar to earlier labs/images
    printMat34("Original Square Points (Homogeneous):", P);
    printMat33("Scaling Matrix:", S);
    printMat34("Scaled Square Points = S × P:", PS);

    // GLUT window setup
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("Lab3d - 2D Scaling");

    glClearColor(0.f, 0.f, 0.f, 1.f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
 

    glutMainLoop();
    return 0;
}
