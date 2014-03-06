#include <iostream>
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "Gate.hpp"
#include "Node.hpp"
#include "Graph.hpp"
#include "Viewer/GraphViewer.hpp"

#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 800

void initSDL();
void reshape(int w, int h);
void initGL();

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    initSDL();
    initGL();

    Graph g;
    Node* node1 = new Node{&g};
    Id nid1 = g.addNode(node1);

    Node* node2 = new Node{&g};
    Id nid2 = g.addNode(node2);

    Gate* g1 = new Gate{&g, nid1, nid2};
    Id gid1 = g.addGate(g1);

    Gate* g2 = new Gate{&g, 1, nid2};
    Id gid2 = g.addGate(g2);

    GraphViewer gw{&g};

    bool running = true;
    SDL_Event event;
    while (running) {
        SDL_WaitEvent(&event);
        // On traite l'évènement
        switch (event.type) {
            case SDL_QUIT:
                // On a fermé la fenetre
                running = false;
                break;
            case SDL_VIDEORESIZE:
                reshape(event.resize.w, event.resize.h);
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
                break;
            default:
                gw.postEvent(event);
                break;
        }
        // On met à jour
        gw.update(0);
        // On dessine
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        gw.draw();
        SDL_GL_SwapBuffers();
    }

    SDL_Quit();
    return 0;
}

void initSDL() {
    SDL_Init(SDL_INIT_VIDEO);

    if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) == -1) {
       throw std::runtime_error("Impossible d'activer le double buffer\n");
    }

    SDL_WM_SetCaption("Graph generator", NULL);

    if (SDL_SetVideoMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32, SDL_OPENGL | SDL_RESIZABLE) == NULL) {
        throw std::runtime_error("Impossible de passer en mode OpenGL."/*, SDL_GetError()*/);
    }
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	if (SDL_SetVideoMode(w, h, 32, SDL_OPENGL | SDL_RESIZABLE) == NULL) {
		fprintf(stderr, "Impossible de passer en mode OpenGL : %s\n", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, w, 0, h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void initGL() {
	glClearColor(0.0, 0.0, 0.25, 0.0);

    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, SCREEN_SIZE_X, 0, SCREEN_SIZE_Y, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}
