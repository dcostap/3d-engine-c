INCLUDES = -Iinclude -Iinclude/SDL/include -Iinclude/SDL2_gfx

# For windows (WSL)
# LIBS = -Llibs -lSDL2
LIBS = -Llibs -lSDL2 -lm

CFLAGS = -Wall -Wextra -pg -std=c99 -pedantic -Wno-unused-parameter

# For windows (WSL)
# CC = x86_64-w64-mingw32-gcc

CC = gcc

build/app: $(wildcard src/*.c) $(wildcard src/assets/*.c)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) $(INCLUDES)
	cp libs/* build/