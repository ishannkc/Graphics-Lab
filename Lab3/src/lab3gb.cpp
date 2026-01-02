// Lab3gb: Composite Transformation (Translation + Rotation) - FreeGLUT

#include <GL/freeglut.h>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

static int winW = 800;
static int winH = 800;

// Triangle as 3x3 homogeneous matrix: columns are points
static double P[3][3];     // original triangle
static double Tm[3][3];    // translation matrix
static double Rm[3][3];    // rotation matrix (anticlockwise)
static double Cmp[3][3];   // composite = Rm x Tm
static double Pc[3][3];    // transformed = Cmp x P

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

    // Original triangle (blue)
    glColor3f(0.2f, 0.2f, 1.0f);
    drawTriangle(P);

    // Transformed triangle (red)
    glColor3f(1.0f, 0.2f, 0.2f);
    drawTriangle(Pc);

    glutSwapBuffers();
}

static void reshape(int w, int h) {
    winW = w; winH = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Include a bit of negative X so the rotated triangle (x' ~ -1.7..-0.6) is visible
    gluOrtho2D(-2.0, 10.0, 0.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    // Original triangle points: (0,0), (1,0), (0.5,1)
    P[0][0] = 0.0; P[1][0] = 0.0; P[2][0] = 1.0;
    P[0][1] = 1.0; P[1][1] = 0.0; P[2][1] = 1.0;
    P[0][2] = 0.5; P[1][2] = 1.0; P[2][2] = 1.0;

    // Translation by (3,3)
    Tm[0][0] = 1.0; Tm[0][1] = 0.0; Tm[0][2] = 3.0;
    Tm[1][0] = 0.0; Tm[1][1] = 1.0; Tm[1][2] = 3.0;
    Tm[2][0] = 0.0; Tm[2][1] = 0.0; Tm[2][2] = 1.0;

    // Rotation 60 degrees anticlockwise about origin
    const double deg = 60.0;
    const double rad = deg * 3.14159265358979323846 / 180.0;
    const double c = cos(rad);
    const double s = sin(rad);
    Rm[0][0] =  c;  Rm[0][1] = -s; Rm[0][2] = 0.0;
    Rm[1][0] =  s;  Rm[1][1] =  c; Rm[1][2] = 0.0;
    Rm[2][0] = 0.0; Rm[2][1] = 0.0; Rm[2][2] = 1.0;

    // Composite and transformed
    multiply3x3(Rm, Tm, Cmp);   // R × T -> apply T then R
    multiply3x3(Cmp, P, Pc);    // Pc = Cmp × P

    // Console output mirroring the example
    printMat33("Original Triangle Points (Homogeneous):", P);
    printMat33("Translation Matrix:", Tm);
    printMat33("Rotation Matrix (60° anticlockwise):", Rm);
    printMat33("Composite Transformation Matrix (R × T):", Cmp);
    printMat33("Transformed Triangle Points = Composite × P:", Pc);

    // GLUT window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("Lab3gb - Composite Transformation (T + R)");

    glClearColor(0.f, 0.f, 0.f, 1.f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
