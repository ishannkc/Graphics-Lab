// Lab4a: Cohen–Sutherland Line Clipping (FreeGLUT)

#include <GL/freeglut.h>
#include <iostream>
using namespace std;

// Window size
static int winW = 1000;
static int winH = 600;

// Clipping rectangle (window)
static double xminW = 40.0, yminW = 40.0;
static double xmaxW = 700.0, ymaxW = 420.0;

// Original line segment endpoints
static double x1L = 120.0, y1L = 90.0;
static double x2L = 760.0, y2L = 520.0;

// Codes for the Cohen–Sutherland regions
enum {
    CS_LEFT   = 1,   // 0001
    CS_RIGHT  = 2,   // 0010
    CS_BOTTOM = 4,   // 0100
    CS_TOP    = 8    // 1000
};

static inline int computeCode(double x, double y) {
    int code = 0;
    if (x < xminW) code |= CS_LEFT;
    else if (x > xmaxW) code |= CS_RIGHT;
    if (y < yminW) code |= CS_BOTTOM;
    else if (y > ymaxW) code |= CS_TOP;
    return code;
}

// Result of clipping (cached once for drawing and printed to terminal)
static bool clipOK = false;
static double cx1 = 0, cy1 = 0, cx2 = 0, cy2 = 0;

static bool cohenSutherlandClip(double x1, double y1, double x2, double y2,
                                double &ox1, double &oy1, double &ox2, double &oy2)
{
    int c1 = computeCode(x1, y1);
    int c2 = computeCode(x2, y2);

    while (true) {
        if ((c1 | c2) == 0) {
            // Trivially accept
            ox1 = x1; oy1 = y1; ox2 = x2; oy2 = y2; return true;
        }
        if (c1 & c2) {
            // Trivially reject
            return false;
        }

        int c_out = c1 ? c1 : c2;
        double x = 0.0, y = 0.0;

        if (c_out & CS_TOP) {
            x = x1 + (x2 - x1) * (ymaxW - y1) / (y2 - y1);
            y = ymaxW;
        } else if (c_out & CS_BOTTOM) {
            x = x1 + (x2 - x1) * (yminW - y1) / (y2 - y1);
            y = yminW;
        } else if (c_out & CS_RIGHT) {
            y = y1 + (y2 - y1) * (xmaxW - x1) / (x2 - x1);
            x = xmaxW;
        } else { // CS_LEFT
            y = y1 + (y2 - y1) * (xminW - x1) / (x2 - x1);
            x = xminW;
        }

        if (c_out == c1) {
            x1 = x; y1 = y; c1 = computeCode(x1, y1);
        } else {
            x2 = x; y2 = y; c2 = computeCode(x2, y2);
        }
    }
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

    // Draw original line in red (whole line)
    glColor3f(0.8f, 0.2f, 0.2f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2d(x1L, y1L);
    glVertex2d(x2L, y2L);
    glEnd();

    // Draw clipped (visible) segment in green, thicker
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
    // Pixel-like coordinates with origin at bottom-left
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    // Compute clipping once and log to terminal
    cout << "Cohen–Sutherland Line Clipping\n";
    cout << "Clip window: [xmin=" << xminW << ", ymin=" << yminW
         << ", xmax=" << xmaxW << ", ymax=" << ymaxW << "]\n";
    cout << "Original line: (" << x1L << ", " << y1L << ") -> ("
         << x2L << ", " << y2L << ")\n";

    clipOK = cohenSutherlandClip(x1L, y1L, x2L, y2L, cx1, cy1, cx2, cy2);
    if (clipOK) {
        cout << "Result: ACCEPTED\n";
        cout << "Visible segment: (" << cx1 << ", " << cy1 << ") -> ("
             << cx2 << ", " << cy2 << ")\n";
    } else {
        cout << "Result: REJECTED (line lies outside window)\n";
    }

    // Set up GLUT window for visualization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("Lab4 - Cohen Sutherland Line Clipping");

    glClearColor(0.f, 0.f, 0.f, 1.f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
