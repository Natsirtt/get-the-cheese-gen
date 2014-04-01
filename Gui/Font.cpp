#include "Font.hpp"

#include <GL/glew.h>
#include <GL/glut.h>

int stringSizeX(std::string text) {
    /*int res = 0;
    for (auto& c : text) {
        res += 8;
    }
    return res;*/
    return 8 * text.size();
}

int stringSizeY(std::string text) {
    int res = 13;
    for (auto& c : text) {
        if (c == '\n') {
            res += 13;
        }
    }
    return res;
}

void glPrint(std::string text) {
	for (auto& c : text) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
    }
}
