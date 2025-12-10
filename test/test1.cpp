#include <gtest/gtest.h>
#include "../include/point.h"
#include "../include/figure.h"
#include "../include/pentagon.h"
#include "../include/rhombus.h"
#include "../include/trapezoid.h"
#include "../include/array.h"

TEST(PointTest, Constructor) {
    Point<double> p(3.5, -2.0);
    EXPECT_DOUBLE_EQ(p.x, 3.5);
    EXPECT_DOUBLE_EQ(p.y, -2.0);
}

TEST(PentagonTest, Area) {
    Pentagon<double> p(
        Point<double>(1.0, 0.0),
        Point<double>(0.309, 0.951),
        Point<double>(-0.809, 0.588),
        Point<double>(-0.809, -0.588),
        Point<double>(0.309, -0.951)
    );
    EXPECT_NEAR(static_cast<double>(p), 2.37764, 2e-4);
}

TEST(RhombusTest, Area) {
    Rhombus<double> r(
        Point<double>(-2, 0),
        Point<double>(0, 1.5),
        Point<double>(2, 0),
        Point<double>(0, -1.5)
    );
    EXPECT_NEAR(static_cast<double>(r), 6.0, 1e-4);
}

TEST(TrapezoidTest, Area) {
    Trapezoid<double> t(
        Point<double>(0, 0),
        Point<double>(4, 0),
        Point<double>(3, 3),
        Point<double>(1, 3)
    );
    EXPECT_NEAR(static_cast<double>(t), 9.0, 1e-4);
}

TEST(ArrayTest, BasicOperations) {
    Array<int> arr;
    arr.add(5);
    arr.add(10);
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_EQ(arr[0], 5);
    EXPECT_EQ(arr[1], 10);
}

TEST(ArrayTest, Remove) {
    Array<int> arr;
    arr.add(1);
    arr.add(2);
    arr.add(3);
    arr.remove(1);
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
}

TEST(ArrayTest, AllArea) {
    Array<std::shared_ptr<Figure<double>>> arr;
    arr.add(std::make_shared<Pentagon<double>>(
        Point<double>(1.0, 0.0),
        Point<double>(0.309, 0.951),
        Point<double>(-0.809, 0.588),
        Point<double>(-0.809, -0.588),
        Point<double>(0.309, -0.951)
    ));
    arr.add(std::make_shared<Rhombus<double>>(
        Point<double>(-2, 0),
        Point<double>(0, 1.5),
        Point<double>(2, 0),
        Point<double>(0, -1.5)
    ));
    EXPECT_NEAR(arr.allArea(), 8.37764, 2e-4);
}

TEST(ArrayTest, MoveSemantics) {
    Array<int> arr1;
    arr1.add(1);
    arr1.add(2);
    Array<int> arr2 = std::move(arr1);
    EXPECT_EQ(arr2.getSize(), 2);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
}

TEST(FigureTest, Comparison) {
    Pentagon<double> p1(
        Point<double>(1.0, 0.0),
        Point<double>(0.309, 0.951),
        Point<double>(-0.809, 0.588),
        Point<double>(-0.809, -0.588),
        Point<double>(0.309, -0.951)
    );
    auto p2 = p1.copy();
    EXPECT_TRUE(p1 == *p2);
}

TEST(ArrayTest, IndexOutOfRange) {
    Array<int> arr;
    arr.add(1);
    EXPECT_THROW(arr[5], std::out_of_range);
    EXPECT_THROW(arr.remove(5), std::out_of_range);
}

TEST(FigureTest, IOTest) {
    Pentagon<double> p(
        Point<double>(1, 0),
        Point<double>(0, 1),
        Point<double>(-1, 0),
        Point<double>(-0.5, -1),
        Point<double>(0.5, -1)
    );
    std::stringstream ss;
    ss << p;
    EXPECT_FALSE(ss.str().empty());
}

TEST(ArrayTest, CopyConstructor) {
    Array<int> arr1;
    arr1.add(1);
    arr1.add(2);
    Array<int> arr2(arr1);
    EXPECT_EQ(arr2.getSize(), 2);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
}

TEST(ArrayTest, AssignmentOperator) {
    Array<int> arr1;
    arr1.add(1);
    arr1.add(2);
    Array<int> arr2;
    arr2 = arr1;
    EXPECT_EQ(arr2.getSize(), 2);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
