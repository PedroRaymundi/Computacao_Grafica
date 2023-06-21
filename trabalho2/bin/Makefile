SRC_FILES = ../lib/*.cpp ../lib/scenes/*.cpp ../src/glad.c ../src/*.cpp
LINUX_FLAGS = -ldl -lglfw -lGL -lGLEW -std=c++17
LINUX_DEBUG_FLAGS = $(LINUX_FLAGS) -ggdb3 -pedantic -Wall -Wextra
WINDOWS_FLAGS = -g -static-libgcc -static-libstdc++ -lm --std=c++17

windows:
	g++ -I../include -L../lib $(SRC_FILES) ../lib/glfw3dll.lib $(WINDOWS_FLAGS) -o main
linux:
	g++ -I../include/ -L../lib $(SRC_FILES) $(LINUX_FLAGS) -o main
linux-debug:
	g++ -I../include/ -L../lib $(SRC_FILES) $(LINUX_DEBUG_FLAGS) -o main
