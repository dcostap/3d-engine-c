INCLUDES = -Iinclude -Iinclude/SDL/include -Iinclude/SDL2_gfx

# Windows (WSL)
LIBS = -Llibs -lSDL2

# Linux
# LIBS = -Llibs -lSDL2 -lm

CFLAGS = -Wall -Wextra -pg -std=c99 -pedantic -Wno-unused-parameter

# Windows (WSL)
CC = x86_64-w64-mingw32-gcc

# CC = gcc

build/app: $(wildcard src/*.c) $(wildcard src/assets/*.c)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) $(INCLUDES)
	cp libs/* build/