#include <benchmark/benchmark.h>

#include "QuadNode.h"
#include "Point.h"
#include "Rectangle.h"
#include "QuadTree.h"
#include "KDTree.h"
#include "KDNode.h"

using namespace utec::spatial;

//TODO: Move to common/utils.h
template <typename T>
T genRandomNumber(T startRange, T endRange)
{
    return startRange + (T)rand()/((T)RAND_MAX/(T)(endRange-startRange));
}

using data_t = int;
using point_t = Point<data_t, 2>;

template <class TypeTree>
void BM_tree(benchmark::State& state)
{
  TypeTree tree;

  const std::size_t num_points=state.range(0);
  const std::size_t min=0, max=1000;
  auto cmp = [](point_t a, point_t b) {
    const int x=0, y=1;
    return (a.get(x) < b.get(x)) || ((a.get(x) == b.get(x)) && (a.get(y) < b.get(y)));
  };

  std::set<point_t, decltype(cmp)> points(cmp);

  for(std::size_t I=0;I<num_points;I++)
    points.insert(point_t({genRandomNumber<int>(min, max), genRandomNumber<int>(min, max)}));

  for(auto& p : points)
    tree.insert(p);

  Rectangle<point_t> region_query({{200, 200}}, {{600, 600}});

  for (auto _ : state)
  {
    auto result = tree.range(region_query);
  }
}

template <class TypeTree>
void BM_insert(benchmark::State& state)
{
  TypeTree tree;

  const std::size_t num_points=state.range(0);
  const std::size_t min=0, max=1000;
  auto cmp = [](point_t a, point_t b) {
    const int x=0, y=1;
    return (a.get(x) < b.get(x)) || ((a.get(x) == b.get(x)) && (a.get(y) < b.get(y)));
  };

  std::set<point_t, decltype(cmp)> points(cmp);

  for(std::size_t I=0;I<num_points;I++)
    points.insert(point_t({genRandomNumber<int>(min, max), genRandomNumber<int>(min, max)}));

  for (auto _ : state)
  {
    for(auto& p : points)
      tree.insert(p);
  }
}

// BENCHMARK_TEMPLATE(BM_tree, QuadTree<QuadNode<point_t>, Rectangle<point_t>, point_t>)->Range(1 << 10, 1 << 17);
// BENCHMARK_TEMPLATE(BM_tree, KDTree<KDNode<point_t>, Rectangle<point_t>, point_t>)->Range(1 << 10, 1 << 17);

BENCHMARK_TEMPLATE(BM_insert, QuadTree<QuadNode<point_t>, Rectangle<point_t>, point_t>)->Range(1 << 10, 1 << 17);
BENCHMARK_TEMPLATE(BM_insert, KDTree<KDNode<point_t>, Rectangle<point_t>, point_t>)->Range(1 << 10, 1 << 17);

BENCHMARK_MAIN();
