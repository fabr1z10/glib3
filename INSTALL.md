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
* MacOS High Sierra 10.13.6 + AppleClang 10.0.0.10001145 + XCode 10.0

# Get the source code

You can get the source code downloading a file from the latest
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
* Go to http://glew.sourceforge.net/ 
* Get the windows binaries
* Copy the `glew32.dll` in `bin/Release/x64` into `c:/windows/System32` 
* Copy `glew32.lib` and `glew32s.lib` in `lib/Release/x64` into `{VC Root}/lib/x64`
* Copy the content of the include folder in `{VC Root}/include`

### GLFW

Get the source code from https://www.glfw.org/, and unzip it. Open up a MS Visual Studio command prompt and in the root folder type:
    
    cd build
    cmake .. 
    MSBuild GLFW.sln /p:Configuration=Release
    cmake cmake_install.cmake

This will create a `GLFW` folder in your `C:\Program Files` folder. However (I don't know why, if anyone does please let me know) it looks like I need to rename GLFW into glfw3 to make it work.

### GLM

This is a header-only library. Download the latest release from https://glm.g-truc.net. Copy the `glm` include folder (the one containing `glm.hpp`) in `{VC Root}/include`.

### ZLIB (required by PNG library)

Go to https://www.zlib.net/ and download the source code. Unzip it, open a MS Visual Studio prompt and cd to the root folder of the unzipped file. Type the following:

    mkdir build
    cd build
    cmake ..
    msbuild zlib.sln /p:Configuration=Release
If everything goes well, you should have a `Release` folder inside the `Build` folder containing the binary files. Now copy `zlib.lib` and `zlibstatic.lib` into `{VC Root}\lib\x64`, and copy `zlib.dll` into `c:\windows\system32`. Also, copy the header file `zlib.h` and `build\zconf.h` in `{VC Root}\include`.

### PNG

Go to http://www.libpng.org/pub/png/libpng.html and get the latest source code. Unzip it, open a MS Visual Studio prompt and cd to the root folder of the unzipped file. Type the following:

    mkdir build
    cd build
    cmake ..
    msbuild libpng.sln /p:Configuration=Release
You should now have a `Release` folder inside the `Build` folder containing the binary files. Copy `libpng16.lib` and `libpng16_static.lib` into `{VC Root}\lib\x64`. Copy `libpng16.dll` into `c:\windows\system32`. Also copy `png.h`, `pngconf.h` and `build\pnglibconf.h` in `{VC Root}\include`.

### JPG

Get the `JPEG` lib package from https://www.nuget.org/packages/libjpeg/.

### FreeType

Go to the Freetype main page https://www.freetype.org/. In the Download section, you should find a link to a GitHub repository with the latest binary files. Get the latest release, unzip it and cd to the newly created folder. You will find the binaries in the `win64` folder. Copy `freetype.lib` in `{VC Root}\lib\x64`, `freetype.dll` in `c:\windows\system32`, and the contents of the `include` folder in `{VC Root}\include`.

### LUA

Get the Windows binaries from http://luabinaries.sourceforge.net/download.html. Copy the `lua53.dll` in `c:\windows\system32` and `lua53.lib` into `{VC Root}\lib\x64`. Also, copy the content of the `include` folder in `{VC Root}\include`.

### BOOST

## macOS details

You can install the dependencies using brew

    brew install glew
    brew install glfw3
    brew install glm
    brew install libpng
    brew install libjpeg
    brew install freetype
    brew install lua
    brew install boost

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
