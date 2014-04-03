#include <cmath>
#include <iostream>

#include <GL/glut.h>

#include "Camera.hpp"

static const float pi = 4 * std::atan(1);

float degToRad(float x) {
    return x * pi / 180.0f;
}

float radToDeg(float x) {
    return x * 180.0f / pi;
}

Camera::Camera() : mSpeed{60.0f}, mPhi{degToRad(-33.0f)}, mTheta{degToRad(-10.0f)},
                    mThetaMax{degToRad(75.0f)}, mSensi{0.5f}, mPosition{0.0f, 0.0f, -2.0f},
                    mDirection{Direction::NONE}, mMouseX{0}, mMouseY{0} {
}

void Camera::update(int dt) {
    rotate(dt);

    // On translate la caméra
    float mul = (dt / 1000.0f) * mSpeed;
    Vector move = getDirection();
    move.normalize();
    move = move * mul;
    move = move + mPosition;

    setPosition(move);

    // On calcule la direction de vue de la caméra
    Vector front = frontDir();
    front.normalize();
    Vector to = mPosition + front;

    glLoadIdentity();
    gluLookAt(mPosition.getX(), mPosition.getY(), mPosition.getZ(), to.getX(), to.getY(), to.getZ(), 0.0, 1.0, 0.0);
}

void Camera::setPosition(Vector v) {
    mLastPosition = mPosition;
    mPosition = v;
}

Vector Camera::getLastPosition() {
    return mLastPosition;
}

Vector Camera::getPosition() {
    return mPosition;
}

Vector Camera::getDirection() {
    Vector frontdir = frontDir();
    Vector rightdir = frontdir.vectoriel(Vector{0.0f, 1.0f, 0.0f});
    Vector d;

    switch (mDirection) {
    case Direction::NONE:
        return {};
        break;
    case Direction::NORTH:
        return frontdir;
        break;
    case Direction::SOUTH:
        return frontdir.neg();
        break;
    case Direction::WEST:
        return rightdir.neg();
        break;
    case Direction::EAST:
        return rightdir;
        break;
    case Direction::NORTH_EAST:
        d = (frontdir + rightdir);
        d.normalize();
        return d;
        break;
    case Direction::NORTH_WEST:
        d = (frontdir + rightdir.neg());
        d.normalize();
        return d;
        break;
    case Direction::SOUTH_EAST:
        d = (frontdir.neg() + rightdir);
        d.normalize();
        return d;
        break;
    case Direction::SOUTH_WEST:
        d = (frontdir.neg() + rightdir.neg());
        d.normalize();
        return d;
        break;
    }
    return {};
}

////////////////////////////////////////////////////////////////////////////////
// FONCTION PRIVEES
////////////////////////////////////////////////////////////////////////////////

void Camera::rotate(int dt) {
    int screenMiddleX = glutGet(GLUT_WINDOW_WIDTH) / 2;
    int screenMiddleY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
    int mouseX = mMouseX;
    int mouseY = mMouseY;

    // Si la souris n'est plus au centre de l'écran
    if ((mouseX != screenMiddleX) || (mouseY != screenMiddleY)) {
        float dx = mouseX - screenMiddleX;
        float dy = mouseY - screenMiddleY;
        mPhi -= degToRad(dx * mSensi);
        mTheta -= degToRad(dy * mSensi);

        /*
         * On évite à phi de devenir trop grand (ou trop petit)
         *   en enlevant (ou ajoutant) 1 tour à chaque tour
         */
        if (mPhi > degToRad(360.0f)) {
            mPhi -= degToRad(360.0f);
        } else if (mPhi < 0.0f) {
            mPhi += degToRad(360.0f);
        }
        // On évite que theta dépasse la limite
        if (mTheta > mThetaMax) {
            mTheta = mThetaMax;
        } else if (mTheta < -mThetaMax) {
            mTheta = -mThetaMax;
        }

        // On remet la souris au centre de l'écran
        glutWarpPointer(screenMiddleX, screenMiddleY);
        mMouseX = screenMiddleX;
        mMouseY = screenMiddleY;
    }
}

Vector Camera::frontDir() {
    Vector v{static_cast<float>(cos(mTheta) * cos(mPhi)),
                static_cast<float>(sin(mTheta)),
                static_cast<float>(-cos(mTheta) * sin(mPhi))};
    return v;
}

void Camera::window_key(unsigned char key, bool down) {
    Direction mod = Direction::NONE;
    if (key == 'z') {
        mod = Direction::NORTH;
    } else if (key == 's') {
        mod = Direction::SOUTH;
    } else if (key == 'q') {
        mod = Direction::WEST;
    } else if (key == 'd') {
        mod = Direction::EAST;
    } else {
        mod = Direction::NONE;
    }
    if (down) {
        mDirection = (Direction)((int)mDirection | (int)mod);
    } else {
        mDirection = (Direction)((int)mDirection & (~(int)mod));
    }
}

void Camera::setMouse(int x, int y) {
    mMouseX = x;
    mMouseY = y;
}
