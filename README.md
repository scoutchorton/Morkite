# Project: Morkite

A pocket monster type game engine and implementation using C++, Lua, and SDL.

# Installing From Source

## Linux

### Debian/Ubuntu

1. Install the prerequisite packages

   ```bash
   sudo apt update
   #sudo apt install git build-essential pkg-config lua5.4 liblua5.4-0 liblua5.4-0-dbg liblua5.4-dev libsdl2-2.0-0 libsdl2-dev libsdl2-image-2.0-0 libsdl2-image-dev
   sudo apt install git build-essential cmake lua5.4 liblua5.4-0 liblua5.4-0-dbg liblua5.4-dev libsdl2-2.0-0 libsdl2-dev libsdl2-image-2.0-0 libsdl2-image-dev
   ```

1. Clone the repository

   ```bash
   git clone https://github.com/scoutchorton/Morkite.git
   cd Morkite
   ```

1. Compile the project

   ```bash
   mkdir build
   cmake ../
   ```

## Windows

### MinGW

1. Install the prerequisite packages

   ```bash
   pacman -Syu
   pacman -S git gcc make pkg-config mingw-w64-$(uname -m)-lua mingw-w64-$(uname -m)-SDL2
   ```

1. Clone the repository

   ```bash
   git clone https://github.com/scoutchorton/Morkite.git
   cd Morkite
   ```

1. Compile the project

   ```bash
   CFLAGS='-I/mingw64/include/' make
   ```



@todo add SDL2-image to instrcutions