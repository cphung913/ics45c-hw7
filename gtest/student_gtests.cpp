// ------------------------- Your tests - student_gtests.cpp ----------------------------- //
// Your own GoogleTest suite for the Array of int in int_array.hpp. It is graded: the
// autograder runs it against a correct Array and against several with one bug each. A test is
// worth something only when it passes on the correct Array and fails on a broken one, so a
// test that always fails (or that tests nothing) earns nothing.
//
// Two examples are given. Add tests of your own for the constructors, the copy and move
// operations, operator[] in and out of range, fill, and length.
// --------------------------------------------------------------------------------------- //

#include <gtest/gtest.h>

#include <string>

#include "int_array.hpp"

TEST(IntArrayTests, DefaultArrayIsEmpty) {
    const Array a;
    EXPECT_EQ(a.length(), 0);
}

TEST(IntArrayTests, SizedArrayReportsItsLength) {
    const Array a{5};
    EXPECT_EQ(a.length(), 5);
}

TEST(IntArrayTests, Subscript) {
    Array a{3};
    a[0] = 1;
    a[2] = 3;
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[2], 3);
    EXPECT_THROW(a[3], std::string);

    std::string message;
    try {
        a[-1];
    } catch (const std::string& e) {
        message = e;
    }
    EXPECT_EQ(message, "Exception operator[](-1) Out Of Range");
}

TEST(IntArrayTests, ConstSubscript) {
    Array a{3};
    a[0] = 1;
    a[2] = 3;
    const Array& c = a;
    EXPECT_EQ(c[0], 1);
    EXPECT_EQ(c[2], 3);
    EXPECT_THROW(c[3], std::string);
    EXPECT_THROW(c[-1], std::string);
}

TEST(IntArrayTests, Fill) {
    Array a{4};
    a.fill(7);
    EXPECT_EQ(a[0], 7);
    EXPECT_EQ(a[3], 7);
}
