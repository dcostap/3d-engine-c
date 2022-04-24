INCLUDES = -Iinclude -Iinclude/SDL/include -Iinclude/SDL2_gfx

CFLAGS = -Wall -Wextra -pg -std=c99 -Wno-unused-parameter -Wno-unknown-pragmas

# Windows (WSL)
# LIBS = -Llibs -lSDL2 -lopengl32
# Linux
LIBS = -lSDL2 -lm -lGL

# Windows (WSL)
# CC = x86_64-w64-mingw32-gcc
# Linux
CC = gcc

build/app:$(wildcard src/*.c) $(wildcard src/models/*.c)
	rm -rf build/*
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) $(INCLUDES)
	cp libs/* build/
	rsync -av --progress assets/ build/assets --exclude models
