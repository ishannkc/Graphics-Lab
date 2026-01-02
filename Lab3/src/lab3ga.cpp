// Lab3ga: Composite Transformation (Translation + Scaling) - FreeGLUT

#include <GL/freeglut.h>
#include <iostream>
#include <iomanip>
using namespace std;

static int winW = 800;
static int winH = 800;

// 3 points of a triangle, homogeneous columns [x;y;1]
static double P[3][3];        // original triangle
static double Tm[3][3];       // translation matrix
static double Sm[3][3];       // scaling matrix
static double Cmp[3][3];      // composite = Sm x Tm
static double Pc[3][3];       // transformed = Cmp x P

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

    // Original triangle (blue) bottom-left
    glColor3f(0.2f, 0.2f, 1.0f);
    drawTriangle(P);

    // Transformed triangle (red) top-right
    glColor3f(1.0f, 0.2f, 0.2f);
    drawTriangle(Pc);

    glutSwapBuffers();
}

static void reshape(int w, int h) {
    winW = w; winH = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Match the simple 0..10 coordinate range seen in sample
    gluOrtho2D(0.0, 10.0, 0.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    // Original triangle points: (0,0), (1,0), (0.5,1)
    P[0][0] = 0.0; P[1][0] = 0.0; P[2][0] = 1.0;
    P[0][1] = 1.0; P[1][1] = 0.0; P[2][1] = 1.0;
    P[0][2] = 0.5; P[1][2] = 1.0; P[2][2] = 1.0;

    // Translation by (tx, ty) = (3, 3)
    Tm[0][0] = 1.0; Tm[0][1] = 0.0; Tm[0][2] = 3.0;
    Tm[1][0] = 0.0; Tm[1][1] = 1.0; Tm[1][2] = 3.0;
    Tm[2][0] = 0.0; Tm[2][1] = 0.0; Tm[2][2] = 1.0;

    // Uniform scaling by s = 2.0
    Sm[0][0] = 2.0; Sm[0][1] = 0.0; Sm[0][2] = 0.0;
    Sm[1][0] = 0.0; Sm[1][1] = 2.0; Sm[1][2] = 0.0;
    Sm[2][0] = 0.0; Sm[2][1] = 0.0; Sm[2][2] = 1.0;

    // Composite S x T, then apply to P
    multiply3x3(Sm, Tm, Cmp);
    multiply3x3(Cmp, P, Pc);

    // Terminal output in the requested style
    printMat33("Original Triangle Points (Homogeneous):", P);
    printMat33("Translation Matrix:", Tm);
    printMat33("Scaling Matrix (2x):", Sm);
    printMat33("Composite Transformation Matrix (S × T):", Cmp);
    printMat33("Transformed Triangle Points = Composite × P:", Pc);

    // GLUT window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("Lab3ga - Composite Transformation (T + S)");

    glClearColor(0.f, 0.f, 0.f, 1.f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
