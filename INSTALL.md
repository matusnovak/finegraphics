# Installing

You can compile the FineGraphics from the source code (see below), or [use one of the automatically built releases from GitHub Releases](https://github.com/matusnovak/finegraphics/releases).

### Linux

Install this packages before compiling. These are needed for git, cmake, g++, OpenGL, and X11. 
When distributing an application linked with FineGraphics, these packages are not required for the users.

```bash
sudo apt install build-essential git cmake xorg-dev libgl1-mesa-glx libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev mesa-common-dev
```

Then, compile from the source code:

```bash
# Clone the repository
git clone https://github.com/matusnovak/finegraphics
cd finegraphics

# Download the dependencies
git submodule init
git submodule update

# Create build folder and run cmake
mkdir build
cd build

# You can add -G "Unix Makefiles" right after .. if you wish
cmake ..  -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=MinSizeRel

# Build
make all

# Optionally run the INSTALL step
sudo make install
```

### Windows

```bash
# Clone the repository
git clone https://github.com/matusnovak/finegraphics
cd finegraphics

# Download the dependencies
git submodule init
git submodule update

# Create build folder and run cmake
mkdir build
cd build

# You can replace the "Visual Studio 15 2017" with 
# "Visual Studio 15 2017 Win64" to compile for 64-bit applications.
# You can also replace it with -G "MinGW Makefiles"
cmake .. -G "Visual Studio 15 2017" -DCMAKE_INSTALL_PREFIX=C:/...

# Build using cmake (or open it in Visual Studio IDE)
cmake --build . --target ALL_BUILD --config MinSizeRel

# Optionally run the INSTALL
cmake --build . --target INSTALL --config MinSizeRel
```
