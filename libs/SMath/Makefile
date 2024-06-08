# Name of executable
PROGRAM_NAME = libsmath.a
PROGRAM_NAME_TEST = SMath_Test

# Compiler
CC = g++

# Libraries
GLEW_LIBS = -lGLEW -lEGL -lGL -lGLU -lOpenGL 
GLFW_LIBS = -lglfw
GTEST = $(shell pkg-config --libs gtest)
SMATH = -lsmath -L./bin/

# Directories
SRC = src
BIN = bin
OBJ = bin/obj
TEST = test

# Target names
TARGET = $(BIN)/$(PROGRAM_NAME)
TARGET_TEST = $(BIN)/$(PROGRAM_NAME_TEST)

# Find all src file in directories
SRCS = $(shell find $(SRC) -name '*.cpp')
SRCS_TEST = $(shell find $(TEST) -name '*.cpp')

OBJS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))
OBJS_TEST = $(patsubst $(TEST)/%.cpp, $(OBJ)/%.o, $(SRCS_TEST))

all: $(TARGET) $(TARGET_TEST)

$(TARGET): $(OBJS)
	ar -crs $@ $^

$(TARGET_TEST): $(OBJS_TEST)
	$(CC) -o $@ $^ $(GLEW_LIBS) $(GLFW_LIBS) $(GTEST) $(SMATH)

# comile test src files
$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p $(@D)
	$(CC) -c $< -o $@

# comile test src files
$(OBJ)/%.o: $(TEST)/%.cpp
	@mkdir -p $(@D)
	$(CC) -c $< -o $@

# Clean up object and executeble files
clean:
	@echo "Cleaning up..."
	@rm -rf $(BIN)/*