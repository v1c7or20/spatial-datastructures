#pragma once

#include "Point.h"
#include <memory>

namespace utec
{
namespace spatial
{

template<typename Point>
class KDNode{
public:
    KDNode(Point new_point):_p(new_point){}
    Point get_point() {return this->_p;}

    std::shared_ptr<KDNode>& left() {return this->_left;};
    std::shared_ptr<KDNode>& right() {return this->_right;};
private:
    Point _p;
    std::shared_ptr<KDNode> _left;
    std::shared_ptr<KDNode> _right;
};

} //spatial
} //utec