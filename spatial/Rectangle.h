#pragma once

namespace utec
{
namespace spatial
{

template<typename Point>
struct Rectangle{
    Rectangle(Point min, Point max):_min(min),_max(max){}
    Point _min;
    Point _max;

    bool contains(const Point& point) const{
        const int x=0, y=1;
        return _min.get(x) <= point.get(x) && _min.get(y) <= point.get(y) &&
                _max.get(x) >= point.get(x) && _max.get(y) >= point.get(y);
    }
};

} //spatial
} //utec
