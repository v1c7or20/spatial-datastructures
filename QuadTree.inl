#include "QuadTree.h"
#include <memory>
#include <iostream>
#include <vector>

namespace utec
{
namespace spatial
{

template<typename Node, typename Rectangle, typename Point>
QuadTree<Node, Rectangle, Point>::QuadTree(){
    this->root=nullptr;
}

template<typename Node, typename Rectangle, typename Point>
void QuadTree<Node, Rectangle, Point>::insert(Point new_point){
    std::shared_ptr<Node>& target = search(new_point, this->root);
    if(target==nullptr){
        target=std::make_shared<Node>(new_point);
    }
}

template<typename Node, typename Rectangle, typename Point>
std::shared_ptr<Node>& QuadTree<Node, Rectangle, Point>::search(Point target, std::shared_ptr<Node>& node){
    if(node == nullptr){
        return node; //not found
    } else if(node->get_point() == target){
        return node;
    }
    
    auto cur_point = node->get_point();

    const int x=0, y=1;

    if(target.get(x) < cur_point.get(x)){
        if(target.get(y) > cur_point.get(y))
            return search(target, node->NW());
        else
            return search(target, node->SW());
    }else{
        if(target.get(y) > cur_point.get(y))
            return search(target, node->NE());
        else
            return search(target, node->SE());
    }
}

template<typename Node, typename Rectangle, typename Point>
std::shared_ptr<Node> QuadTree<Node, Rectangle, Point>::search(Point target){
    return search(target, this->root);
}

template<typename Node, typename Rectangle, typename Point>
bool QuadTree<Node, Rectangle, Point>::in_quadrant(Rectangle region, Point point_in){
  
  const int x=0, y=1;
  
  Point reg_max = region._max;
  Point reg_min = region._min;
  
  if (point_in.get(x) <= reg_max.get(x) && point_in.get(x) >= reg_min.get(x) && 
    point_in.get(y) <= reg_max.get(y) && point_in.get(y) >= reg_min.get(y)){
    return true;
  }
  return false;
}

template<typename Node, typename Rectangle, typename Point>
bool QuadTree<Node, Rectangle, Point>::in_region(Rectangle region, std::shared_ptr<Node>& node_father, std::shared_ptr<Node>& node_son){
    const int x=0, y=1;
  
    Point reg_max = region._max;
    Point reg_min = region._min;
    Point curent = node_father->get_point();
    Point next = node_son->get_point();

    auto x_min = (curent.get(x) < next.get(x)) ? curent.get(x) : next.get(x);
    auto x_max = (curent.get(x) > next.get(x)) ? curent.get(x) : next.get(x);
    auto y_min = (curent.get(y) < next.get(y)) ? curent.get(y) : next.get(y);
    auto y_max = (curent.get(y) > next.get(y)) ? curent.get(y) : next.get(y);
    /*
    std::cout<<"DEBUG: min "<<x_min<<" "<<y_min<<"\n";
    std::cout<<"DEBUG: max "<<x_max<<" "<<y_max<<"\n";
    */
    if(reg_max.get(x) < x_min){
        return false;
    }
    if(reg_min.get(x) > x_max){
        return false;
    }
    if(reg_max.get(y) < y_min){
        return false;
    }
    if(reg_min.get(y) > y_max){
        return false;
    }
    return true;
}

template<typename Node, typename Rectangle, typename Point>
std::vector<Point> QuadTree<Node, Rectangle, Point>::range(Rectangle region, std::shared_ptr<Node>& node, std::vector<Point> & result){
    auto current_point = node->get_point();
    const int x=0, y=1;
    
    Point reg_max = region._max;
    Point reg_min = region._min;

    if (in_quadrant(region, current_point)){
        result.push_back(current_point);
    }

    if (node->NW() != nullptr){
        if(reg_min.get(x) <= current_point.get(x) and reg_max.get(y) >= current_point.get(y))
            range(region, node->NW(), result);
    }
    if (node->SW() != nullptr){
        if(reg_min.get(x) <= current_point.get(x) and reg_min.get(y) <= current_point.get(y))
            range(region, node->SW(), result);
    }
    if (node->NE() != nullptr){
        if(reg_max.get(x) >= current_point.get(x) and reg_max.get(y) >= current_point.get(y))
            range(region, node->NE(), result);
    }
    if (node->SE() != nullptr){
        if(reg_max.get(x) >= current_point.get(x) and reg_min.get(y) <= current_point.get(y))
            range(region, node->SE(), result);
    }

    return result;
}

template<typename Node, typename Rectangle, typename Point>
std::vector<Point> QuadTree<Node, Rectangle, Point>::range(Rectangle region){
    std::vector<Point> answer;
    return range(region, this->root, answer);
}

template<typename Node, typename Rectangle, typename Point>
Point QuadTree<Node, Rectangle, Point>::nearest_neighbor(Point reference){
    // TODO
}

} //spatial
} //utec
