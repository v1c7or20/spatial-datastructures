#pragma once

#include "Point.h"
#include "Rectangle.h"
#include <memory>
#include <vector>


//1024 bytes / tamaño de nodo en bytes
// #define MIN_M 3
// #define MAX_M 5
namespace utec
{
namespace spatial
{

template<typename Point, typename Rectangle, unsigned int MIN_M, unsigned int MAX_M>
class RNode{
public:
    RNode(bool isLeaf):_isLeaf(isLeaf){}

    //Point get_point() {return this->_p;}
    // std::shared_ptr<RNode>& left() {return this->_left;};
    // std::shared_ptr<RNode>& right() {return this->_right;};

    bool add(Point p){
        assert(_isLeaf);
        
        if(_points.size()<MAX_M){
            _points.push_back(p);
            return true;
        }
        return false;
    }

    std::vector<std::shared_ptr<RNode>> getChildren(){
        return _children;
    }

    std::vector<Point> getPoints(){
        return _points;
    }

private:
    std::vector<Point> _points;
    bool _isLeaf;

    std::vector<std::shared_ptr<RNode>> _children;
    std::vector<Rectangle> _mbrs;
};

} //spatial
} //utec