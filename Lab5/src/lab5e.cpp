#include <GL/freeglut.h>
#include <algorithm>
#include <thread>
#include <mutex>
#include <atomic>
#include <iostream>
#include <string>
#include <cmath>

// Window size
static const int WIN_W = 800;
static const int WIN_H = 600;

// Animation state
static float z_pos = -4.0f;      // starting position (midpoint between near -2 and far -6)
static float z_target = -4.0f;   // target position initially same as start
static std::atomic<bool> animating{false};
static std::atomic<bool> requestExit{false};
static std::mutex stateMutex;

static void draw_cube()
{
    // Simple green square (front face) centered at origin
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-0.5f, -0.5f, 0.0f);
        glVertex3f( 0.5f, -0.5f, 0.0f);
        glVertex3f( 0.5f,  0.5f, 0.0f);
        glVertex3f(-0.5f,  0.5f, 0.0f);
    glEnd();
}

static void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 0.0,
              0.0, 0.0, -1.0,
              0.0, 1.0, 0.0);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, z_pos);
    draw_cube();
    glPopMatrix();

    glutSwapBuffers();
}

static void reshape(int w, int h)
{
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    const double aspect = (double)w / (double)h;
    gluPerspective(45.0, aspect, 0.1, 50.0);
}

static void idle()
{
    if (requestExit.load()) {
        glutLeaveMainLoop();
        return;
    }

    if (animating.load()) {
        // Step toward target smoothly
        float current;
        float target;
        {
            std::lock_guard<std::mutex> lk(stateMutex);
            current = z_pos;
            target = z_target;
        }

        const float step = 0.05f; // animation speed
        const float delta = target - current;

        if (std::abs(delta) <= step) {
            std::lock_guard<std::mutex> lk(stateMutex);
            z_pos = target;
            animating.store(false);
        } else {
            std::lock_guard<std::mutex> lk(stateMutex);
            z_pos += (delta > 0.0f ? step : -step);
        }

        glutPostRedisplay();
    }
}

static void consoleThread()
{
    std::cout << "\n===== Perspective Projection Controls =====\n";
    std::cout << "1: Move farther (smaller) to Z = -6.0\n";
    std::cout << "2: Move nearer  (bigger)  to Z = -2.0\n";
    std::cout << "ESC/q/exit: Quit\n";
    std::cout << "-----------------------------------------\n";

    std::string line;
    while (!requestExit.load()) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) {
            // End of input
            requestExit.store(true);
            break;
        }
        // Trim simple whitespace
        while (!line.empty() && (line.back()=='\r' || line.back()=='\n' || line.back()==' ')) line.pop_back();
        if (line == "1") {
            std::lock_guard<std::mutex> lk(stateMutex);
            z_target = -6.0f;
            animating.store(true);
        } else if (line == "2") {
            std::lock_guard<std::mutex> lk(stateMutex);
            z_target = -2.0f;
            animating.store(true);
        } else if (line == "q" || line == "Q" || line == "exit" || line == "ESC" || line == "esc") {
            requestExit.store(true);
        } else if (line.empty()) {
            // ignore
        } else {
            std::cout << "Unknown command: '" << line << "'\n";
        }
    }
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIN_W, WIN_H);
    glutCreateWindow("Animated Perspective Projection with Cube");

    // Basic GL state
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    // Start console control thread
    std::thread(consoleThread).detach();

    glutMainLoop();
    return 0;
}
