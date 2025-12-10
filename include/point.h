#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <type_traits>
#include <concepts>

template<typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
struct Point {
    T x;
    T y;

    Point() = default;
    Point(T x_, T y_) : x(x_), y(y_) {}

    friend std::ostream& operator<<(std::ostream& os, Point<T> const& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

#endif
