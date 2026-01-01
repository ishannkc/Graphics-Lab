// Lab3c: 2D Rotation (FreeGLUT)
// Simple: print matrices and draw original + rotated triangle

#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;

static int winW = 1000;
static int winH = 600;

// Triangle as 3x3 homogeneous matrix: columns are points
// [ x1 x2 x3 ; y1 y2 y3 ; 1 1 1 ]
static double P[3][3];       // original triangle
static double R[3][3];       // rotation matrix
static double PR[3][3];      // rotated triangle = R x P

static void printMat3(const char* title, const double M[3][3]) {
    cout << title << "\n";
    cout << scientific << setprecision(8);
    cout << "[[" << M[0][0] << " " << M[0][1] << " " << M[0][2] << "]\n";
    cout << " [" << M[1][0] << " " << M[1][1] << " " << M[1][2] << "]\n";
    cout << " [" << M[2][0] << " " << M[2][1] << " " << M[2][2] << "]]\n\n";
}

static void drawTriangle(const double M[3][3]) {
    glBegin(GL_TRIANGLES);
    for (int j = 0; j < 3; ++j) {
        glVertex2d(M[0][j], M[1][j]);
    }
    glEnd();
}

static void drawTriangleOutline(const double M[3][3]) {
    glBegin(GL_LINE_LOOP);
    for (int j = 0; j < 3; ++j) {
        glVertex2d(M[0][j], M[1][j]);
    }
    glEnd();
}

static void multiply3x3(const double A[3][3], const double B[3][3], double C[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            C[i][j] = 0.0;
            for (int k = 0; k < 3; ++k) C[i][j] += A[i][k] * B[k][j];
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw at the same position (no translation):
    // original as blue outline, rotated as solid red
    glLineWidth(3.0f);
    glColor3f(0.2f, 0.2f, 1.0f);
    drawTriangleOutline(P);

    glColor3f(1.0f, 0.2f, 0.2f);
    drawTriangle(PR);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    winW = w; winH = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // View that comfortably contains the triangles at origin
    gluOrtho2D(-10.0, 10.0, -8.0, 8.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



int main(int argc, char** argv) {
    // Original upright triangle with a shared origin vertex
    P[0][0] = 0.0; P[1][0] = 0.0; P[2][0] = 1.0; // (0,0,1)
    P[0][1] = 4.0; P[1][1] = 0.0; P[2][1] = 1.0; // (4,0,1)
    P[0][2] = 2.0; P[1][2] = 3.0; P[2][2] = 1.0; // (2,3,1)

    // Rotation angle (clockwise)
    double angleDeg = 60.0;               // matches reference caption
    const double PI = 3.14159265358979323846;
    double theta = angleDeg * PI / 180.0;
    double c = cos(theta);
    double s = sin(theta);

    // Clockwise rotation matrix in homogeneous coords
    R[0][0] = c;  R[0][1] = s;  R[0][2] = 0.0;
    R[1][0] = -s; R[1][1] = c;  R[1][2] = 0.0;
    R[2][0] = 0.0;R[2][1] = 0.0;R[2][2] = 1.0;

    multiply3x3(R, P, PR);

    // Terminal output like the reference
    printMat3("Original Triangle Points (Homogeneous):", P);
    printMat3("Rotation Matrix (60° clockwise):", R);
    printMat3("Rotated Triangle Points = R × P:", PR);

    // GLUT window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("Lab3c - 2D Rotation");

    glClearColor(0.f, 0.f, 0.f, 1.f);
    glDisable(GL_POINT_SMOOTH);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
  

    glutMainLoop();
    return 0;
}
