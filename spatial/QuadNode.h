#pragma once

#include "Point.h"

namespace utec
{
namespace spatial
{

template<typename Point>
class QuadNode{
public:
    QuadNode(Point new_point):_p(new_point){}
    Point get_point() {return this->_p;}

    std::shared_ptr<QuadNode>& NW() {return this->_NW;};
    std::shared_ptr<QuadNode>& NE() {return this->_NE;};
    std::shared_ptr<QuadNode>& SW() {return this->_SW;};
    std::shared_ptr<QuadNode>& SE() {return this->_SE;};

private:
    Point _p;
    std::shared_ptr<QuadNode> _NW;
    std::shared_ptr<QuadNode> _NE;
    std::shared_ptr<QuadNode> _SW;
    std::shared_ptr<QuadNode> _SE;
};

} //spatial
} //utec