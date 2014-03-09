#ifndef GUIELEMENT_HPP
#define GUIELEMENT_HPP

#include <iostream>
#include <SDL/SDL.h>

class GuiElement {
public:
    GuiElement();

    virtual void draw() = 0;
    virtual void postEvent(SDL_Event* e) = 0;

	virtual double getX();
	virtual double getY();
	virtual double getWidth();
	virtual double getHeight();
	std::string getName();
	bool  isVisible();
	bool  isActive();

    void setLocation(double x, double y);
    void setSize(double w, double h);
    void setVisible(bool visible);
    void setName(std::string name);
    void active(bool active);

    void action();
private:
    double mX;
    double mY;
    double mW;
    double mH;
    int mVisible;
    int mActive;
    std::string mName;
};

#endif
