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
bool genGraph(IGraph* graph, int p, Id lastId, Id lastBranch, bool* finished);

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    initSDL();
    initGL();

    Graph g;
    bool finished = false;
    genGraph(&g, 0, 1, 1, &finished);

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
                if (event.key.keysym.sym == SDLK_SPACE) {
                    gw.clear();
                    g.clear();
                    bool finished = false;
                    genGraph(&g, 0, 1, 1, &finished);
                    gw.reset(&g);
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

bool genGraph(IGraph* graph, int p, Id lastId, Id lastBranch, bool* finished) {
    do {
        int branch = 0;
        { // Permet de se débarrasser des variables locales inutiles
            double interval[] = {0, 1, 2, 3, 4};
            double first = std::min(p * 0.05, 1.0);
            if (*finished) {
                first = 0.0;
            }
            double second = std::min((1.0 - first) * p * 0.1, 1.0);
            double weights[] =  {first,
                                second,
                                (1.0 - second) * 0.7,
                                (1.0 - second) * 0.3};
            std::piecewise_constant_distribution<> dist(std::begin(interval),
                                                        std::end(interval),
                                                        std::begin(weights));
            Rand_Int<std::piecewise_constant_distribution<>> rand(dist);
            branch = rand();
        }

        if (branch == 0) {
            // Fin du level
            Node* node = new Node{graph, NodeType::Finish, p + 1};
            Id nid = graph->addNode(node);
            // On le relie au dernier noeud
            Gate* gate = new Gate{graph, lastId, nid};
            graph->addGate(gate);
            *finished = true;
            return true;
        } else if (branch == 1) {
            // Repliage
            Node* node = new Node{graph, NodeType::Room, p + 1};
            Id nid = graph->addNode(node);
            // On le relie au dernier noeud
            Gate* gate = new Gate{graph, lastId, nid};
            graph->addGate(gate);
            // On boucle
            gate = new Gate{graph, nid, lastBranch};
            graph->addGate(gate);
        } else {
            Node* node = new Node{graph, NodeType::Room, p + 1};
            Id nid = graph->addNode(node);
            // On le relie au dernier noeud
            Gate* gate = new Gate{graph, lastId, nid};
            graph->addGate(gate);
            Id newOldBranch = lastBranch;
            if (branch > 2) {
                newOldBranch = nid;
            }
            bool f = false;
            for (int i = 0; i < branch - 1; ++i) {
                f = f || genGraph(graph, p + 1, nid, newOldBranch, finished);
            }
            if ((newOldBranch == nid) && (!f)) {
                // On boucle
                Gate* gate = new Gate{graph, nid, lastBranch};
                graph->addGate(gate);
            }
            if (f) {
                // ATTENTION pas de "return f;"
                return true;
            }
        }
    } while ((lastId == 1) && (!*finished));

    return false;
}

