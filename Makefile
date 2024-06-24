# Name of executable
PROGRAM_NAME = Forest_Frenzy
PROGRAM_NAME_TEST = Forest_Frenzy_Test

# Compiler
CC = g++ -std=c++17

# Libraries
GLEW_LIBS = -lGLEW -lEGL -lGL -lGLU -lOpenGL 
GLFW_LIBS = -lglfw
# GTEST = $(shell pkg-config --libs gtest)
SMATH = -lsmath -L./libs/SMath/bin/

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
OBJS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

all:$(TARGET)

# Link main program
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(GLEW_LIBS) $(GLFW_LIBS) $(SMATH)

# comile main program src files
$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p $(@D)
	$(CC) -c $< -o $@

# Clean up object and executeble files
clean:
	@echo "Cleaning up..."
	@rm -rf $(BIN)/*