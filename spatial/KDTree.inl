#include "KDTree.h"
#include <memory>
#include <iostream>
#include <vector>

namespace utec
{
namespace spatial
{

template<typename Node, typename Rectangle, typename Point>
KDTree<Node, Rectangle, Point>::KDTree(){
    this->root=nullptr;
}

template<typename Node, typename Rectangle, typename Point>
void KDTree<Node, Rectangle, Point>::insert(Point new_point){
    std::shared_ptr<Node>& target = search(new_point, this->root, 0 /*level*/);
    if(target==nullptr){
        target=std::make_shared<Node>(new_point);
    }
}

template<typename Node, typename Rectangle, typename Point>
std::shared_ptr<Node>& KDTree<Node, Rectangle, Point>::search(Point target, std::shared_ptr<Node>& node, bool level){
    if(node == nullptr){
        return node; //not found
    } else if(node->get_point() == target){
        return node;
    }

    auto cur_point = node->get_point();

    const int x=0, y=1;

    if(target.get(level) < cur_point.get(level))
        return search(target, node->left(), !level);
    else
        return search(target, node->right(), !level);

    // if(!level){ //X
    //     if(target.get(x) < cur_point.get(x))
    //         return search(target, node->left(), !level);
    //     else
    //         return search(target, node->right(), !level);
    // }else{ //Y
    //     if(target.get(y) < cur_point.get(y))
    //         return search(target, node->left(), !level);
    //     else
    //         return search(target, node->right(), !level);
    // }
}

template<typename Node, typename Rectangle, typename Point>
std::shared_ptr<Node> KDTree<Node, Rectangle, Point>::search(Point target){
    return search(target, this->root, 0 /*level*/);
}

template<typename Node, typename Rectangle, typename Point>
void KDTree<Node, Rectangle, Point>::range(Rectangle region, std::shared_ptr<Node>& node, std::vector<Point>& result, bool level){
    if(node == nullptr){
        return;
    }

    numero_accesos++;

    auto cur_point = node->get_point();

    if(region.contains(cur_point)){
        result.push_back(cur_point);
    }

    const int x=0, y=1;

    if(!level) { // x
        if (region._max.get(x) >= cur_point.get(x))
            range(region, node->right(), result, !level);
        if (region._min.get(x) < cur_point.get(x))
            range(region, node->left(), result, !level);
    } else { // y
        if (region._max.get(y) >= cur_point.get(y))
            range(region, node->right(), result, !level);
        if (region._min.get(y) < cur_point.get(y))
            range(region, node->left(), result, !level);
    }
}

template<typename Node, typename Rectangle, typename Point>
std::vector<Point> KDTree<Node, Rectangle, Point>::range(Rectangle region){
    std::vector<Point> result;
    numero_accesos=0;
    range(region, this->root, result);
    //TODO: Refactor
    //std::cout<<"Número de accesos: "<<numero_accesos<<"\n";
    return result;
}

template<typename Node, typename Rectangle, typename Point>
Point KDTree<Node, Rectangle, Point>::nearest_neighbor(Point reference){
    // TODO
}

} //spatial
} //utec

