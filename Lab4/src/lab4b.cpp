// Lab4b: Liang–Barsky Line Clipping (FreeGLUT)

#include <GL/freeglut.h>
#include <iostream>
#include <algorithm>
using namespace std;

static int winW = 1000;
static int winH = 600;

// Axis-aligned clip window (rectangle)
static double xminW = 100.0, yminW = 80.0;
static double xmaxW = 760.0, ymaxW = 420.0;

// A diagonal line (top-left to bottom-right), like the sample
static double x1L = 5.0,   y1L = 595.0;
static double x2L = 995.0, y2L = 5.0;

// Result of clipping
static bool clipOK = false;
static double cx1 = 0, cy1 = 0, cx2 = 0, cy2 = 0;

static bool liangBarsky(double x1, double y1, double x2, double y2,
                        double &ox1, double &oy1, double &ox2, double &oy2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;

    double p[4] = { -dx,  dx, -dy,  dy };
    double q[4] = { x1 - xminW, xmaxW - x1, y1 - yminW, ymaxW - y1 };

    double u1 = 0.0, u2 = 1.0;

    for (int i = 0; i < 4; ++i) {
        double pi = p[i];
        double qi = q[i];

        if (pi == 0) {
            if (qi < 0) return false; // parallel and outside
            else continue;            // parallel and inside – no change
        }

        double u = qi / pi;
        if (pi < 0) {
            // entering
            u1 = max(u1, u);
        } else {
            // leaving
            u2 = min(u2, u);
        }
        if (u1 > u2) return false; // reject early
    }

    ox1 = x1 + u1 * dx; oy1 = y1 + u1 * dy;
    ox2 = x1 + u2 * dx; oy2 = y1 + u2 * dy;
    return true;
}

static void drawRect(double xmn, double ymn, double xmx, double ymx) {
    glBegin(GL_LINE_LOOP);
    glVertex2d(xmn, ymn);
    glVertex2d(xmx, ymn);
    glVertex2d(xmx, ymx);
    glVertex2d(xmn, ymx);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping window (light blue)
    glColor3f(0.3f, 0.6f, 0.9f);
    glLineWidth(1.5f);
    drawRect(xminW, yminW, xmaxW, ymaxW);

    // Draw original line in red
    glColor3f(0.8f, 0.2f, 0.2f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2d(x1L, y1L);
    glVertex2d(x2L, y2L);
    glEnd();

    // Draw clipped segment in green
    if (clipOK) {
        glColor3f(0.2f, 0.9f, 0.2f);
        glLineWidth(2.5f);
        glBegin(GL_LINES);
        glVertex2d(cx1, cy1);
        glVertex2d(cx2, cy2);
        glEnd();
    }

    glutSwapBuffers();
}

void reshape(int w, int h) {
    winW = w; winH = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    cout << "Liang Barsky Line Clipping\n";
    cout << "Clip window: [xmin=" << xminW << ", ymin=" << yminW
         << ", xmax=" << xmaxW << ", ymax=" << ymaxW << "]\n";
    cout << "Original line: (" << x1L << ", " << y1L << ") -> ("
         << x2L << ", " << y2L << ")\n";

    clipOK = liangBarsky(x1L, y1L, x2L, y2L, cx1, cy1, cx2, cy2);
    if (clipOK) {
        cout << "Result: ACCEPTED\n";
        cout << "Visible segment: (" << cx1 << ", " << cy1 << ") -> ("
             << cx2 << ", " << cy2 << ")\n";
    } else {
        cout << "Result: REJECTED (line lies outside window)\n";
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("Lab4b - Liang Barsky Line Clipping");

    glClearColor(0.f, 0.f, 0.f, 1.f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
