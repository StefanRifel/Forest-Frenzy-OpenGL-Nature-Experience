#include "Vec4Test.hpp"
#include "Vec3Test.hpp"
#include "Mat4Test.hpp"
#include "VectorTest.hpp"
#include <iostream>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}