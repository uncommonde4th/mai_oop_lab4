#include <iostream>
#include <memory>

#include "../include/point.h"
#include "../include/figure.h"
#include "../include/pentagon.h"
#include "../include/rhombus.h"
#include "../include/trapezoid.h"
#include "../include/array.h"


using FigurePtr = std::shared_ptr<Figure<double>>;
using FigureArray = Array<FigurePtr>;

int main() {
    FigureArray figures;

    std::cout << "Ввод пятиугольника (5 вершин):\n";
    figures.readFigure<Pentagon<double>>();

    std::cout << "\nВвод ромба (4 вершины):\n";
    figures.readFigure<Rhombus<double>>();

    std::cout << "\nВвод трапеции (4 вершины):\n";
    figures.readFigure<Trapezoid<double>>();

    std::cout << "\nВсе фигуры:\n" << figures;

    std::cout << "Общая площадь: " << figures.allArea() << "\n";

    figures.remove(0);
    std::cout << "\nПосле удаления первой фигуры:\n" << figures;
    std::cout << "Новая общая площадь: " << figures.allArea() << "\n";

    return 0;
}
