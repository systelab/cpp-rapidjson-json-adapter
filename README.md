[![Build Status](https://travis-ci.org/systelab/cpp-rapidjson-json-adapter.svg?branch=master)](https://travis-ci.org/systelab/cpp-rapidjson-json-adapter)
[![Build status](https://ci.appveyor.com/api/projects/status/qdrjivrs26gf46lo?svg=true)](https://ci.appveyor.com/project/systelab/cpp-rapidjson-json-adapter)
[![codecov](https://codecov.io/gh/systelab/cpp-rapidjson-json-adapter/branch/master/graph/badge.svg)](https://codecov.io/gh/systelab/cpp-rapidjson-json-adapter)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/492f2b284cd149018ec9dd54a45d53df)](https://www.codacy.com/app/systelab/cpp-rapidjson-json-adapter?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=systelab/cpp-rapidjson-json-adapter&amp;utm_campaign=Badge_Grade)

# C++ JSON Adapter implementation for rapidjson

This repository implements the interface for the [C++ JSON Server Adapter](https://github.com/systelab/cpp-json-adapter) using [Rapidjson](http://rapidjson.org).

## Setup

### Build from sources

Prerequisites:
  - [Git](https://git-scm.com/)
  - [Conan](https://conan.io/)
  - [CMake](https://cmake.org/)
  - [Visual Studio](https://visualstudio.microsoft.com/) (only on Windows)
  - [GCC](https://gcc.gnu.org/) (only on Linux)

Build library with the following steps:
  1. Clone this repository in a local drive
  2. Make a build directory (i.e. `build/`)
  3. Install `conan` dependencies in the build directory
  4. Run `cmake` in the build directory to configure build targets
  5. Use `Visual Studio` (on Windows) or `make` (on Linux) to build the library

#### Windows
``` bash
> git clone https://github.com/systelab/cpp-rapidjson-json-adapter
> md build && cd build
> conan install .. -s arch=x86
> cmake ..
> devenv.exe RapidJSONAdapter.sln
```

#### Linux
``` bash
> git clone https://github.com/systelab/cpp-boostasio-webserver-adapter
> mkdir build && cd build
> conan install ..
> cmake .. -DCMAKE_BUILD_TYPE=[Debug | Coverage | Release]
> make
```

### Download using Conan (not available yet)

  1. Create/update your `conanfile.txt` to add this library as follows:

```
[requires]
RapidJSONAdapter/1.0.0@systelab/stable

[generators]
cmake
```

  2. Integrate Conan into CMake by adding the following code into your `CMakeLists.txt`:

```cmake
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
```

  3. Link against `${CONAN_LIBS}` when configuring your executables in CMake:

```cmake
set(MY_PROJECT MyProject)
add_executable(${MY_PROJECT} main.cpp)
target_link_libraries(${MY_PROJECT} ${CONAN_LIBS})
```

## Usage

```cpp
TBD
```
