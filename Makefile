# Name of executable
PROGRAM_NAME = OpenGL_Odyssey
PROGRAM_NAME_TEST = OpenGL_Odyssey_Test

# Compiler
CC = g++

# Libraries
GLEW_LIBS = -lGLEW -lEGL -lGL -lGLU -lOpenGL 
GLFW_LIBS = -lglfw
GTEST = $(shell pkg-config --libs gtest)
SMATH = -lsmath -L./libs/SMath/bin/
IMGUI = -limgui -L./libs/ImGui/

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

# Build main program
all: $(TARGET)

# Build test program
test: $(TARGET_TEST)
	@$(TEST_TARGET)

# Link main program
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(GLEW_LIBS) $(GLFW_LIBS) $(GTEST) $(SMATH) $(IMGUI)

# Link test program
$(TARGET_TEST): $(OBJS_TEST) $(filter-out $(OBJ)/main.o, $(OBJS))
	$(CC) -o $@ $^ $(GLEW_LIBS) $(GLFW_LIBS) $(GTEST) $(SMATH) $(IMGUI)

# comile main program src files
$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p $(@D)
	$(CC) -c $< -o $@

# comile src files for tests
$(OBJ)/%.o: $(TEST)/%.cpp
	@mkdir -p $(@D)
	$(CC) -c $< -o $@

# Clean up object and executeble files
clean:
	@echo "Cleaning up..."
	@rm -rf $(BIN)/*