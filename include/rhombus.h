#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "figure.h"
#include <cmath>
#include <memory>
#include <typeinfo>

template <Scalar T>
class Rhombus : public Figure<T> {
public:
    Rhombus() : Figure<T>(4, nullptr) {
        this->points = std::make_unique<std::unique_ptr<Point<T>>[]>(4);
        for (size_t i = 0; i < 4; ++i) {
            this->points[i] = std::make_unique<Point<T>>();
        }
        this->amountOfPoints = 4;
    }

    Rhombus(const Point<T>& p1, const Point<T>& p2, 
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
        double d1 = std::sqrt(
            std::pow(this->points[2]->x - this->points[0]->x, 2) +
            std::pow(this->points[2]->y - this->points[0]->y, 2)
        );
        double d2 = std::sqrt(
            std::pow(this->points[3]->x - this->points[1]->x, 2) +
            std::pow(this->points[3]->y - this->points[1]->y, 2)
        );
        return (d1 * d2) / 2.0;
    }

    void read(std::istream& is) override {
        std::cout << "Введите 4 вершины ромба (x y для каждой):\n";
        for (size_t i = 0; i < 4; ++i) {
            T x, y;
            std::cout << "Вершина " << i + 1 << ": ";
            is >> x >> y;
            this->points[i] = std::make_unique<Point<T>>(x, y);
        }
    }

    void print(std::ostream& os) const override {
        os << "Ромб ";
        os << "Центр: " << center() << ", площадь: " << area() << ", точки:";
        this->printPoints(os);
    }
    
    std::unique_ptr<Figure<T>> copy() const override {
        return std::make_unique<Rhombus<T>>(
            *this->points[0], *this->points[1],
            *this->points[2], *this->points[3]
        );
    }

    bool operator==(const Figure<T>& other) const override {
        if (typeid(*this) != typeid(other)) return false;
        
        const Rhombus* otherRhombus = dynamic_cast<const Rhombus*>(&other);
        if (!otherRhombus) return false;
        
        return std::abs(this->area() - otherRhombus->area()) < 1e-6;
    }
};

#endif
