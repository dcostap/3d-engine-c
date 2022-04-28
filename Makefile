# the build/windows.exe target builds a .exe, but it must still be compiled from linux. You can use WSL2

# default target
.DEFAULT_GOAL := build/linux

# use make <target> to choose
TARGETS= build/windows.exe build/linux

INCLUDES = -Iinclude -Iinclude/SDL/include -Iinclude/SDL2_gfx -Iinclude/glew/include

CFLAGS = -Wall -Wextra -pg -std=c99 -Wno-unused-parameter -Wno-unknown-pragmas

build/windows.exe: LIBS = -Llibs -lSDL2 -lopengl32 -lglew32
build/linux: LIBS = -lSDL2 -lm -lGLEW -lGLU -lGL

build/windows.exe: CC = x86_64-w64-mingw32-gcc
build/linux: CC = gcc

$(TARGETS):$(wildcard src/*.c) $(wildcard src/models/*.c) $(wildcard src/png/*.c)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) $(INCLUDES)
	cp libs/* build/
	rm -rf build/assets/*
	rsync -av --progress assets/ build/assets
