#ifndef FIGURESRAINPOLYGON_H_INCLUDED
#define FIGURESRAINPOLYGON_H_INCLUDED

#include <vector>

using std::vector;

// ����� ������, ������������ ��� ������������.
// �� ������ ������������ ����� ����� ��� ����-�� ���.
// � ������ ������ �������� �� ��� ������������, ����� ��������. � ��� ����� �������� ������� ����� ����.
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

// ��������� ������, ������������ ��������������.
// ��� ������ ������ ����������� ���, ����� ������������ ����� � ���� ��������.
class VisPolygon {
public:
    virtual ~VisPolygon() = default;
    virtual vector<VisPoint> getVertices() const = 0;
};


#endif // FIGURESRAINPOLYGON_H_INCLUDED
