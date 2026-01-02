// Lab3gd: Composite Transformation (Translation + X-Shearing) - FreeGLUT

#include <GL/freeglut.h>
#include <iostream>
#include <iomanip>
using namespace std;

static int winW = 900;
static int winH = 500;

// Triangle as 3x3 homogeneous matrix: columns are points
static double P[3][3];     // original triangle
static double Tm[3][3];    // translation matrix
static double Shx[3][3];   // x-shear matrix
static double Cmp[3][3];   // composite = Shx × Tm
static double Pc[3][3];    // transformed = Cmp × P

static void printMat33(const char* title, const double M[3][3]) {
    cout << title << "\n";
    cout << fixed << setprecision(1);
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

    // Original triangle (blue) at bottom-left
    glColor3f(0.2f, 0.2f, 1.0f);
    drawTriangle(P);

    // Transformed triangle (red) towards right
    glColor3f(1.0f, 0.2f, 0.2f);
    drawTriangle(Pc);

    glutSwapBuffers();
}

static void reshape(int w, int h) {
    winW = w; winH = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Show both original and translated+sheared triangle
    gluOrtho2D(0.0, 8.0, 0.0, 5.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    // Original triangle points: (0,0), (1,0), (0.5,1)
    P[0][0] = 0.0; P[1][0] = 0.0; P[2][0] = 1.0;
    P[0][1] = 1.0; P[1][1] = 0.0; P[2][1] = 1.0;
    P[0][2] = 0.5; P[1][2] = 1.0; P[2][2] = 1.0;

    // Translation (tx, ty) = (2, 2)
    Tm[0][0] = 1.0; Tm[0][1] = 0.0; Tm[0][2] = 2.0;
    Tm[1][0] = 0.0; Tm[1][1] = 1.0; Tm[1][2] = 2.0;
    Tm[2][0] = 0.0; Tm[2][1] = 0.0; Tm[2][2] = 1.0;

    // X-shearing with shx = 1.0 -> x' = x + y
    const double shx = 1.0;
    Shx[0][0] = 1.0; Shx[0][1] = shx; Shx[0][2] = 0.0;
    Shx[1][0] = 0.0; Shx[1][1] = 1.0; Shx[1][2] = 0.0;
    Shx[2][0] = 0.0; Shx[2][1] = 0.0; Shx[2][2] = 1.0;

    // Composite = Shx × T (apply translation first, then shear)
    multiply3x3(Shx, Tm, Cmp);
    multiply3x3(Cmp, P, Pc);

    // Console output matching the sample format
    printMat33("Original Triangle Points (Homogeneous):", P);
    printMat33("Translation Matrix (3,3):", Tm); // label mirrors screenshot
    printMat33("X-Shearing Matrix:", Shx);
    printMat33("Composite Matrix = Shx × T:", Cmp);
    printMat33("Transformed Triangle Points = Composite × P:", Pc);

    // GLUT window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("Lab3gd - Composite Transformation (T + X-shear)");

    glClearColor(0.f, 0.f, 0.f, 1.f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
