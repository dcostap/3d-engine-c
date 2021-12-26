INCLUDES = -Iinclude -ISDL/include -ISDL2_gfx
LIBS = -Llibs -lSDL2
CFLAGS = -Wall

SRC=$(wildcard ./src/*.c)

test: $(SRC)
	x86_64-w64-mingw32-gcc -o build/$@ $^ $(CFLAGS) $(LIBS) $(INCLUDES)
	cp libs/* build/