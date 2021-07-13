#pragma once

#include "SpatialTreeBase.h"

namespace utec
{
namespace spatial
{

/**
 * KDTree implementation
 */
template<typename Node, typename Rectangle, typename Point>
class KDTree : public SpatialTreeBase<Node, Rectangle, Point>{
private:
    /**
     * Función recursiva de búsqueda.
     *
     * @param target Punto a buscar
     * @param node Nodo actual
     *
     * @return Retorna referencia al Nodo que contiene o podría contener el punto buscado
     */
    std::shared_ptr<Node>& search(Point target, std::shared_ptr<Node>& node, bool level);
    void range(Rectangle region, std::shared_ptr<Node>& node, std::vector<Point>& result, bool level=0 /*X axis*/);
    std::size_t numero_accesos;

public:
    KDTree();
    void insert(Point new_point) override;
    std::shared_ptr<Node> search(Point target) override;
    std::vector<Point> range(Rectangle region) override;
    Point nearest_neighbor(Point reference_point) override;
};

} //spatial
} //utec

#include "KDTree.inl"
