#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "Gate.hpp"
#include "Node.hpp"
#include "Graph.hpp"
#include "Viewer/GraphViewer.hpp"
#include "ObstacleChooser.hpp"

#include "Gui/GuiManager.hpp"
#include "Gui/GuiFileWalker.hpp"
#include "Gui/GuiButton.hpp"

#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 800

void initSDL();
void reshape(int w, int h);
void initGL();

void genGraph(IGraph* graph);

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    initSDL();
    initGL();

    Graph g;
    if (argc > 1) {
        g.load(argv[1]);
    } else {
        genGraph(&g);
    }

    GraphViewer gw{&g};

    GuiManager gui;
    FileWalker filewalker{"./", ".gra"};
    filewalker.setLocation(10, 50);
    filewalker.setSize(100, 50);
    gui.add(&filewalker);

    GuiButton loadButton(10, 10, 100, 25, "Charger");
    loadButton.setAction([&]{
        if (filewalker.isValid()) {
            gw.clear();
            g.clear();
            g.load(filewalker.getSelectedFile());
            gw.reset(&g);
        }
    });
    gui.add(&loadButton);

    GuiButton saveButton(filewalker.getX() + filewalker.getWidth() + 10, 10, 100, 25, "Sauvegarder");
    saveButton.setAction([&]{
        std::string filename;
        bool found = false;
        int i = 0;
        while (!found) {
            std::stringstream ss;
            ss << "Graphe" << i << ".gra";
            std::ifstream file(ss.str());
            if (!file.is_open()) {
                found = true;
                filename = ss.str();
            }
            i++;
        }
        g.save(filename);
        filewalker.update();
        saveButton.setLocation(filewalker.getX() + filewalker.getWidth() + 10, 10);
    });
    gui.add(&saveButton);

    GuiButton deleteButton(filewalker.getX() + filewalker.getWidth() + 10, 40, 100, 25, "Supprimer");
    deleteButton.setAction([&]{
        if (filewalker.isValid()) {
            remove(filewalker.getSelectedFile().c_str());
            filewalker.update();
        }
    });
    gui.add(&deleteButton);

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
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
                if (event.key.keysym.sym == SDLK_SPACE) {
                    gw.clear();
                    g.clear();
                    genGraph(&g);
                    gw.reset(&g);
                }
                break;
            default:
                gui.postEvent(&event);
                gw.postEvent(event);
                break;
        }
        // On met à jour
        gw.update(0);
        // On dessine
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        gw.draw();
        gui.drawAll();
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

bool genGraph_Handler(IGraph* graph, int p, Id lastId, Id lastBranch, bool* finished, Perso perso, ObstacleChooser& chooser) {
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
            IGate* gate = chooser.choose(graph, lastId, nid, perso);
            graph->addGate(gate);
            *finished = true;
            return true;
        } else if (branch == 1) {
            // Repliage
            Node* node = new Node{graph, NodeType::Room, p + 1};
            Id nid = graph->addNode(node);
            // On le relie au dernier noeud
            IGate* gate = chooser.choose(graph, lastId, nid, perso);
            graph->addGate(gate);
            // On boucle
            gate = chooser.choose(graph, nid, lastBranch, perso);
            graph->addGate(gate);
        } else {
            Node* node = new Node{graph, NodeType::Room, p + 1};
            Id nid = graph->addNode(node);
            // On le relie au dernier noeud
            IGate* gate = chooser.choose(graph, lastId, nid, perso);
            graph->addGate(gate);
            Id newOldBranch = lastBranch;
            if (branch > 2) {
                newOldBranch = nid;
            }
            bool f = false;
            for (int i = 0; i < branch - 1; ++i) {
                f = f || genGraph_Handler(graph, p + 1, nid, newOldBranch, finished, perso, chooser);
            }
            if ((newOldBranch == nid) && (!f)) {
                // On boucle
                IGate* gate = chooser.choose(graph, nid, lastBranch, perso);
                graph->addGate(gate);
            }
            if (f) {
                // ATTENTION pas de "return f;"
                return true;
            }
        }
    } while ((lastId == 1) && (!*finished)); // Si on est le noeud de départ et qu'aucun noeud de fin n'à été créé

    return false;
}

void genGraph(IGraph* graph) {
    bool finished = false;
    ObstacleChooser chooser;
    genGraph_Handler(graph, 0, 1, 1, &finished, Perso::All, chooser);
}
