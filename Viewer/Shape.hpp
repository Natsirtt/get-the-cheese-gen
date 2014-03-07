#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <SDL/SDL.h>
#include "Vector.hpp"
#include "Random.hpp"

class Shape {
public:
    Shape() : mPosition(Rand_Int<>(0, 800)(), Rand_Int<>(0, 800)(), 0.0), mDragging{false} {

    }
    virtual ~Shape() {};
    virtual void update(int dt) = 0;
    virtual void draw() = 0;

    virtual bool postEvent(SDL_Event& event) {
        const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
        int screenY = videoInfo->current_h;
        if ((mDragging) && (event.type == SDL_MOUSEMOTION)) {
            mPosition = Vector(event.motion.x, screenY - event.motion.y, 0.0);
            return true;
        } else if ((mDragging) && (event.type == SDL_MOUSEBUTTONUP)) {
            mDragging = false;
            return true;
        } else if ((!mDragging) && (event.type == SDL_MOUSEBUTTONDOWN)) {
            mDragging = isInside(Vector(event.motion.x, screenY - event.motion.y, 0.0));
            return mDragging;
        }
        mDragging = false;
        return false;
    }

    virtual void setSize(int size) = 0;

    virtual void setPosition(Vector v) {
        mPosition = v;
    }

    virtual Vector getPosition() {
        return mPosition;
    }

    virtual bool isInside(Vector p) = 0;

private:
    Vector mPosition;
    bool mDragging;
};

#endif // SHAPE_HPP

