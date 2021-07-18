#include <gtest/gtest.h>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/shared_ptr.hpp>

#include "Point.h"
#include "Rectangle.h"
#include "QuadTree.h"
#include "KDTree.h"
#include "KDNode.h"

using namespace utec::spatial;

template <typename T>
T genRandomNumber(T startRange, T endRange)
{
    return startRange + (T)rand()/((T)RAND_MAX/(T)(endRange-startRange));
}

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

namespace boost{ namespace geometry{ namespace index{
template <typename Box>
struct indexable<boost::shared_ptr<Box>>{
  typedef boost::shared_ptr<Box> V;
  typedef Box const& result_type;
  result_type operator()(V const& v) const {return *v;}
};
}}} //boost::geometry::index

typedef bg::model::point<double, 2, bg::cs::cartesian> point;
typedef boost::shared_ptr<point> value;
typedef bg::model::box<point> box;

class QuadTreeParamTest : public ::testing::TestWithParam<std::size_t> {
  protected:
    using data_t = int;
    using point_t = Point<data_t, 2>;
    //QuadTree<QuadNode<point_t>, Rectangle<point_t>, point_t> tree;
    KDTree<KDNode<point_t>, Rectangle<point_t>, point_t> tree;

    bgi::rtree<value, bgi::linear<16, 4>> rtree;
};

TEST_P(QuadTreeParamTest, randomRangeTest) {
  const std::size_t num_points = GetParam();
  const std::size_t min=0, max=1000;

  auto cmp = [](point_t a, point_t b) {
    const int x=0, y=1;
    return (a.get(x) < b.get(x)) || ((a.get(x) == b.get(x)) && (a.get(y) < b.get(y)));
  };

  std::set<point_t, decltype(cmp)> points(cmp);

  for(std::size_t I=0;I<num_points;I++)
    points.insert(point_t({genRandomNumber<int>(min, max), genRandomNumber<int>(min, max)}));

  for(auto& p : points){
    tree.insert(p);

    boost::shared_ptr<point> new_point(new point(p.get(0), p.get(1)));
    rtree.insert(new_point);
  }

  Rectangle<point_t> region({{200, 200}}, {{600, 600}});
  auto result = tree.range(region);

  box query(point(200, 200), point(600, 600));
  std::vector<value> reference_result;
  rtree.query(bgi::intersects(query), std::back_inserter(reference_result));

  EXPECT_EQ(result.size(), reference_result.size());
}

INSTANTIATE_TEST_CASE_P(
        TreePointsParam,
        QuadTreeParamTest,
        ::testing::Values(10, 100, 1000, 10000));

int main(int argc, char **argv) {
  srand((unsigned)time(0));

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}