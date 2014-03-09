#include <iostream>
#include <stdexcept>
#include <GL/glew.h>
#include "GuiManager.hpp"

GuiManager::GuiManager() {

}

void GuiManager::add(GuiElement* elmnt) {
    if (elmnt == NULL) {
        throw std::runtime_error("GuiManager::add : elmnt NULL");
    }
    mElements.push_back(elmnt);
}

void GuiManager::clean() {
    mElements.clear();
}

void GuiManager::drawAll() {
    for (auto& elmnt : mElements) {
		elmnt->draw();
	}
}

void GuiManager::postEvent(SDL_Event* e) {
    for (auto& elmnt : mElements) {
		elmnt->postEvent(e);
	}
}

