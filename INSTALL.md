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
* Python (https://www.python.org)

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

Go to https://www.zlib.net/ and download the source code. Unzip it, open a MS Visual Studio prompt with admin rights and type in the following:

    md build
    cd build
    cmake ..
    msbuild INSTALL.vcxproj /p:Configuration=Release

This should build and install the library in a proper location (should be in `c:\Program Files (x86)\zlib` or the like).

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

Go to the Freetype main page https://www.freetype.org/ and download the latest stable release. Unzip it, and in a MS Visual Studio prompt (run it as administrator) type in the following:

    md build
	cd build
	cmake .. -DBUILD_SHARED_LIBS:BOOL=TRUE
	msbuild INSTALL.vcxproj /p:Configuration=Release 

This will build the library and install it in the proper location, typically in a `freetype` folder in `C:\Program Files (x86)` or similar.

### YAML

You can find this library at https://github.com/jbeder/yaml-cpp. Download and unzip the latest release, then in the root folder type:

	md build && cd build
	cmake ..
	msbuild INSTALL.vcxproj /p:Configuration=Release

### Python

Go to https://www.python.org/ and grab and install the latest release for Windows. This should install all the components required by the engine.

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
    sudo apt-get install python-dev python3-dev
