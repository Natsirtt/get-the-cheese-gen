#ifndef TUPLE_HPP
#define TUPLE_HPP

#include <tuple>

inline std::tuple<long, long, long> operator+(std::tuple<long, long, long> t1, std::tuple<long, long, long> t2) {
    return std::make_tuple(std::get<0>(t1) + std::get<0>(t2),
                           std::get<1>(t1) + std::get<1>(t2),
                           std::get<2>(t1) + std::get<2>(t2));
}

#endif // TUPLE_HPP

