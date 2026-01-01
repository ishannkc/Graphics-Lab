// Lab3e: 2D Reflection about X-axis (FreeGLUT)
// Simple: print matrices and draw original + reflected triangle

#include <GL/freeglut.h>
#include <iostream>
#include <iomanip>
using namespace std;

static int winW = 1000;
static int winH = 600;

// Triangle as 3x3 homogeneous matrix: columns are points
// [ x1 x2 x3 ; y1 y2 y3 ; 1 1 1 ]
static double P[3][3];    // original triangle
static double Rx[3][3];   // reflection about X-axis
static double PR[3][3];   // reflected triangle = Rx x P

static void printMat3(const char* title, const double M[3][3]) {
    cout << title << "\n";
    cout << scientific << setprecision(8);
    cout << "[[" << M[0][0] << " " << M[0][1] << " " << M[0][2] << "]\n";
    cout << " [" << M[1][0] << " " << M[1][1] << " " << M[1][2] << "]\n";
    cout << " [" << M[2][0] << " " << M[2][1] << " " << M[2][2] << "]]\n\n";
}

static void multiply3x3(const double A[3][3], const double B[3][3], double C[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            C[i][j] = 0.0;
            for (int k = 0; k < 3; ++k) C[i][j] += A[i][k] * B[k][j];
        }
    }
}

static void drawAxes() {
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    glVertex2d(-10.0, 0.0); glVertex2d(10.0, 0.0);  // X-axis
    glVertex2d(0.0, -8.0);  glVertex2d(0.0, 8.0);   // Y-axis
    glEnd();
}

static void drawTriangleFilled(const double M[3][3]) {
    glBegin(GL_TRIANGLES);
    for (int j = 0; j < 3; ++j) glVertex2d(M[0][j], M[1][j]);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();

    glColor3f(0.2f, 0.2f, 1.0f); // original in blue (upper)
    drawTriangleFilled(P);

    glColor3f(1.0f, 0.2f, 0.2f); // reflected in red (lower)
    drawTriangleFilled(PR);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    winW = w; winH = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10.0, 10.0, -8.0, 8.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int, int) {
    if (key == 27 /* ESC */) glutLeaveMainLoop();
}

int main(int argc, char** argv) {
    // Put original triangle in first quadrant similar to the image
    // Columns: (2,2,1), (3,2,1), (2.5,3,1)
    P[0][0] = 2.0;  P[1][0] = 2.0;  P[2][0] = 1.0;
    P[0][1] = 3.0;  P[1][1] = 2.0;  P[2][1] = 1.0;
    P[0][2] = 2.5;  P[1][2] = 3.0;  P[2][2] = 1.0;

    // Reflection about X-axis: y -> -y
    Rx[0][0]=1; Rx[0][1]=0; Rx[0][2]=0;
    Rx[1][0]=0; Rx[1][1]=-1;Rx[1][2]=0;
    Rx[2][0]=0; Rx[2][1]=0; Rx[2][2]=1;

    multiply3x3(Rx, P, PR);

    // Terminal output like the reference
    printMat3("Original Triangle Points:", P);
    printMat3("Reflection Matrix about X-axis:", Rx);
    printMat3("Reflected Triangle Points = Rx × P:", PR);

    // GLUT window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("Lab3e - 2D Reflection (X-axis)");

    glClearColor(0.f, 0.f, 0.f, 1.f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
