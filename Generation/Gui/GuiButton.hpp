#ifndef GUIBUTTON_HPP
#define GUIBUTTON_HPP

#include "GuiElement.hpp"


class GuiButton : public GuiElement {
public:
	GuiButton(double x, double y, double w, double h, std::string name);

	void draw();
	void postEvent(SDL_Event* e);

private:
    bool mPressed;
};

#endif
