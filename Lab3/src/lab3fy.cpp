// Lab3fy: 2D Shearing (Y-shear)


#include <GL/freeglut.h>
#include <iostream>
#include <iomanip>
using namespace std;

static int winW = 1000;
static int winH = 600;

// Rectangle as 3x4 homogeneous matrix: columns are points
// [ x1 x2 x3 x4 ; y1 y2 y3 y4 ; 1 1 1 1 ]
static double P[3][4];    // original rectangle
static double Shy[3][3];  // Y-shear matrix
static double PS[3][4];   // sheared rectangle = Shy x P

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

    // Y-sheared rectangle in red (overlay)
    glColor3f(1.0f, 0.2f, 0.2f);
    drawQuadFilled(PS);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    winW = w; winH = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // View centered at origin, plenty of room for y-shear
    gluOrtho2D(-2.0, 6.0, -1.5, 6.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int main(int argc, char** argv) {
    // Original rectangle with points: (0,0), (2,0), (2,1), (0,1)
    P[0][0] = 0.0; P[1][0] = 0.0; P[2][0] = 1.0;
    P[0][1] = 2.0; P[1][1] = 0.0; P[2][1] = 1.0;
    P[0][2] = 2.0; P[1][2] = 1.0; P[2][2] = 1.0;
    P[0][3] = 0.0; P[1][3] = 1.0; P[2][3] = 1.0;

    // Y-shear: x' = x, y' = y + shy * x
    double shy = 1.0; // visible shear similar to sample
    Shy[0][0] = 1.0; Shy[0][1] = 0.0; Shy[0][2] = 0.0;
    Shy[1][0] = shy; Shy[1][1] = 1.0; Shy[1][2] = 0.0;
    Shy[2][0] = 0.0; Shy[2][1] = 0.0; Shy[2][2] = 1.0;

    multiply3x3_3x4(Shy, P, PS);

    // Terminal output in the requested style
    printMat34("Original Rectangle Points (Homogeneous):", P);
    printMat33("Y-axis Shear Matrix:", Shy);
    printMat34("Sheared Rectangle Points = Shear_y × P:", PS);

    // GLUT window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("Lab3fy - 2D Shearing (Y)");

    glClearColor(0.f, 0.f, 0.f, 1.f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);


    glutMainLoop();
    return 0;
}
