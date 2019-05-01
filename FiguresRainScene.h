#ifndef FIGURESRAINSCENE_H_INCLUDED
#define FIGURESRAINSCENE_H_INCLUDED

#include "FiguresRainPolygon.h"

// Интерфейс всей сцены целиком.
// Ваша сцена должна его реализовать.
class FiguresRainScene {
public:
    virtual ~FiguresRainScene() = default;
    virtual unsigned int getNumberOfFigures() const = 0;
    virtual const VisPolygon* getFigure(unsigned int number) const = 0;
    virtual void doTimeStep() = 0;
};

#endif // FIGURESRAINSCENE_H_INCLUDED
