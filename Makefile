PROGRAMM_NAME = OpenGL_Odyssey

GLEW_LIBS = -lGLEW -lEGL -lGL -lGLU -lOpenGL 
GLFW_LIBS = -lglfw
SMATH = -lsmath -L./libs/SMath/bin/
IMGUI = -limgui -L./libs/ImGui/

CC = g++
SRC = src
BIN = bin
OBJ = obj

TARGET = $(BIN)/$(PROGRAMM_NAME)
SRCS = $(wildcard $(SRC)/*.cpp)
OBJS = $(patsubst $(SRC)/%.cpp, $(BIN)/$(OBJ)/%.o, $(SRCS))

all:$(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(GLEW_LIBS) $(GLFW_LIBS) $(SMATH) $(IMGUI)

bin/obj/%.o: $(SRC)/%.cpp
	g++ -c $< -o $@

clean:
	rm $(BIN)/* $(BIN)/$(OBJ)/*