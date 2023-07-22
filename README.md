# Galaxy
## A modular set of tools grouped in an app, made in C++ with Qt6
---
### Table of contents
 - [Modules](#modules)
 - [Download](#download) *SOON*
 - [Build and Run](#build-and-run)
 - [Contact](#contact)
 - [Coding conventions](#coding-conventions)
 - [License](#license)

## Modules
There is only one module for now :  
 - [x] To-Do Lists
 - [ ] Calendar
 - [ ] Terminal
 - *and more soon*

## Download *SOON*

## Build and Run
### Dependencies
- Qt5 (Widgets)
- Pthread

### Install the dependencies
**On Ubuntu 22.04 or later**
```shell
$ sudo apt-get install qt6-base-dev libpthread-stubs0-dev
```

**On Windows (with [vcpkg](https://github.com/microsoft/vcpkg/#quick-start-windows)) :**
```shell
> vcpkg install qt6 pthreads
```

**On MacOS (with [Homebrew](https://brew.sh/index)) :**
```shell
$ brew install qt6 libpthread-stubs
```

You will also need [CMake](https://cmake.org/download/) in your system PATH (Minimum version : 3.1.0)
### Build
In 'Galaxy' (top) folder :  
On Windows **NEED TO BUILD EACH MODULE INDIVIDUALLY** (they are in the 'modules' folder) :  
```shell
cmake .. -DCMAKE_TOOLCHAIN_FILE=(path/to/)vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build . -j 8 --config Release
```
Otherwise :
```shell
./build_modules.sh
cd build/
cmake .. 
cmake --build . -j 8
```
### Run
The executable is in the 'Galaxy/build' folder ;)  
The modules (*.glx) and their config files (*.yml) are in the 'Galaxy/build/modules' folder. 
## Contact
You can reach me by e-mail at this address: enyotoyrep@gmail.com or on Discord: yoen.
## Coding Conventions
If you want to contribute to this project, you must respect the coding conventions from Qt (https://wiki.qt.io/Coding_Conventions).
## License
[MIT License](https://en.wikipedia.org/wiki/MIT_License)

Copyright (c) 2023 EnyoYoen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.