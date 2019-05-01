#ifndef FIGURESRAINPOLYGON_H_INCLUDED
#define FIGURESRAINPOLYGON_H_INCLUDED

#include <vector>

using std::vector;

// Точка фигуры, используемая для визуализации.
// Вы можете использовать такие точки для чего-то ещё.
// А можете только отдавать их для визуализации, когда попросят. А для своих расчётов хранить нечто иное.
class VisPoint {
protected:
    double x;
    double y;
public:
    VisPoint() {}
    VisPoint(double x, double y) : x(x), y(y) {}

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }
};

// Интерфейс фигуры, используемый визуализатором.
// Все фигуры должны реализовать его, чтобы визуализатор начал с ними работать.
class VisPolygon {
public:
    virtual ~VisPolygon() = default;
    virtual vector<VisPoint> getVertices() const = 0;
};


#endif // FIGURESRAINPOLYGON_H_INCLUDED
