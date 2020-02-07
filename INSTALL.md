# Table of contents

* [Platforms](#platforms)
* [Get the source code](#get-the-source-code)
* [Dependencies](#dependencies)
* [Compiling](#compiling)
  * [Windows details](#windows-details)
  * [macOS details](#macos-details)
  * [Linux details](#linux-details)

# Platforms

So far I've compiled glib3 succesfully on the following platforms:

* Windows 10 + Visual Studio Community 2019
* Linux + gcc 7.4.0

I will update this info as soon as I'm able to build succesfully on macOS too.

# Get the source code

You can get the source code downloading a xyz file from the latest
glib3 release

https://github.com/fabr1z10/glib3/releases

You can also clone the repository using the command:

    git clone https://github.com/fabr1z10/glib3.git

# Dependencies

The library requires the following packages installed in your system. More details on how to install each of them for specific platforms in the #compiling section.

* GLEW (http://glew.sourceforge.net/)
* GLFW (https://www.glfw.org/)
* glm (https://glm.g-truc.net/0.9.9/index.html)
* FreeType (https://www.freetype.org/)
* PNG library (http://www.libpng.org/pub/png/libpng.html)
* JPEG library (http://ijg.org/)
* LUA (https://www.lua.org/home.html)
* Boost (only the filesystem component) (https://www.boost.org/)

You also need CMake to build the engine.

# Compiling

## Windows details

Below you can find some instructions on how to install the dependencies on Windows. In this section, {VC Root} refers to the root where your C++ compiler in installed. For instance, in my setup it is in `C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\MSVC\14.23.28105`

### GLEW
* Go to glew.sourceforge.net/ 
* Get the windows binaries
* Copy the `glew32.dll` in `bin/Release/x64` into `c:/windows/System32` 
* Copy `glew32.lib` and `glew32s.lib` in `lib/Release/x64` into `{VC Root}/lib/x64`
* Copy the content of the include folder in `{VC Root}/include`

## Linux details

You can install the required packages with the following by typying

    sudo apt-get install freeglut3-dev
    sudo apt-get install libglew-dev
    sudo apt-get install libglfw3 libglfw3-dev
    sudo apt-get install libglm-dev
    sudo apt-get install libfreetype6 libfreetype6-dev
    sudo apt-get install libjpeg-dev
    sudo apt-get install libpng-dev
    sudo apt-get install liblua5.3-dev
