

#include <iostream>
#include <cmath>
#include <vector>

#include "Point.hpp"
#include "Vector.hpp"
#include "Scene.hpp"

#include "Camera.hpp"
#include "3D/Grid.hpp"


#include <GL/glut.h>

#define WIDTH  1200
#define HEIGHT 1000

#define RED   1
#define GREEN 0
#define BLUE  0
#define ALPHA 1

#define KEY_ESC 27

// Entêtes de fonctions
void init_scene();
void render_TP1();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);
GLvoid keyboard_up(unsigned char key, int x, int y);
GLvoid keyboard_down(unsigned char key, int x, int y);
GLvoid window_mouse(int button, int state, int x, int y);
GLvoid window_mouseMotion(int x, int y);
GLvoid window_passiveMouseMotion(int x, int y);

Scene* scene;
Camera camera;


int main(int argc, char* argv[]) {
    // initialisation  des paramètres de GLUT en fonction
    // des arguments sur la ligne de commande
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);

    // définition et création de la fenêtre graphique, ainsi que son titre
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("GraphViewer");

    glewInit();

    // initialisation de OpenGL et de la scène
    initGL();

    scene = new Scene(std::string(argv[1]));

    // choix des procédures de callback pour
    // le tracé graphique
    glutDisplayFunc(&window_display);
    // le redimensionnement de la fenêtre
    glutReshapeFunc(&window_reshape);
    // la gestion des événements clavier
    glutKeyboardFunc(&window_key);
    glutKeyboardUpFunc(&keyboard_up);
    //glutKeyboardDownFunc(&keyboard_down);
    // la gestion des événements souris
    glutMouseFunc(&window_mouse);
    glutMotionFunc(&window_mouseMotion);
    glutPassiveMotionFunc(&window_passiveMouseMotion);

    // la boucle prinicipale de gestion des événements utilisateur
    glutMainLoop();

    return 1;
}

// initialisation du fond de la fenêtre graphique : noir opaque
GLvoid initGL() {
    glClearColor(RED, GREEN, BLUE, ALPHA);
    glPointSize(5.0);
    glLineWidth(2.0);
    glEnable(GL_DEPTH_TEST);
    /*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
}

GLvoid window_display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    camera.update(1);

    render_scene();

    // trace la scène grapnique qui vient juste d'être définie
    glFlush();
}

// fonction de call-back pour le redimensionnement de la fenêtre

GLvoid window_reshape(GLsizei width, GLsizei height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60, width / height, 1.0, 1000.0);

    glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y) {
    switch (key) {
    case KEY_ESC:
        delete scene;
        exit(1);
        break;
    default:
        scene->keyboard(key);
        break;
    }
    camera.window_key(key, true);

    window_display();
}

GLvoid keyboard_up(unsigned char key, int x, int y) {
    camera.window_key(key, false);
}
GLvoid keyboard_down(unsigned char key, int x, int y) {
    camera.window_key(key, true);
}

GLvoid window_mouse(int button, int state, int x, int y) {
    scene->mouseEvent(button, state, x, y);
    window_display();
}

GLvoid window_mouseMotion(int x, int y) {
    camera.setMouse(x, y);
    window_display();
}

GLvoid window_passiveMouseMotion(int x, int y) {
    camera.setMouse(x, y);
    window_display();
}

void drawPoint(const Point& p) {
    p.draw();
}

void drawLine(const Point& p1, const Point& p2) {
    p1.drawLine(p2);
}

void render_scene() {
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(10.0, 0.0, 0.0);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 10.0, 0.0);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 10.0);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);

    scene->draw(true);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0.0, 0.0, 0.0);
    scene->draw(false);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
