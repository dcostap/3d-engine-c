INCLUDES = -Iinclude -ISDL/include -ISDL2_gfx
LIBS = -Llibs -lSDL2
CFLAGS = -Wall -std=c99
CC = x86_64-w64-mingw32-gcc

SRC = $(wildcard src/*.c)

all: $(SRC)
	$(CC) -o build/$@ $^ $(CFLAGS) $(LIBS) $(INCLUDES)
	cp libs/* build/