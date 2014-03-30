#include "Random.hpp"
#include <chrono>

std::default_random_engine Rand_Int::re(std::chrono::system_clock::now().time_since_epoch().count());

std::default_random_engine Rand_Float::re(std::chrono::system_clock::now().time_since_epoch().count());
