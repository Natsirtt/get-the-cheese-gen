#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <map>
#include <tuple>
#include "Drawable.hpp"
#include "Box.hpp"

class Scene : public Drawable {
    public:
        Scene(std::string filename);
        virtual ~Scene();

        virtual void draw(bool color);

        virtual bool mouseEvent(int button, int state, int x, int y);
        virtual bool mouseMove(int x, int y);
        virtual bool keyboard(int key);

        virtual void addDrawable(Drawable* d);

        virtual Box getBoundingBox();
        virtual bool isInside(Box b);
        virtual bool isInsideStrict(Box b);

    private:
        void update();

        std::vector<std::pair<long, Box>> mBoxes;
        std::vector<Drawable*> mDrawables;

        std::map<int, std::tuple<float, float, float>> mColors;
};

#endif // SCENE_HPP

