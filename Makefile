# # the build/windows.exe target builds a .exe, but it must still be compiled from linux. You can use WSL2

# # default target
# # .DEFAULT_GOAL := build/linux

# # use make <target> to choose
# # TARGET = build/windows.exe build/linux

# INCLUDES = -Iinclude -Iinclude/SDL/include -Iinclude/SDL2_gfx -Iinclude/glew/include
# CFLAGS = -Wall -Wextra -pg -std=c99 -Wno-unused-parameter -Wno-unknown-pragmas

# SOURCE_FILES = $(wildcard src/*.c) $(wildcard src/models/*.c) $(wildcard src/png/*.c)
# OBJECT_FILES=$(subst ./src, ./obj, $(SRC:.c=.o))

# # build/windows.exe: LIBS = -Llibs -lSDL2 -lopengl32 -lglew32
# all: LIBS = -lSDL2 -lm -lGLEW -lGLU -lGL

# # build/windows.exe: CC = x86_64-w64-mingw32-gcc
# all: CC = gcc

# # all: $(SOURCE_FILES) $(TARGET)

# # $(TARGET): $(OBJECT_FILES)
# # 	$(CC) $(LIBS) $(OBJECT_FILES) -o $@

# ./obj/%.o: ./src/%.c
# 	$(CC) $(LIBS) $(CFLAGS) $(INCL) -o $@ $<

# clean:
# 	cp libs/* build/
# 	rm -rf build/assets/*
# 	rsync -av --progress assets/ build/assets



OUTDIRS := build obj/models obj/png
SRCFILES := $(wildcard src/*.c) $(wildcard src/models/*.c) $(wildcard src/png/*.c)

INCLUDES = -Iinclude -Iinclude/SDL/include -Iinclude/SDL2_gfx -Iinclude/glew/include
CFLAGS = -Wall -Wextra -pg -std=c99 -Wno-unused-parameter -Wno-unknown-pragmas -O0

EXE := linux
FULL_OUTPUT := build/${EXE}

.PHONY: default all test release clean dirs

OBJFILES := $(patsubst src/%.c,obj/%.o,$(SRCFILES))
DEPFILES := $(patsubst src/%.c,obj/%.d,$(SRCFILES))

all: dirs clean linux
default: linux

linux: CC := gcc
windows: CC := x86_64-w64-mingw32-gcc

linux: LIBS := -lSDL2 -lm -lGLEW -lGLU -lGL
windows: LIBS := -Llibs -lSDL2 -lopengl32 -lglew32

dirs:
	@mkdir -p  $(OUTDIRS)

linux: $(FULL_OUTPUT)
windows: $(FULL_OUTPUT)

test:
	@echo OBJFILES = $(OBJFILES)
	@echo SRCFILES = $(SRCFILES)
	@echo DEPFILES = $(DEPFILES)

clean:
	rm -f $(OBJFILES) $(DEPFILES) $(EXE)

${FULL_OUTPUT}: $(OBJFILES)
	cp libs/* build/
	rm -rf build/assets/*
	rsync -av -q assets/ build/assets

	$(CC) $(LIBS) $(CFLAGS) $(INCLUDES) $(OBJFILES) -o $(FULL_OUTPUT)
	strip $(FULL_OUTPUT)
	@echo ""
	@echo "✅ Created release binary 🚀"
	@echo "./$(FULL_OUTPUT) "

-include $(DEPFILES)

obj/%.o: src/%.c
	$(CC) $(RELFLAGS) $(LIBS) $(CFLAGS) $(INCLUDES) -MMD -MF $(patsubst obj/%.o, obj/%.d, $@) -c $< -o $@
