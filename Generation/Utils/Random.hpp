#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include <chrono>

template <class T = std::uniform_int_distribution<>>
class Rand_Int {
    public:
    Rand_Int(int low, int hight) : dist{low, hight} {

    }
    Rand_Int(T dist) : dist{dist} {

    }
    int operator()() {
        return dist(re);
    }

    private:
    static std::default_random_engine re;
    T dist;
};

template <class T>
std::default_random_engine Rand_Int<T>::re(std::chrono::system_clock::now().time_since_epoch().count());

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

