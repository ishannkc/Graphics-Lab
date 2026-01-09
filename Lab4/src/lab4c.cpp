// Lab4c: Sutherland–Hodgman Polygon Clipping (FreeGLUT)

#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Pt { double x, y; };

static int winW = 1000;
static int winH = 600;

// Clip rectangle bounds
static double xminW = 140.0, yminW = 140.0;
static double xmaxW = 900.0, ymaxW = 440.0;

// Original polygon (a skewed quadrilateral around the window)
static vector<Pt> poly = {
    {  30.0,  30.0}, // bottom-left outside
    { 100.0, 560.0}, // left side outside
    { 980.0, 560.0}, // top-right outside
    { 930.0,  60.0}  // bottom-right outside
};

static vector<Pt> clipped; // result

enum Edge { LEFT=0, RIGHT=1, BOTTOM=2, TOP=3 };

static inline bool inside(const Pt& p, Edge e) {
    switch (e) {
        case LEFT:   return p.x >= xminW;
        case RIGHT:  return p.x <= xmaxW;
        case BOTTOM: return p.y >= yminW;
        case TOP:    return p.y <= ymaxW;
    }
    return false;
}

static Pt intersect(const Pt& p1, const Pt& p2, Edge e) {
    Pt r{p1.x, p1.y};
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    switch (e) {
        case LEFT: {
            double t = (xminW - p1.x) / dx;
            r.x = xminW; r.y = p1.y + t * dy; break;
        }
        case RIGHT: {
            double t = (xmaxW - p1.x) / dx;
            r.x = xmaxW; r.y = p1.y + t * dy; break;
        }
        case BOTTOM: {
            double t = (yminW - p1.y) / dy;
            r.y = yminW; r.x = p1.x + t * dx; break;
        }
        case TOP: {
            double t = (ymaxW - p1.y) / dy;
            r.y = ymaxW; r.x = p1.x + t * dx; break;
        }
    }
    return r;
}

static vector<Pt> clipAgainstEdge(const vector<Pt>& in, Edge e) {
    vector<Pt> out;
    if (in.empty()) return out;
    Pt S = in.back();
    for (const Pt& E : in) {
        bool Ein = inside(E, e);
        bool Sin = inside(S, e);
        if (Ein) {
            if (!Sin) out.push_back(intersect(S, E, e));
            out.push_back(E);
        } else {
            if (Sin) out.push_back(intersect(S, E, e));
        }
        S = E;
    }
    return out;
}

static vector<Pt> suthHodgClip(const vector<Pt>& polygon) {
    vector<Pt> out = polygon;
    out = clipAgainstEdge(out, LEFT);
    out = clipAgainstEdge(out, RIGHT);
    out = clipAgainstEdge(out, BOTTOM);
    out = clipAgainstEdge(out, TOP);
    return out;
}

static void drawRect(double xmn, double ymn, double xmx, double ymx) {
    glBegin(GL_LINE_LOOP);
    glVertex2d(xmn, ymn);
    glVertex2d(xmx, ymn);
    glVertex2d(xmx, ymx);
    glVertex2d(xmn, ymx);
    glEnd();
}

static void drawPolygon(const vector<Pt>& P) {
    if (P.empty()) return;
    glBegin(GL_LINE_LOOP);
    for (const auto& v : P) glVertex2d(v.x, v.y);
    glEnd();
}

static void printPoly(const char* title, const vector<Pt>& P) {
    cout << title << " (" << P.size() << " pts)\n";
    cout << fixed << setprecision(2);
    for (size_t i = 0; i < P.size(); ++i) {
        cout << i << ": (" << P[i].x << ", " << P[i].y << ")\n";
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Clip window (yellow)
    glColor3f(1.0f, 1.0f, 0.3f);
    glLineWidth(1.2f);
    drawRect(xminW, yminW, xmaxW, ymaxW);

    // Original polygon (red)
    glColor3f(0.9f, 0.2f, 0.2f);
    glLineWidth(1.0f);
    drawPolygon(poly);

    // Clipped polygon (green, thicker)
    if (!clipped.empty()) {
        glColor3f(0.2f, 0.9f, 0.2f);
        glLineWidth(2.0f);
        drawPolygon(clipped);
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
    cout << "Sutherland Hodgman Polygon Clipping\n";
    cout << "Clip window: [xmin=" << xminW << ", ymin=" << yminW
         << ", xmax=" << xmaxW << ", ymax=" << ymaxW << "]\n";
    printPoly("Original polygon:", poly);

    clipped = suthHodgClip(poly);
    if (clipped.empty()) cout << "Result: REJECTED (empty polygon)\n";
    else { cout << "Result: ACCEPTED\n"; printPoly("Clipped polygon:", clipped); }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("Lab4c - Sutherland Hodgman Polygon Clipping");

    glClearColor(0.f, 0.f, 0.f, 1.f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
