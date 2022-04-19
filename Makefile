INCLUDES = -Iinclude -Iinclude/SDL/include -Iinclude/SDL2_gfx

CFLAGS = -Wall -Wextra -pg -std=c99 -pedantic -Wno-unused-parameter

# Windows (WSL)
LIBS = -lSDL2 -lopengl32
# Linux
# LIBS = -lSDL2 -lm -lGL

# Windows (WSL)
CC = x86_64-w64-mingw32-gcc
# Linux
# CC = gcc

build/app: $(wildcard src/*.c) $(wildcard src/assets/*.c)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) $(INCLUDES)
	cp libs/* build/