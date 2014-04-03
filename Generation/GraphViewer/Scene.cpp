#include "Scene.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "Random.hpp"

#define CUBE_SIZE 1.0

Scene::Scene(std::string filename) {
    std::fstream file(filename);
    long x, y, z, t;
    Rand_Float random(0.0, 1.0);
    while (!file.eof()) {
        file >> x >> y >> z >> t;
        mColors[t] = std::make_tuple(random(), random(), random());
        auto& tup = mColors[t];
        std::cout << std::get<0>(tup) << " " << std::get<1>(tup) << " " << std::get<2>(tup) << std::endl;
        mBoxes.push_back(std::make_pair(
                        t,
                        Box(x * CUBE_SIZE - CUBE_SIZE / 2, x * CUBE_SIZE + CUBE_SIZE / 2,
                             y * CUBE_SIZE - CUBE_SIZE / 2, y * CUBE_SIZE + CUBE_SIZE / 2,
                             z * CUBE_SIZE - CUBE_SIZE / 2, z * CUBE_SIZE + CUBE_SIZE / 2)));
    }
}

Scene::~Scene() {

}

void Scene::draw(bool color) {
    glPushMatrix();

    double i = 0.0;
    for (auto& b : mBoxes) {
        if (color) {
            auto& tup = mColors[b.first];
            //std::cout << std::get<0>(tup) << " " << std::get<1>(tup) << " " << std::get<2>(tup) << std::endl;
            glColor3f(std::get<0>(tup), std::get<1>(tup), std::get<2>(tup));
        }

        b.second.draw();
        i++;
    }
    glPopMatrix();
}

bool Scene::mouseEvent(int button, int state, int x, int y) {
    return false;
}
bool Scene::mouseMove(int x, int y) {
    return false;
}
bool Scene::keyboard(int key) {
    return false;
}

void Scene::addDrawable(Drawable* d) {
    mDrawables.push_back(d);
    update();
}

bool Scene::isInside(Box b) {
    return false;
}
bool Scene::isInsideStrict(Box b) {
    return false;
}

Box Scene::getBoundingBox() {
    Box b(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    if (mDrawables.size() > 0) {
        b = mDrawables[0]->getBoundingBox();
    }
    for (auto& d : mDrawables) {
        b.update(d->getBoundingBox());
    }

    return b;
}

void Scene::update() {
}

