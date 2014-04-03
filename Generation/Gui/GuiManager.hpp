#ifndef GUIMANAGER_HPP
#define GUIMANAGER_HPP

#include <vector>
#include <memory>
#include <SDL/SDL.h>

#include "GuiElement.hpp"

class GuiManager {
public:
	GuiManager();

	void add(GuiElement* elmnt);

	void clean();

	void drawAll();

	void postEvent(SDL_Event* e);

private:
	std::vector<GuiElement*> mElements;
};

#endif
