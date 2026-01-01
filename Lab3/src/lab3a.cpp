// Lab3a: Midpoint Ellipse (FreeGLUT)


#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
using namespace std;

static int winW = 800;
static int winH = 600;

// Plot the 4-way symmetric points for an ellipse
static inline void plotEllipsePoints(int cx, int cy, int x, int y) {
    glVertex2i(cx + x, cy + y);
    glVertex2i(cx - x, cy + y);
    glVertex2i(cx + x, cy - y);
    glVertex2i(cx - x, cy - y);
}

// Midpoint ellipse algorithm
void drawEllipseMidpoint(int cx, int cy, int rx, int ry) {
    long rx2 = 1L * rx * rx;     // rx^2
    long ry2 = 1L * ry * ry;     // ry^2
    long twoRx2 = 2L * rx2;
    long twoRy2 = 2L * ry2;

    int x = 0;
    int y = ry;

    long dx = 0;                 // 2*ry^2*x
    long dy = twoRx2 * y;        // 2*rx^2*y

    // Decision parameter for region 1
    long d1 = ry2 - rx2 * ry + (rx2 / 4);

    // Region 1: slope > -1 (dx < dy)
    while (dx < dy) {
        plotEllipsePoints(cx, cy, x, y);

        if (d1 < 0) {
            x++;
            dx += twoRy2;
            d1 += dx + ry2;
        } else {
            x++;
            y--;
            dx += twoRy2;
            dy -= twoRx2;
            d1 += dx - dy + ry2;
        }
    }

    // Decision parameter for region 2
    long d2 = (ry2 * (long)(x + 0.5) * (long)(x + 0.5)) +
              (rx2 * (long)(y - 1) * (long)(y - 1)) -
              (rx2 * ry2);

    // Region 2: slope <= -1 (y >= 0)
    while (y >= 0) {
        plotEllipsePoints(cx, cy, x, y);

        if (d2 > 0) {
            y--;
            dy -= twoRx2;
            d2 += rx2 - dy;
        } else {
            y--;
            x++;
            dx += twoRy2;
            dy -= twoRx2;
            d2 += dx + rx2 - dy;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.2f, 0.2f); // red-ish points
    glPointSize(2.0f);

    glBegin(GL_POINTS);
    // Example ellipse: center in window, rx=220, ry=140
    int cx = winW / 2;
    int cy = winH / 2;
    int rx = 220;
    int ry = 140;
    drawEllipseMidpoint(cx, cy, rx, ry);
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    winW = w; winH = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Simple pixel coordinate system (origin at bottom-left)
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("Lab3a - Midpoint Ellipse");

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // black background

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);


    glutMainLoop();
    return 0;
}
