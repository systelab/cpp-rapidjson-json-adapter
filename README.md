[![Codacy Badge](https://api.codacy.com/project/badge/Grade/66db56a3ca3c4f19930201b4bfb655c0)](https://app.codacy.com/app/joaquimvila/cpp-rapidjson-json-adapter?utm_source=github.com&utm_medium=referral&utm_content=systelab/cpp-rapidjson-json-adapter&utm_campaign=Badge_Grade_Dashboard)
[![Build Status](https://travis-ci.org/systelab/cpp-rapidjson-json-adapter.svg?branch=master)](https://travis-ci.org/systelab/cpp-rapidjson-json-adapter)
[![Build status](https://ci.appveyor.com/api/projects/status/3ynlr6vq3b89bvrn?svg=true)](https://ci.appveyor.com/project/systelab/cpp-rapidjson-json-adapter)
[![codecov](https://codecov.io/gh/systelab/cpp-rapidjson-json-adapter/branch/master/graph/badge.svg)](https://codecov.io/gh/systelab/cpp-rapidjson-json-adapter)


# C++ RapidJson JSON Adapter

# Download #

Remember to clone the repository with "--recursive" flag, otherwise the 'cpp-json-adapter' will not be downloaded.

# Build #

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
