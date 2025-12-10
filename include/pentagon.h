#ifndef PENTAGON_H
#define PENTAGON_H

#include "figure.h"
#include <cmath>
#include <memory>
#include <typeinfo>

template <Scalar T>
class Pentagon : public Figure<T> {
public:
    Pentagon() : Figure<T>(5, nullptr) {
        this->points = std::make_unique<std::unique_ptr<Point<T>>[]>(5);
        for (size_t i = 0; i < 5; ++i) {
            this->points[i] = std::make_unique<Point<T>>();
        }
        this->amountOfPoints = 5;
    }

    Pentagon(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, 
             const Point<T>& p4, const Point<T>& p5) {
        this->points = std::make_unique<std::unique_ptr<Point<T>>[]>(5);
        this->points[0] = std::make_unique<Point<T>>(p1);
        this->points[1] = std::make_unique<Point<T>>(p2);
        this->points[2] = std::make_unique<Point<T>>(p3);
        this->points[3] = std::make_unique<Point<T>>(p4);
        this->points[4] = std::make_unique<Point<T>>(p5);
        this->amountOfPoints = 5;
    }

    Point<T> center() const override {
        T cX = 0;
        T cY = 0;
        for (size_t i = 0; i < 5; ++i) {
            cX += this->points[i]->x;
            cY += this->points[i]->y;
        }
        return Point<T>(cX / 5, cY / 5);
    }

    double area() const override {
        T side = std::sqrt(
            std::pow(this->points[0]->x - this->points[1]->x, 2) +
            std::pow(this->points[0]->y - this->points[1]->y, 2)
        );
        return 1.25 * side * side / std::tan(M_PI / 5);
    }

    void read(std::istream& is) override {
        std::cout << "Введите 5 вершин пятиугольника (x y для каждой):\n";
        for (size_t i = 0; i < 5; ++i) {
            T x, y;
            std::cout << "Вершина " << i + 1 << ": ";
            is >> x >> y;
            this->points[i] = std::make_unique<Point<T>>(x, y);
        }
    }

    void print(std::ostream& os) const override {
        os << "Пятиугольник ";
        os << "Центр: " << center() << ", площадь: " << area() << ", точки:";
        this->printPoints(os);
    }
    
    std::unique_ptr<Figure<T>> copy() const override {
        return std::make_unique<Pentagon<T>>(
            *this->points[0], *this->points[1], *this->points[2],
            *this->points[3], *this->points[4]
        );
    }

    bool operator==(const Figure<T>& other) const override {
        if (typeid(*this) != typeid(other)) return false;
        
        const Pentagon* otherPentagon = dynamic_cast<const Pentagon*>(&other);
        if (!otherPentagon) return false;
        
        return std::abs(this->area() - otherPentagon->area()) < 1e-6;
    }
};

#endif
