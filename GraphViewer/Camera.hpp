#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Vector.hpp"

enum Direction {
    NORTH = 1,
    SOUTH = 2,
    EAST = 4,
    WEST = 8,
    NORTH_EAST = 5,
    NORTH_WEST = 9,
    SOUTH_EAST = 6,
    SOUTH_WEST = 10,
    NONE = 0

};

class Camera {
public:
    Camera();

    void update(int dt);

    void setPosition(Vector v);

    void window_key(unsigned char key, bool down);

    /**
     * Renvoie la position de la camera.
     */
    Vector getPosition();
    /**
     * Renvoie la direction de DEPLACEMENT de la cam�ra.
     * NOTE : La direction de d�placement peut �tre diff�rente de la direction
     *          dans laquelle la camera est tourn�e.
     */
    Vector getDirection();
    Vector getLastPosition();

    void setMouse(int x, int y);

private:
    void rotate(int dt);
    void translate();
    Vector frontDir();

    float mSpeed; // Vitesse de d�placement de la cam�ra (Unit�s / seconde).
    float mPhi;   // Orientation de la vue horizontale par rapport a x+ (en radian).
    float mTheta; // Orientation de la vue verticale par rapport a y+  (en radian).
    float mThetaMax; // Angle theta maximum par rapport � (OZ) (en radian).
    float mSensi; // Sensibilit� de la souris (Degr�s / pixel).
    Vector mPosition;

    Vector mLastPosition;

    Direction mDirection;

    int mMouseX;
    int mMouseY;
};
#endif // CAMERA_HPP
