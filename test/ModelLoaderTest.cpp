#include <gtest/gtest.h>
#include "../include/ModelLoader.hpp" // Include the header file for ModelLoader

// Test fixture for ModelLoader
class ModelLoaderTest : public ::testing::Test {
protected:
    // SetUp() is called before each test
    void SetUp() override {
        // Set up any common variables or resources needed for the tests
    }

    // TearDown() is called after each test
    void TearDown() override {
        // Clean up any temporary resources created in SetUp()
    }
};

// Test loading a model file
TEST_F(ModelLoaderTest, LoadModel) {
    // Create an instance of ModelLoader
    ModelLoader loader;

    // Define paths to test model files
    char* validModelPath = "../assets/models/cube.obj";
    char* invalidModelPath = "path/to/invalid/model.obj";

    // Test loading a valid model file
    std::vector<Vertex> vertices; 
    std::vector<GLuint> indices;
    bool success = loader.load(validModelPath, vertices, indices);
    ASSERT_TRUE(success); // Assert that loading was successful
    ASSERT_FALSE(vertices.empty()); // Assert that vertices were loaded
    ASSERT_FALSE(indices.empty()); // Assert that faces were loaded

    // Test loading an invalid model file
    success = loader.load(invalidModelPath, vertices, indices);
    ASSERT_FALSE(success); // Assert that loading failed
}

// Main function to run all tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}