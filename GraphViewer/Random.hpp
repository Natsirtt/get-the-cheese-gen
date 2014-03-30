#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>

class Rand_Int {
    public:
    Rand_Int(int low, int hight) : dist{low, hight} {

    }

    int operator()() {
        return dist(re);
    }

    private:
    static std::default_random_engine re;
    std::uniform_int_distribution<> dist;
};

class Rand_Float {
    public:
    Rand_Float(float low, float hight) : dist{low, hight} {

    }

    float operator()() {
        return dist(re);
    }

    private:
    static std::default_random_engine re;
    std::uniform_real_distribution<> dist;
};


#endif // RANDOM_HPP

