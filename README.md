# Boost Library Template

Branch          | Travis | Appveyor | Azure Pipelines | codecov.io | Docs | Matrix |
:-------------: | ------ | -------- | --------------- | ---------- | ---- | ------ |
[`master`](https://github.com/madmongo1/webclient/tree/master) | [![Build Status](https://travis-ci.org/madmongo1/webclient.svg?branch=master)](https://travis-ci.org/madmongo1/webclient) | [![Build status](https://ci.appveyor.com/api/projects/status/github/madmongo1/webclient?branch=master&svg=true)](https://ci.appveyor.com/project/madmongo1/webclient/branch/master) | [![Build Status](https://img.shields.io/azure-devops/build/madmongo1/6c855cbf-4aa5-4b51-bcad-245dc439ae7d/3/master)](https://madmongo1.visualstudio.com/webclient/_build/latest?definitionId=3&branchName=master) | [![codecov](https://codecov.io/gh/madmongo1/webclient/branch/master/graph/badge.svg)](https://codecov.io/gh/madmongo1/webclient/branch/master) | [![Documentation](https://img.shields.io/badge/docs-master-brightgreen.svg)](http://vinniefalco.github.com/doc/webclient/index.html) | [![Matrix](https://img.shields.io/badge/matrix-master-brightgreen.svg)](http://www.boost.org/development/tests/master/developer/webclient.html)
[`develop`](https://github.com/madmongo1/webclient/tree/develop) | [![Build Status](https://travis-ci.org/madmongo1/webclient.svg?branch=develop)](https://travis-ci.org/madmongo1/webclient) | [![Build status](https://ci.appveyor.com/api/projects/status/github/madmongo1/webclient?branch=develop&svg=true)](https://ci.appveyor.com/project/madmongo1/webclient/branch/develop) | [![Build Status](https://img.shields.io/azure-devops/build/madmongo1/6c855cbf-4aa5-4b51-bcad-245dc439ae7d/3/develop)](https://madmongo1.visualstudio.com/webclient/_build/latest?definitionId=3&branchName=develop) | [![codecov](https://codecov.io/gh/madmongo1/webclient/branch/develop/graph/badge.svg)](https://codecov.io/gh/madmongo1/webclient/branch/develop) | [![Documentation](https://img.shields.io/badge/docs-develop-brightgreen.svg)](http://vinniefalco.github.com/doc/webclient/index.html) | [![Matrix](https://img.shields.io/badge/matrix-develop-brightgreen.svg)](http://www.boost.org/development/tests/develop/developer/webclient.html)

## This is **NOT** an official Boost library.

## CMake

    cmake -G "Visual Studio 16 2019" -A Win32 -B bin -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/msvc.cmake
    cmake -G "Visual Studio 16 2019" -A x64 -B bin64 -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/msvc.cmake

## License

Distributed under the Boost Software License, Version 1.0.
(See accompanying file [LICENSE_1_0.txt](LICENSE_1_0.txt) or copy at
https://www.boost.org/LICENSE_1_0.txt)
