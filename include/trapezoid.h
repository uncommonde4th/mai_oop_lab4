#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "figure.h"
#include <cmath>
#include <memory>
#include <typeinfo>

template <Scalar T>
class Trapezoid : public Figure<T> {
public:
    Trapezoid() : Figure<T>(4, nullptr) {
        this->points = std::make_unique<std::unique_ptr<Point<T>>[]>(4);
        for (size_t i = 0; i < 4; ++i) {
            this->points[i] = std::make_unique<Point<T>>();
        }
        this->amountOfPoints = 4;
    }

    Trapezoid(const Point<T>& p1, const Point<T>& p2, 
              const Point<T>& p3, const Point<T>& p4) {
        this->points = std::make_unique<std::unique_ptr<Point<T>>[]>(4);
        this->points[0] = std::make_unique<Point<T>>(p1);
        this->points[1] = std::make_unique<Point<T>>(p2);
        this->points[2] = std::make_unique<Point<T>>(p3);
        this->points[3] = std::make_unique<Point<T>>(p4);
        this->amountOfPoints = 4;
    }

    Point<T> center() const override {
        T cX = 0;
        T cY = 0;
        for (size_t i = 0; i < 4; ++i) {
            cX += this->points[i]->x;
            cY += this->points[i]->y;
        }
        return Point<T>(cX / 4, cY / 4);
    }

    double area() const override {
        double sum = 0;
        for (int i = 0; i < 4; ++i) {
            int j = (i + 1) % 4;
            sum += this->points[i]->x * this->points[j]->y - 
                   this->points[j]->x * this->points[i]->y;
        }
        return std::abs(sum) / 2.0;
    }

    void read(std::istream& is) override {
        std::cout << "Введите 4 вершины трапеции (x y для каждой):\n";
        for (size_t i = 0; i < 4; ++i) {
            T x, y;
            std::cout << "Вершина " << i + 1 << ": ";
            is >> x >> y;
            this->points[i] = std::make_unique<Point<T>>(x, y);
        }
    }

    void print(std::ostream& os) const override {
        os << "Трапеция ";
        os << "Центр: " << center() << ", площадь: " << area() << ", точки:";
        this->printPoints(os);
    }
    
    std::unique_ptr<Figure<T>> copy() const override {
        return std::make_unique<Trapezoid<T>>(
            *this->points[0], *this->points[1],
            *this->points[2], *this->points[3]
        );
    }

    bool operator==(const Figure<T>& other) const override {
        if (typeid(*this) != typeid(other)) return false;
        
        const Trapezoid* otherTrapezoid = dynamic_cast<const Trapezoid*>(&other);
        if (!otherTrapezoid) return false;
        
        return std::abs(this->area() - otherTrapezoid->area()) < 1e-6;
    }
};

#endif
