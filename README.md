## Workspace Setup
All the SDL libraries used are included in the `include` folder as _git submodules_ that point to the official repos. You need to clone their source code:

    git submodule update --init

Create the output `build` folder:

    mkdir build

Make the necessary changes to the `Makefile` to get the project compiling in your platform, you may need to change i.e. the `LIBS` or `CC` flags.

Compile the project:

    make

## Building a Windows executable (.exe) file via WSL2

`apt install mingw-w64`

Change `CC` flag in `Makefile`.