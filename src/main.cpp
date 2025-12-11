#include <iostream>
#include <memory>

#include "../include/point.h"
#include "../include/figure.h"
#include "../include/pentagon.h"
#include "../include/rhombus.h"
#include "../include/trapezoid.h"
#include "../include/array.h"

using namespace std;

int main() {
    Array<shared_ptr<Pentagon<int>>> pentagons;
    
    pentagons.add(make_shared<Pentagon<int>>(
        Point<int>(0,0), Point<int>(2,0), 
        Point<int>(2,2), Point<int>(0,2), Point<int>(1,1)
    ));
    pentagons.add(make_shared<Pentagon<int>>(
        Point<int>(1,1), Point<int>(3,1), 
        Point<int>(3,3), Point<int>(1,3), Point<int>(2,2)
    ));
    
    cout << "Пятиугольники: " << pentagons;
    cout << "Суммарная площадь: " << pentagons.allArea() << endl;
    
    Array<shared_ptr<Figure<double>>> figures;
    
    figures.readFigure<Pentagon<double>>();
    figures.readFigure<Rhombus<double>>();
    
    cout << "Фигуры: " << figures << endl;
    cout << "Общая площадь: " << figures.allArea() << endl;
    
    return 0;
}
