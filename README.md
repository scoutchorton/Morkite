# Project: Morkite

A pocket monster type game engine and implementation using C++, Lua, and SDL.

## Installing From Source

### Linux

1. Install the prerequisite packages
   #### Debian/Ubuntu

   ```bash
   sudo apt update
   sudo apt install git build-essential cmake lua5.4 liblua5.4-0 liblua5.4-0-dbg liblua5.4-dev libsdl2-2.0-0 libsdl2-dev libsdl2-image-2.0-0 libsdl2-image-dev
   ```

   #### Arch

   ```bash
   sudo pacman -Syy
   sudo pacman -S cmake lua sdl2 sdl2_image base-devel git
   ```

1. Clone the repository

   ```bash
   git clone https://github.com/scoutchorton/Morkite.git
   cd Morkite
   ```

1. Compile the project

   ```bash
   mkdir build
   cd build
   cmake ../
   make
   ```

1. Package and install

   ```bash
   make package
   sudo dpkg -i morkite_0.1.0_amd64.deb # Adjust filename for platform
   ```

### Windows

#### Visual Studio

1. Open Visual Studio and click `Clone a repository`

1. Enter this repository's URL (`https://github.com/scoutchorton/Morkite.git`) and pick a folder to clone to

1. Open the project in folder view

1. Right click `CMakeLists.txt` and click `Configure cache`

1. On the ribbon, click `Build > Build All`

#### MinGW

**Work in progress**

1. Install the prerequisite packages

   ```bash
   pacman -Syu
   pacman -Sy
   pacman -S git mingw-w64-$(uname -m)-cmake mingw-w64-$(uname -m)-clang
   ```

1. Clone the repository

   ```bash
   git clone https://github.com/scoutchorton/Morkite.git
   cd Morkite
   ```

1. Compile the project

   ```bash
   mkdir build
   cd build
   cmake ../
   ninja # @todo still doesn't work
   ```

### macOS

**Work in progress**

## Todos

### README/Documentation

- [ ] Prereq instructions
  - [x] Linux (dpkg)
  - [ ] Linux (rpm)
  - [ ] Linux (source)
  - [ ] Windows (Visual Studio)
    - [ ] Installing Visual Studio
  - [ ] Windows (MinGW)
    - [ ] Extra steps for MSYS2/MinGW?
  - [ ] macOS (through Homebrew)

### Planning

_See files in [planning directory](./planning/)_

- [ ] Engine specs
  - [ ] C++ internal classes
    - [ ] Sprite
    - [ ] Menu
    - [ ] Level
    - [ ] Scene
    - [ ] Engine
  - [ ] Lua API
    - [ ] Registration
      - [ ] Images
      - [ ] Scene
        - [ ] Levels
        - [ ] Menus
        - [ ] Sprites
    - [ ] Bindings to engine
- [ ] Game development
  - _**@todo** figure out steps needed once Lua API is established (stuff like sprite design, level design, etc.)_
- [ ] Misc
  - [ ] New engine name

### CMake

- [ ] Compiling
  - [x] Linux
  - [x] Windows (Visual Studio)
  - [ ] Windows (MinGW)
  - [ ] macOS
- [ ] Packaging/Installers
  - [x] Linux (dpkg)
  - [ ] Linux (rpm)
  - [ ] Windows (msi in Visual Studio)
  - [ ] Windows (exe in Visual Studio)
  - [ ] Windows (msi in MinGW)
  - [ ] Windows (exe in MinGW)
  - [ ] macOS
- [ ] Install (without package manager)
  - [ ] Linux
  - [ ] Windows
  - [ ] macOS

### Engine

_**@todo** make list, for now see [planning section](#planning) for list of things to implement_

### Game content

_**@todo** make list, for now see [planning section](#planning) for list of things to create_

### Issues

- [ ] Finish/fix issues with MinGW (can't link to libraries or something like that)

### Future

- [ ] Store game information in separate file, like Doom's WAD files
  - [ ] Create game package information (like a Node.js `package.json` file)
  - [ ] Include extra utilities for managing game contents (probably in Lua or Python, TBD)
  - [ ] Migrate current game assets and scripts to new format
- [ ] Add online capabilities
  - [ ] Move server side to separate project?
  - [ ] Determine level of involvement (only a link/trading system or some item market, or all the way up to MMO type stuff)