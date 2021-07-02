#pragma once

#include "Point.h"

namespace utec
{
namespace spatial
{

template<typename KDPoint>
class KDNode{
public:
    KDNode(KDPoint new_point):_p(new_point){}
    KDPoint get_point() {return this->_p;}

    std::shared_ptr<KDNode>& left() {return this->_left;};
    std::shared_ptr<KDNode>& right() {return this->_right;};
private:
    KDPoint _p;
    std::shared_ptr<KDNode> _left;
    std::shared_ptr<KDNode> _right;
};

} //spatial
} //utec