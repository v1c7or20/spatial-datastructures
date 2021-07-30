#include <gtest/gtest.h>

#include "Point.h"
#include "Rectangle.h"
#include "RNode.h"

using namespace utec::spatial;

using data_t = int;
using point_t = Point<data_t, 2>;

const unsigned int MIN_M = 2;
const unsigned int MAX_M = 2;

//RNode
TEST(RNodeTest, insertPoint) {
  point_t point = {{30, 40}};

  RNode<point_t, Rectangle<point_t>, MIN_M, MAX_M> root(true);

  for(std::size_t I=0;I<MAX_M;I++)
    EXPECT_EQ(true, root.add(point));
  EXPECT_EQ(false, root.add(point));
}

//Asumimos que es un nodo hoja
TEST(RNodeTest, nodeCheck) {
  std::vector<point_t> points = {{{30, 40}}, {{10, 20}}};

  RNode<point_t, Rectangle<point_t>, MIN_M, MAX_M> node(true);

  for(auto point : points){
    node.add(point);
  }

  //Recorrer y comprobar que el numero de nodos es el mismo que se agregaron
  EXPECT_EQ(points.size(), node.getPoints().size());
}

// TEST(RNodeInteralTest, sameChildrenMBRsCheck) {
//   std::vector<point_t> points = {{30, 40}, {10, 20}, {36, 46}, {15, 25},{34, 44}, {13, 23},{32, 42}, {11, 21}};

//   RTree tree;

//   for(point : points){
//     tree.insert(point);
//   }

//   //Verificando que el numero de hijos sea igual al numero de MBRs
//   EXPECT_EQ(tree.getRoot().getChilden().size(), tree.getRoot().getMBRs().size());
// }


// //X Y             A B

// //                               P->CH1   CH2
// //X Y A B                           X Y   A B

// // |           |   -------  |
// // |   -----   |   |A       |
// // |   | X |   |   |        |
// // |   |   |   |   |        |
// // |   | Y |   |   |        |
// // |   -----   |   |        |
// // |           |   |     B  |
// // |           |   -----    |
// // |           |            |

// TEST(RNodeTest, quadractic_splitting) {
//   std::vector<point_t> points = {{10, 10}, {15, 15}, {60, 60}, {65, 65}};

//   RNode<point_t, Rectangle<point_t>> node(true);

//   //overflow
//   for(point : points){
//     node.add(point);
//   }

//   RTree<point_t, Rectangle<point_t>> tree;
//   RNode* node = tree.quadratic_split(&node);

//   EXPECT_EQ(2, node->getChildren().size());

//   EXPECT_EQ(node->getChildren()[0].getPoints()[0], point_t(10, 10));
//   EXPECT_EQ(node->getChildren()[0].getPoints()[1], point_t(15, 15));

//   EXPECT_EQ(node->getChildren()[1].getPoints()[0], point_t(60, 60));
//   EXPECT_EQ(node->getChildren()[1].getPoints()[1], point_t(65, 65));
// }

// //Otros tests

// //RTree
// TEST(RTreeTest, initialize){
//   RTree<point_t, Rectangle<point_t>> tree;
//   EXPECT_EQ(nullptr, tree.getRoot());
// }


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
