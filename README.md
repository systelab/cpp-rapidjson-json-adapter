[![Build Status](https://travis-ci.org/systelab/cpp-rapidjson-json-adapter.svg?branch=master)](https://travis-ci.org/systelab/cpp-rapidjson-json-adapter)
[![Build status](https://ci.appveyor.com/api/projects/status/qdrjivrs26gf46lo?svg=true)](https://ci.appveyor.com/project/systelab/cpp-rapidjson-json-adapter)
[![codecov](https://codecov.io/gh/systelab/cpp-rapidjson-json-adapter/branch/master/graph/badge.svg)](https://codecov.io/gh/systelab/cpp-rapidjson-json-adapter)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/492f2b284cd149018ec9dd54a45d53df)](https://www.codacy.com/app/systelab/cpp-rapidjson-json-adapter?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=systelab/cpp-rapidjson-json-adapter&amp;utm_campaign=Badge_Grade)

# C++ JSON Adapter implementation for rapidjson

## Download

Remember to clone the repository with "--recursive" flag, otherwise the 'cpp-json-adapter' will not be downloaded.

## Build

The easiest way to deal with the cpp-rapidjson-json-adapter is just open the "CMakeLists.txt" with your QtCreator. However, since it is a CMake project, you don't really need an "IDE" to work with. 

You can build the project from source directly from command line following these steps:  

(In cpp-rapidjson-jsondb-adapter folder)  

	$mkdir build  
	$cd build  
	$cmake ..

Windows:  

	-	CMake will create a Visual Studio Solution from where you can easily modify and compile your project.  

POSIX:  
	-	CMake will create a Makefile from where you can build your binaries by simply calling "$make" command.  
