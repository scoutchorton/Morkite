# Project: Morkite

A pocket monster type game engine and implementation using C++, Lua, and SDL.

# Installing From Source

## Windows

### MinGW

1. Install the prerequisite packages with the following command:

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