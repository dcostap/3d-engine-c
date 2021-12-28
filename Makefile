INCLUDES = -Iinclude -ISDL/include -ISDL2_gfx
LIBS = -Llibs -lSDL2
CFLAGS = -Wall -Wextra -O2 -std=c99 -pedantic
CC = x86_64-w64-mingw32-gcc

SRC = $(wildcard src/*.c)

build/test.exe: $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) $(INCLUDES)
	cp libs/* build/