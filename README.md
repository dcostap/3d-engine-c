## Workspace Setup
All the SDL libraries used are included in the `include` folder as _git submodules_ that point to the official repos. You need to clone their source code:

    git submodule update --init

Create the output `build` folder:

    mkdir build

## Compiling for Linux

    sudo apt-get install libsdl2-dev

https://github.com/libsdl-org/SDL/blob/main/docs/README-linux.md

Change `CC` and `LIBS` flag in `Makefile`.

Run `make` and open the output in `./build`.

Alternatively: `./linux_run.sh`

## Compiling for Windows (.exe) via WSL2

`apt install mingw-w64`

Change `CC` and `LIBS` flag in `Makefile`.

Run `make` and open the output in `./build`.

Alternatively: `./windows_run.sh`