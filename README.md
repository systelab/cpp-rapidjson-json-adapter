[![Build Status](https://travis-ci.org/systelab/cpp-rapidjson-json-adapter.svg?branch=master)](https://travis-ci.org/systelab/cpp-rapidjson-json-adapter)
[![Build status](https://ci.appveyor.com/api/projects/status/qdrjivrs26gf46lo?svg=true)](https://ci.appveyor.com/project/systelab/cpp-rapidjson-json-adapter)
[![codecov](https://codecov.io/gh/systelab/cpp-rapidjson-json-adapter/branch/master/graph/badge.svg)](https://codecov.io/gh/systelab/cpp-rapidjson-json-adapter)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/492f2b284cd149018ec9dd54a45d53df)](https://www.codacy.com/app/systelab/cpp-rapidjson-json-adapter?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=systelab/cpp-rapidjson-json-adapter&amp;utm_campaign=Badge_Grade)
[![Download](https://api.bintray.com/packages/systelab/conan/RapidJSONAdapter:systelab/images/download.svg)](https://bintray.com/systelab/conan/RapidJSONAdapter:systelab/_latestVersion)


# C++ JSON Adapter implementation for rapidjson

This repository implements the interface for the [C++ JSON Server Adapter](https://github.com/systelab/cpp-json-adapter) using [Rapidjson](http://rapidjson.org).

## Setup

### Download using Conan

This library is designed to be installed by making use of [Conan](https://conan.io/) package manager. So, you just need to add the following requirement into your Conan recipe:

```python
def requirements(self):
   self.requires("RapidJSONAdapter/1.1.0@systelab/stable")
```

> Version number of this code snipped is set just as an example. Replace it for the desired package to retrieve.

As this package is not available on the conan-center, you will also need to configure a remote repository before installing dependencies:

```bash
conan remote add systelab-bintray https://api.bintray.com/conan/systelab/conan 
```

See Conan [documentation](https://docs.conan.io/en/latest/) for further details on how to integrate this package with your build system.

### Build from sources

See [BUILD.md](BUILD.md) document for details.


## Usage

Initialize the JSON adapter by creating an instance of the `systelab::json::rapidjson::JSONAdapter` class:

```cpp
#include "RapidJSONAdapter/JSONAdapter.h"

std::unique_ptr<systelab::json::IJSONAdapter> jsonAdapter =
    std::make<systelab::json::rapidjson::JSONAdapter>();
```

Use the `systelab::json::IJSONAdapter` interface of the created object to access to the JSON features as described on [C++ JSON Adapter](https://github.com/systelab/cpp-json-adapter) documentation.
