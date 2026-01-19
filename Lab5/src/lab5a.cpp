// Lab5a: 3D Translation (Homogeneous) — FreeGLUT + OpenGL

#include <GL/freeglut.h>
#include <iostream>
#include <iomanip>
using namespace std;

// Window size
static int WIN_W = 900;
static int WIN_H = 600;

// Homogeneous position p = [x, y, z, 1]^T
// Start at bottom-left corner where cube is fully visible
static double pos[4] = { -1.2, -0.9, -3.0, 1.0 };

// Flag to stop translation once cube reaches center
static bool reachedCenter = false;

// Translation matrix (each frame we apply this once):
// [ 1 0 0 tx ]
// [ 0 1 0 ty ]
// [ 0 0 1 tz ]
// [ 0 0 0  1 ]
static double T[4][4];

// Small step per frame (roughly matches the Python reference)
static const double tx = 0.004;
static const double ty = 0.003;
static const double tz = 0.002;

static void printMat44(const char* title, const double M[4][4]) {
	cout << title << "\n";
	cout << fixed << setprecision(3);
	for (int i = 0; i < 4; ++i) {
		cout << "[ ";
		for (int j = 0; j < 4; ++j) {
			cout << setw(7) << M[i][j] << (j == 3 ? " " : " ");
		}
		cout << "]\n";
	}
	cout << "\n";
}

static void applyTranslation(double P[4], const double M[4][4]) {
	double r[4] = {0,0,0,0};
	for (int i = 0; i < 4; ++i) {
		for (int k = 0; k < 4; ++k) r[i] += M[i][k] * P[k];
	}
	for (int i = 0; i < 4; ++i) P[i] = r[i];
}

static void drawCube() {
	const float s = 0.25f; // half-size (smaller cube)
	glBegin(GL_QUADS);
	// +X face (red)
	glColor3f(1.0f, 0.2f, 0.2f);
	glVertex3f( s, -s, -s); glVertex3f( s,  s, -s); glVertex3f( s,  s,  s); glVertex3f( s, -s,  s);
	// -X face (green)
	glColor3f(0.2f, 1.0f, 0.2f);
	glVertex3f(-s, -s, -s); glVertex3f(-s, -s,  s); glVertex3f(-s,  s,  s); glVertex3f(-s,  s, -s);
	// +Y face (blue)
	glColor3f(0.2f, 0.2f, 1.0f);
	glVertex3f(-s,  s, -s); glVertex3f(-s,  s,  s); glVertex3f( s,  s,  s); glVertex3f( s,  s, -s);
	// -Y face (magenta)
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-s, -s, -s); glVertex3f( s, -s, -s); glVertex3f( s, -s,  s); glVertex3f(-s, -s,  s);
	// +Z face (cyan)
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-s, -s,  s); glVertex3f( s, -s,  s); glVertex3f( s,  s,  s); glVertex3f(-s,  s,  s);
	// -Z face (yellow)
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-s, -s, -s); glVertex3f(-s,  s, -s); glVertex3f( s,  s, -s); glVertex3f( s, -s, -s);
	glEnd();
}

static void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Simple camera looking down -Z from origin
	gluLookAt(0.0, 0.0, 0.0,
			  0.0, 0.0, -3.0,
			  0.0, 1.0, 0.0);

	// Apply translation to the cube's model matrix
	glTranslatef((GLfloat)pos[0], (GLfloat)pos[1], (GLfloat)pos[2]);
	drawCube();

	glutSwapBuffers();
}

static void reshape(int w, int h) {
	WIN_W = w; WIN_H = h;
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const double aspect = (h == 0) ? 1.0 : (double)w / (double)h;
	gluPerspective(45.0, aspect, 0.1, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void tick(int) {
    // Each tick: p' = T * p (only if not yet at center)
    if (!reachedCenter) {
        applyTranslation(pos, T);
        // Stop when cube reaches a bit past center for better 3D view
        if (pos[0] >= 0.4 && pos[1] >= 0.3) {
            pos[0] = 0.4;
            pos[1] = 0.3;
            reachedCenter = true;
            cout << "Cube reached target position. Translation stopped.\n";
        }
    }
	glutPostRedisplay();
	glutTimerFunc(16, tick, 0); // ~60 FPS
}

static void key(unsigned char k, int, int) {
	if (k == 27) { // ESC to quit
		glutLeaveMainLoop();
	}
}

int main(int argc, char** argv) {
	// Build the translation matrix once
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			T[i][j] = (i == j) ? 1.0 : 0.0;
	T[0][3] = tx; T[1][3] = ty; T[2][3] = tz;

	cout << "Starting Position: [" << pos[0] << ", " << pos[1]
		 << ", " << pos[2] << ", " << pos[3] << "]\n";
	printMat44("Translation Matrix (4x4):", T);

	// GLUT window setup
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WIN_W, WIN_H);
	glutCreateWindow("Lab5a - 3D Translation (Homogeneous)");

	glClearColor(0.f, 0.f, 0.f, 1.f);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutTimerFunc(0, tick, 0);

	glutMainLoop();
	return 0;
}

