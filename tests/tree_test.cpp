#include <gtest/gtest.h>

#include "QuadNode.h"
#include "Point.h"
#include "Rectangle.h"
#include "QuadTree.h"
#include "KDTree.h"
#include "KDNode.h"

using namespace utec::spatial;

using data_t = int;
using point_t = Point<data_t, 2>;

template <typename TypeTree>
class SpatialTreeTest : public ::testing::Test {
  protected:
    TypeTree tree;
};

using SpatialTypes = ::testing::Types<QuadTree<QuadNode<point_t>, Rectangle<point_t>, point_t>,
                                      KDTree<KDNode<point_t>, Rectangle<point_t>, point_t>>;

TYPED_TEST_SUITE(SpatialTreeTest, SpatialTypes);

TYPED_TEST(SpatialTreeTest, emptyPointList) {
  point_t point = {{30, 40}};
  auto node = this->tree.search(point);
  EXPECT_EQ(node, nullptr);
}

TYPED_TEST(SpatialTreeTest, insertOneElement) {
  point_t point = {{30, 40}};
  this->tree.insert(point);

  auto node = this->tree.search(point);
  ASSERT_TRUE(node != nullptr);
  EXPECT_EQ(node->get_point(), point);
}

TYPED_TEST(SpatialTreeTest, insertSeveralElement) {
  std::vector<point_t> points = {{{30, 40}}, {{5, 25}}, {{10, 12}}, {{70,70}}, {{50, 30}}, {{35, 45}}};

  for(auto& p : points){
    this->tree.insert(p);
    auto node = this->tree.search(p);

    ASSERT_TRUE(node != nullptr);
    EXPECT_EQ(node->get_point(), p);
  }
}

TYPED_TEST(SpatialTreeTest, simpleRangeTest) {
  std::vector<point_t> points = {{{5, 0}}, {{6, 9}}, {{9, 3}}, {{6, 5}}, {{7, 7}}, {{8, 6}}};

  Rectangle<point_t> region({{8, 2}}, {{10, 4}});

  for(auto& p : points){
    this->tree.insert(p);
  }

  auto result = this->tree.range(region);

  ASSERT_EQ(result.size(), 1);
  EXPECT_EQ(result[0], point_t({9, 3}));
}

int main(int argc, char **argv) {
  srand((unsigned)time(0));

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
