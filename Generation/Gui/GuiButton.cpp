#include <GL/gl.h>
#include <GL/glut.h>

#include "GuiButton.hpp"
#include "Font.hpp"


GuiButton::GuiButton(double x, double y, double w, double h, std::string name) : mPressed{false} {
    setLocation(x, y);
    setSize(w, h);
	setName(name);
}


void GuiButton::draw() {
    double r = 1.0;
    double g = 0.0;
    double b = 0.0;
    if (!isActive()) {
        r = 0.5;
        g = 0.5;
        b = 0.5;
    } else if (mPressed) {
        r /= 2.0;
        g /= 2.0;
        b /= 2.0;
    }

    if (isVisible()) {
        double glX = getX();
        double glY = getY();
        double glW = getWidth();
        double glH = getHeight();

        glBegin(GL_QUADS);
        glColor3f(r, g, b);
        glVertex2f(glX      , glY      );
        glVertex2f(glX + glW, glY      );
        glVertex2f(glX + glW, glY + glH);
        glVertex2f(glX      , glY + glH);
        glEnd();

        glBegin(GL_LINES);
        glColor3f(0.0, 0.0, 0.0);
        glVertex2f(glX      , glY      );
        glVertex2f(glX      , glY + glH);

        glVertex2f(glX      , glY + glH);
        glVertex2f(glX + glW, glY + glH);

        glVertex2f(glX + glW, glY + glH);
        glVertex2f(glX + glW, glY      );

        glVertex2f(glX + glW, glY      );
        glVertex2f(glX      , glY      );
        glEnd();

		glEnable(GL_SCISSOR_TEST);
		glScissor(glX, glY, glW, glH);
		glColor3f(1.0 - r, 1.0 - g, 1.0 - b);
		double offX = (getWidth() - (double) stringSizeX(getName())) / 2.0;
		double offY = (getHeight() - (double) stringSizeY(getName())) / 2.0;
		glRasterPos2f(getX() + offX
					, getY() + offY);
		glPrint(getName());
		glDisable(GL_SCISSOR_TEST);
    }
    glColor3f(1.0, 1.0, 1.0);
}

void GuiButton::postEvent(SDL_Event* e) {
	const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();

	if ((e->type == SDL_MOUSEBUTTONDOWN) || (e->type == SDL_MOUSEBUTTONUP)) {
		double x = e->button.x;
		double y = videoInfo->current_h - e->button.y;
		double bXmin = getX();
		double bXmax = getX() + getWidth();
		double bYmin = getY();
		double bYmax = getY() + getHeight();
		if (e->type == SDL_MOUSEBUTTONDOWN) {
			if ((x >= bXmin) && (x <= bXmax) && (y >= bYmin)
					&& (y <= bYmax) && (isActive())) {
				mPressed = true;
			}
		}
		if (e->type == SDL_MOUSEBUTTONUP) {
			mPressed = false;
			if ((x >= bXmin) && (x <= bXmax) && (y >= bYmin)
					&& (y <= bYmax) && (isActive())) {
				action();
			}
		}
	}
}
