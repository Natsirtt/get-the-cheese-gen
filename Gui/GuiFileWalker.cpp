#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <cerrno>

#include <GL/gl.h>
#include <GL/glut.h>

#include "GuiManager.hpp"
#include "GuiFileWalker.hpp"
#include "Font.hpp"

FileWalker::FileWalker(std::string directory, std::string filter) : mScrolled{false}, mSelected{0}, mDirectory{directory}, mFilter{filter} {
	update();
}

void FileWalker::update() {
    mFiles.clear();
    mSelected = -1;
	DIR* dir = opendir(mDirectory.c_str());
	if (dir == NULL) {
		perror("opendir");
		throw std::runtime_error("FileWalker::FileWalker");
	}
    mMaxXSize = 0;

	struct dirent* ent = readdir(dir);
	while (ent != NULL) {
		if (ent->d_name[0] != '.') {
			std::string name(ent->d_name);
            if ((name.size() > 0) && ((mFilter.size() == 0) ||
                ((mFilter.size() != 0) && (name.find(mFilter) != std::string::npos)))) {
                mFiles.push_back(name);
                mMaxXSize = std::max(mMaxXSize, stringSizeX(name));
            }
		}
		ent = readdir(dir);
	}
	if (closedir(dir) == -1) {
		perror("closedir");
		throw std::runtime_error("FileWalker::FileWalker");
	}
}

void FileWalker::draw() {
    double r = 1.0;
    double g = 1.0;
    double b = 1.0;
    if (!isActive()) {
        r = 0.5;
        g = 0.5;
        b = 0.5;
    }

    if (isVisible()) {
        //const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();

        // int w = (getWidth() / 2.0) * (double) videoInfo->current_w;
        // int h = (getHeight() / 2.0) * (double) videoInfo->current_h;
        // int x = getX();
        // int y = videoInfo->current_h - (getY() + h);

        double glX = getX();
        double glY = getY();
        double glW = getWidth();
        double glH = getHeight();
        /*glEnable(GL_SCISSOR_TEST);
        glScissor(glX, glY, glW, glH);*/

        glBegin(GL_QUADS);
        glColor4f(0.3, 0.3, 0.3, 0.5);
        glVertex2f(glX - 5      , glY - 5      );
        glVertex2f(glX + glW + 5, glY - 5      );
        glVertex2f(glX + glW + 5, glY + glH + 5);
        glVertex2f(glX - 5      , glY + glH + 5);
        glEnd();

        glBegin(GL_LINES);
        glColor4f(0.0, 0.0, 0.0, 0.5);

        glVertex2f(glX - 5      , glY - 5      );
        glVertex2f(glX + glW + 5, glY - 5      );

        glVertex2f(glX + glW + 5, glY - 5      );
        glVertex2f(glX + glW + 5, glY + glH + 5);

        glVertex2f(glX + glW + 5, glY + glH + 5);
        glVertex2f(glX - 5      , glY + glH + 5);

        glVertex2f(glX - 5      , glY + glH + 5);
        glVertex2f(glX - 5      , glY - 5      );
        glEnd();

        glColor3f(r, g, b);
        double offY = 0.0;
        for (int i = (mFiles.size() - 1); i >= 0; i--) {
            double size = stringSizeY(mFiles.at(i));
            if (i == mSelected) {
                glBegin(GL_LINES);
                glColor4f(1.0, 1.0, 1.0, 1.0);
                glVertex2f(glX - 2      , glY + offY - 2       );
                glVertex2f(glX + 2 + glW, glY + offY - 2       );

                glVertex2f(glX + 2 + glW, glY + offY - 2       );
                glVertex2f(glX + 2 + glW, glY + offY + size - 3);

                glVertex2f(glX + 2 + glW, glY + offY + size - 3);
                glVertex2f(glX - 2      , glY + offY + size - 3);

                glVertex2f(glX - 2      , glY + offY + size - 3);
                glVertex2f(glX - 2      , glY + offY - 2       );
                glEnd();
            }
            glRasterPos2f(getX() + 2
                        , getY() + offY);
            glPrint(mFiles[i]);
            offY += size;
            //std::cout << mFiles[i] << std::endl;
        }
        /*glDisable(GL_SCISSOR_TEST);*/
    }
    glColor3f(1.0, 1.0, 1.0);
}

void FileWalker::postEvent(SDL_Event* e) {
    if ((e->type == SDL_MOUSEBUTTONDOWN) && (mFiles.size() > 0)) {
        const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();

        double size = stringSizeY(mFiles[0]);
        double x = e->button.x;
        double y = videoInfo->current_h - e->button.y;
        double newX = x;
        double newY = y;
        double bXmin = getX();
        double bXmax = getX() + getWidth();
        double bYmin = getY();
        double bYmax = getY() + getHeight();
        if ((newX >= bXmin) && (newX <= bXmax) && (newY >= bYmin)
                && (newY <= bYmax) && (isActive())) {
            double dy = newY - bYmin;
            int index = dy / size;
            if ((index < mFiles.size()) && (index >= 0)) {
                mSelected = mFiles.size() - 1 - index;
                action();
            }
        }
    }
}

std::string FileWalker::getSelectedFile() {
    if ((mFiles.size() == 0)) {
        return mDirectory;
    }
	std::string s(mDirectory);
	s += mFiles[mSelected];
	return s;
}

double FileWalker::getWidth() {
    return std::max((double)mMaxXSize, GuiElement::getWidth());
}

double FileWalker::getHeight() {
    return std::max((double)13 * mFiles.size(), GuiElement::getHeight());
}

bool FileWalker::isValid() {
    return (mSelected >= 0) && (mSelected < mFiles.size());
}
