## Workspace Setup
All the libraries linked against are included in the `include` folder as _git submodules_ that point to the official repos. You need to clone their source code:

    git submodule update --init

Create the output `build` folder:

    mkdir build

Create more output folders (I need to automate this in the Makefile somehow:):

    mkdir obj
    mkdir obj/anims
    mkdir obj/models
    mkdir obj/png

Generate the 3D assets:

    python3 process_assets.py

## Compiling for Linux

    sudo apt-get install libsdl2-dev libsdl2-gfx-dev libsdl2-image-dev
    sudo apt-get install libglew-dev

https://github.com/libsdl-org/SDL/blob/main/docs/README-linux.md

Run `make build/linux` and open the output in `./build`.

Alternatively: `./linux_run.sh`

## Compiling for Windows (generating .exe), via WSL2

`apt install mingw-w64`

Run `make -s windows` and open the output in `./build`.

Alternatively: `./windows_run.sh`