#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <GL/glew.h>
#include <GL/glut.h>

#include "Box.hpp"
#include "Point.hpp"

class Drawable {
    public:
        virtual ~Drawable() {};

        virtual void draw(bool color) = 0;

        virtual bool mouseEvent(int button, int state, int x, int y) = 0;
        virtual bool mouseMove(int x, int y) = 0;
        virtual bool keyboard(int key) = 0;

        virtual bool isInside(Box b) = 0;
        virtual bool isInsideStrict(Box b) = 0;
        virtual Box getBoundingBox() = 0;
};

#endif // ICURVE_HPP
