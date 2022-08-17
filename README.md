# Barrel (Work in progress)

<img alt="barrel" align="right"
     src="https://user-images.githubusercontent.com/29029116/182253248-76daa80d-21b9-40bb-aa58-0911973c3330.svg" width="300"/>

#### [C++ wrapper for the Homebrew CLI]

[![GitHub](https://img.shields.io/badge/Source--ffffff?style=social&logo=github)](https://github.com/aydwi/barrel)
[![Twitter](https://img.shields.io/twitter/url?label=Share&style=social&url=https%3A%2F%2Fgithub.com%2Faydwi%2Fbarrel)](https://twitter.com/intent/tweet?text=Barrel%20-%20A%20C%2B%2B%20wrapper%20for%20the%20Homebrew%20CLI:&url=https%3A%2F%2Fgithub.com%2Faydwi%2Fbarrel)


&nbsp;


Barrel is a portable, header-only C++ library that provides programmatic access to the [Homebrew](https://brew.sh) command line interface.

It is intended to help build generic, non-trivial wrappers around Homebrew. For example, using Barrel, you could write a feature-rich GUI frontend for Homebrew on macOS. Or it could be used to develop bespoke tooling to customize/automate Homebrew-based package configuration for your CI/CD jobs. Or it could help you work with homebrew on headless systems.


###### *tl;dr: Use Barrel whenever you want to interact with Homebrew and the shell interface just doesn't cut it.*


Barrel is highly performant, with almost no runtime overhead ([see benchmarks](https://github.com/aydwi/barrel/wiki/Benchmarking-%22Homebrew-via-Barrel%22-against-Homebrew)). It exposes a well documented, succinct C++ API ([see reference](https://barrel.wiki/barrel_8h.html)) which can be integrated with a wide variety of libraries, tools and frameworks ([see examples](https://github.com/aydwi/barrel/wiki)).


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


## Features

* Header-only; no need to build before using
* Self contained; no external dependencies
* Readable, modern C++ source; easy to modify if needed
* Negligible runtime overhead

* Powerful ways to interact with Homebrew:
     * Validate and configure your Homebrew installation
     * Chain and execute _any_ arbitrary `brew` command (except those which read from `stdin` interactively, if any)
     * Capture exit status, and `stdout`, `stderr`, or both
     * ![WIP](https://img.shields.io/badge/WIP-red?style=flat-square) Execute long running `brew` commands asynchronously (with support for early binding/delayed invocation) <sup>[**[1]**](https://github.com/aydwi/barrel#1-helpful-for-example-when-writing-a-gui-wrapper-where-you-would-not-want-to-run-a-compute-heavy-routine-on-the-main-thread-to-keep-the-gui-responsive)</sup>
     * ![WIP](https://img.shields.io/badge/WIP-red?style=flat-square) Live-capture/poll output stream (`stdout`/`stderr`) data from a `brew` command as it is being generated <sup>[**[2]**](https://github.com/aydwi/barrel#2-again-helpful-when-writing-an-interactivereal-timegui-wrapper-around-homebrew-anecdotally-i-have-been-using-cakebrew-which-distinctly-lacks-this-functionality-as-of-v13-which-motivated-me-to-start-this-project-in-the-first-place-i-wanted-the-ability-to-see-what-was-going-on-on-stdoutstderr-in-real-time-as-opposed-to-getting-a-bulk-of-text-dumped-at-once-after-the-execution-was-finished-i-like-cakebrew-but-perhaps-i-will-write-my-own-gui-for-homebrew-at-some-point-using-barrel-and-slint)</sup>
     * ![WIP](https://img.shields.io/badge/WIP-red?style=flat-square) Execute `brew` commands on multiple threads on multi-core machines


&nbsp;


## Elaborate example

Now let's take a look at another example which shows how a client can use some of the advanced functionality offered by Barrel.

```cpp

```


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

* Make
* CMake (3.15 or higher)


&nbsp;


## Getting started

1. Get the source (`git clone` for the latest developmental version, or get a versioned [release](https://github.com/aydwi/barrel/releases))

2. Build Barrel

     `mkdir build && cd $_`

     `cmake ..` 

     `cmake --build . --target install`

     These steps do the following: **1.** Create and enter a `build` directory in the project root, **2.** Configure the project and prepare a build configuration for the actual build system (Make in my case), and **3.** Call Make to build Barrel (by compiling/linking however specified), executing the predefined `install` target to install the library. You should see an `install/` directory in the project root after step 3. Since Barrel is header-only, all the sources in `include/` simply [get copied over](https://github.com/aydwi/barrel/blob/master/CMakeLists.txt#L58) to `install/Barrel/include/`.

Alternatively, you could [**download a pre-built archive**](https://github.com/aydwi/barrel/wiki/Getting-a-pre-built-archive-of-Barrel).


&nbsp;


## Linking to Barrel

Link to Barrel from your project:

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
* CI Server: [CircleCI](https://circleci.com/)


&nbsp;


## Build and test status


[![CircleCI](https://dl.circleci.com/status-badge/img/gh/aydwi/barrel/tree/master.svg?style=svg)](https://dl.circleci.com/status-badge/redirect/gh/aydwi/barrel/tree/master)


&nbsp;


## Footnotes

###### [1] Helpful, for example, when writing a GUI wrapper where you wouldn't want to block the main (UI) thread by running some compute-heavy routine.

###### [2] Again, helpful when writing an interactive/real-time/GUI wrapper around Homebrew. Anecdotally, I have been using [Cakebrew](https://github.com/brunophilipe/Cakebrew) which distinctly lacks this functionality (as of v1.3), which motivated me to start this project in the first place. I wanted the ability to see what was going on on `stdout`/`stderr` in real-time as opposed to getting a bulk of text dumped at once after the execution was finished. I like Cakebrew, but perhaps I will write my own GUI for Homebrew at some point using Barrel and [Slint](https://github.com/slint-ui/slint).
