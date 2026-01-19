// Lab5d - 3D Shearing (FreeGLUT + OpenGL)
// Simple, humanized demo: a colored cube slowly shears over time.
// Window title: "3D Shearing Homogeneous" (matches the reference)

#include <GL/glut.h>

static const int WIN_W = 800;
static const int WIN_H = 600;
static const float TARGET_SHEAR = 0.5f; // stop animating at this value

// Position of the cube in the scene (X, Y, Z)
static float pos[3] = {0.0f, 0.0f, -3.0f};
// Shear factor that we animate every frame
static float shearFactor = 0.0f;

static void drawCube()
{
    const float s = 0.5f; // half-size

    // Front face (Green) — matches the "before" reference look
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-s, -s,  s);
        glVertex3f( s, -s,  s);
        glVertex3f( s,  s,  s);
        glVertex3f(-s,  s,  s);
    glEnd();

    // Left face (Blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex3f(-s, -s, -s);
        glVertex3f(-s, -s,  s);
        glVertex3f(-s,  s,  s);
        glVertex3f(-s,  s, -s);
    glEnd();

    // Top face (Cyan)
    glColor3f(0.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex3f(-s,  s,  s);
        glVertex3f( s,  s,  s);
        glVertex3f( s,  s, -s);
        glVertex3f(-s,  s, -s);
    glEnd();

    // Other faces — darker, so the three colored faces stand out
    glColor3f(0.1f, 0.1f, 0.1f);
    // Back
    glBegin(GL_QUADS);
        glVertex3f(-s, -s, -s);
        glVertex3f( s, -s, -s);
        glVertex3f( s,  s, -s);
        glVertex3f(-s,  s, -s);
    glEnd();
    // Right
    glBegin(GL_QUADS);
        glVertex3f( s, -s,  s);
        glVertex3f( s, -s, -s);
        glVertex3f( s,  s, -s);
        glVertex3f( s,  s,  s);
    glEnd();
    // Bottom
    glBegin(GL_QUADS);
        glVertex3f(-s, -s, -s);
        glVertex3f( s, -s, -s);
        glVertex3f( s, -s,  s);
        glVertex3f(-s, -s,  s);
    glEnd();
}

static void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 0.0,
              0.0, 0.0, -3.0,
              0.0, 1.0, 0.0);

  
    const float m[16] = {
        // Column 0
        1.0f, 0.0f, shearFactor, 0.0f,
        // Column 1
        shearFactor, 1.0f, 0.0f, 0.0f,
        // Column 2
        0.0f, 0.0f, 1.0f, 0.0f,
        // Column 3
        0.0f, 0.0f, 0.0f, 1.0f
    };
    glTranslatef(pos[0], pos[1], pos[2]);
    glRotatef(-25.0f, 0.0f, 1.0f, 0.0f); // yaw
    glRotatef(15.0f, 1.0f, 0.0f, 0.0f);  // pitch
    glMultMatrixf(m);

    drawCube();

    glutSwapBuffers();
}

static void idle()
{
    if (shearFactor < TARGET_SHEAR) {
        shearFactor += 0.001f;
        if (shearFactor > TARGET_SHEAR) shearFactor = TARGET_SHEAR;
        glutPostRedisplay();
    } else {
        glutIdleFunc(nullptr);
    }
}

static void reshape(int w, int h)
{
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    const double aspect = static_cast<double>(w) / static_cast<double>(h);
    gluPerspective(45.0, aspect, 0.1, 10.0);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIN_W, WIN_H);
    glutCreateWindow("3D Shearing Homogeneous");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Set up an initial projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, static_cast<double>(WIN_W) / static_cast<double>(WIN_H), 0.1, 10.0);
    glMatrixMode(GL_MODELVIEW);

    // Event hooks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    // Start the loop
    glutMainLoop();
    return 0;
}
