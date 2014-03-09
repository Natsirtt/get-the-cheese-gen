#include <iostream>

#include "GuiElement.hpp"
#include "GuiManager.hpp"


GuiElement::GuiElement() : mX{0.0}, mY(0.0), mW{0.0}, mH{0.0}, mVisible{true}, mActive{true}, mName{""} {

}

void GuiElement::setLocation(double x, double y) {
    mX = x;
	mY = y;
}

void GuiElement::setSize(double w, double h) {
	mW = w;
	mH = h;
}

void GuiElement::setVisible(bool visible) {
    mVisible = visible;
}

bool GuiElement::isVisible() {
    return mVisible;
}

void GuiElement::active(bool active) {
    mActive = active;
}

bool GuiElement::isActive() {
    return mActive;
}

/*void GuiElement::setAction(void (*action)(GuiElement*)) {
    if (elmnt == NULL) {
        fprintf(stderr, "elmnt NULL");
        return;
    }
    elmnt->_action = action;
}*/

std::string GuiElement::getName() {
    return mName;
}

void GuiElement::setName(std::string name) {
    mName = name;
}

double GuiElement::getX() {
    return mX;
}

double GuiElement::getY() {
    return mY;
}

double GuiElement::getWidth() {
    return mW;
}

double GuiElement::getHeight() {
    return mH;
}
