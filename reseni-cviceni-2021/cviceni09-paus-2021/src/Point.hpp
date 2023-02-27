#ifndef POINT_H
#define POINT_H

#include <ostream>
#include <cmath>

class Point
{
    double x, y;

public:
    Point(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}
    
    // TODO: Dodelat potrebne metody, aby se to zkompilovalo
    
    double abs() const { return sqrt(x*x + y*y); }

    bool operator>(const Point& p2) const { return abs() > p2.abs(); }

    friend std::ostream& operator<<(std::ostream& os, const Point& p)
    {
        return os << "[" << p.x << ", " << p.y << "]";
    }
};

#endif