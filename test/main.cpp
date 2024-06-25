#include "TransformationTest.hpp"

/**
 * @brief Initializes Google Test with command-line arguments and runs all the test cases defined in TransformationTest.hpp
 */
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}