OUTDIRS := build obj/models obj/png obj/anims
SRCFILES := $(wildcard src/*.c) $(wildcard src/models/*.c) $(wildcard src/png/*.c) $(wildcard src/anims/*.c)

INCLUDES = -Iinclude -Iinclude/SDL/include -Iinclude/SDL2_gfx -Iinclude/glew/include
CFLAGS = -Wall -Wextra -pg -std=c99 -Wno-unused-parameter -Wno-unknown-pragmas -O0

.PHONY: default all test release clean dirs

OBJFILES := $(patsubst src/%.c,obj/%.o,$(SRCFILES))
DEPFILES := $(patsubst src/%.c,obj/%.d,$(SRCFILES))

all: dirs clean linux
default: linux

linux: EXE := app
windows: EXE := app.exe

FULL_OUTPUT = build/${EXE}

linux: CC := gcc
windows: CC := x86_64-w64-mingw32-gcc

linux: LIBS := -lSDL2 -lm -lGLEW -lGLU -lGL
windows: LIBS := -Llibs -lSDL2 -lglew32 -lopengl32

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

	$(CC) $(CFLAGS) -g $(OBJFILES) $(LIBS) $(INCLUDES) -o $(FULL_OUTPUT)
	@echo ""
	@echo "✅ Created release binary 🚀"
	@echo "./$(FULL_OUTPUT) "

-include $(DEPFILES)

obj/%.o: src/%.c
	$(CC) $(RELFLAGS) $(LIBS) $(CFLAGS) $(INCLUDES) -g -MMD -MF $(patsubst obj/%.o, obj/%.d, $@) -c $< -o $@
