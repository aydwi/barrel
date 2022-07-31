# Barrel (Work in progress)

<img alt="barrel" align="right"
     src="https://user-images.githubusercontent.com/29029116/182253248-76daa80d-21b9-40bb-aa58-0911973c3330.svg" width="300"/>

#### [C++ wrapper for the Homebrew CLI]
[![GitHub](https://img.shields.io/badge/GitHub--ffffff?style=social&logo=github)](https://github.com/aydwi/barrel)
[![GitHub issues](https://img.shields.io/github/issues/aydwi/barrel?style=social&logo=github)](https://github.com/aydwi/barrel/issues)
[![Twitter](https://img.shields.io/twitter/url?label=Tweet&style=social&url=https%3A%2F%2Fgithub.com%2Faydwi%2Fbarrel)](https://twitter.com/intent/tweet?text=Barrel%20-%20A%20C%2B%2B%20wrapper%20for%20the%20Homebrew%20CLI:&url=https%3A%2F%2Fgithub.com%2Faydwi%2Fbarrel)


&nbsp;


Barrel is a portable header-only C++ library that provides programmatic access to the [Homebrew](https://brew.sh) command line interface.

It is intended to help build generic, non-trivial wrappers around Homebrew. For example, using Barrel, you can write a GUI frontend for Homebrew on macOS. Or it can be used to develop bespoke tooling to customize/automate Homebrew-based package configuration for your CI/CD jobs. Or it can help you work with homebrew on headless systems.


*tl;dr: Use Barrel whenever you want to interact with Homebrew and the shell interface just doesn't cut it.*


Barrel exposes a [well documented](https://barrel.wiki/barrel_8h.html), succinct C++ API which can be integrated with a wide variety of libraries, tools and frameworks. Find more information in the [Wiki](https://github.com/aydwi/barrel/wiki).


&nbsp;


## Quick example

```cpp
#include <Barrel/barrel.h>
#include <iostream>

int main(int argc, char** argv) {
    Brew brew;
    std::cout << brew.getInstallPath();    // /usr/local/bin/brew
    std::cout << brew.getInstallVersion(); // Homebrew 3.5.4
    
    BrewCommand<BrewCommandType::Builtin> cmd(brew, BrewCommandType::Builtin::INFO);
    cmd.execute();
    std::cout << cmd.getExitStatus(); // 0
    std::cout << cmd.getStreamDump(); // 120 kegs, 75,556 files, 1.8GB
    
    return 0;
}
```

This is the "Hello, World!" equivalent of using Barrel. It creates a default `brew` object to set up Homebrew execution environment, then creates a `cmd` object to execute the command `brew info`, and finally prints the exit status and output of the executed command.


&nbsp;


## Elaborate example


&nbsp;


## Project goals and non-goals

[**See the Wiki**](https://github.com/aydwi/barrel/wiki/Goals-and-Non-goals)


&nbsp;


## Requirements

Barrel is a header-only library, written in [C++20](https://en.cppreference.com/w/cpp/20). Using it can be as simple as copying the `include/` directory in your project and importing the primary header like `"include/barrel.h"`. In most cases, however, you'd want to use a build system like [GNU Make](https://www.gnu.org/software/make/)/[Ninja](https://ninja-build.org/), and a build automation tool like [CMake](https://cmake.org/) to manage building your project.

Further, you need an installation of Homebrew. Barrel does not install Homebrew for you. A `brew` binary must be available somewhere in your environment before using Barrel, although it is not necessary for it to be present in `$PATH`.

#### Basic requirements

* macOS (10.15 or higher)
* Homebrew ([requirements](https://docs.brew.sh/Installation#macos-requirements))
* A C++ compiler ([C++20 or higher](https://en.cppreference.com/w/cpp/compiler_support)) and the accompanying toolchain

#### Optional requirements

* GNU Make
* CMake (3.15 or higher)


&nbsp;


## Getting started

1. Get the sources (git clone/[download](https://github.com/aydwi/barrel/archive/refs/heads/master.zip) for the latest developmental version, or get a versioned [release](https://github.com/aydwi/barrel/releases))

2. Build Barrel

     `mkdir build && cd $_`

     `cmake ..` 

     `cmake --build . --target install`

     These steps do the following: **1.** Create and enter a `build` directory in the project root, **2.** Configure the project and prepare a build configuration for the actual build system (Make in my case), and **3.** Call Make to build Barrel (by compiling/linking however specified), executing the predefined `install` target to install the library. You should see an `install/` directory in the project root after step 3. Since Barrel is header-only, all the sources in `include/` simply [get copied over](https://github.com/aydwi/barrel/blob/master/CMakeLists.txt#L58) to `install/Barrel/include/`.


3. Link to Barrel from your project

     * <ins>**As an external dependency**</ins>
    
          Say you have a project you want to include Barrel in, but you do not want to add Barrel to your project's source tree. In this case, you can include Barrel as an external dependency after building it.
          
          CMake [`find_package`](https://cmake.org/cmake/help/latest/command/find_package.html#find-package) makes it straightforward. I have included a simple CMakeLists.txt example you can consult at [`examples/external/CMakeLists.txt`](https://github.com/aydwi/barrel/blob/master/examples/cmake/external/CMakeLists.txt).

     * <ins>**As an internal dependency**</ins>


&nbsp;


## Credits

* Project Logo: [Vecteezy](https://www.vecteezy.com/free-vector/icons)
* Documentation Generator: [Doxygen](https://doxygen.nl/)
* Documentation Stylesheet: [Doxygen Awesome](https://jothepro.github.io/doxygen-awesome-css/)
* Documentation Host: [GitHub Pages](https://pages.github.com/)
