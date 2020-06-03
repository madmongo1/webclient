# Boost Library Template

Branch          | Travis | Appveyor | Azure Pipelines | codecov.io | Docs | Matrix |
:-------------: | ------ | -------- | --------------- | ---------- | ---- | ------ |
[`master`](https://github.com/madmongo1/webclient/tree/master) | [![Build Status](https://travis-ci.org/madmongo1/webclient.svg?branch=master)](https://travis-ci.org/madmongo1/webclient) | [![Build status](https://ci.appveyor.com/api/projects/status/github/madmongo1/webclient?branch=master&svg=true)](https://ci.appveyor.com/project/madmongo1/webclient/branch/master) | [![Build Status](https://img.shields.io/azure-devops/build/madmongo1/6c855cbf-4aa5-4b51-bcad-245dc439ae7d/3/master)](https://madmongo1.visualstudio.com/webclient/_build/latest?definitionId=3&branchName=master) | [![codecov](https://codecov.io/gh/madmongo1/webclient/branch/master/graph/badge.svg)](https://codecov.io/gh/madmongo1/webclient/branch/master) | [![Documentation](https://img.shields.io/badge/docs-master-brightgreen.svg)](http://vinniefalco.github.com/doc/webclient/index.html) | [![Matrix](https://img.shields.io/badge/matrix-master-brightgreen.svg)](http://www.boost.org/development/tests/master/developer/webclient.html)
[`develop`](https://github.com/madmongo1/webclient/tree/develop) | [![Build Status](https://travis-ci.org/madmongo1/webclient.svg?branch=develop)](https://travis-ci.org/madmongo1/webclient) | [![Build status](https://ci.appveyor.com/api/projects/status/github/madmongo1/webclient?branch=develop&svg=true)](https://ci.appveyor.com/project/madmongo1/webclient/branch/develop) | [![Build Status](https://img.shields.io/azure-devops/build/madmongo1/6c855cbf-4aa5-4b51-bcad-245dc439ae7d/3/develop)](https://madmongo1.visualstudio.com/webclient/_build/latest?definitionId=3&branchName=develop) | [![codecov](https://codecov.io/gh/madmongo1/webclient/branch/develop/graph/badge.svg)](https://codecov.io/gh/madmongo1/webclient/branch/develop) | [![Documentation](https://img.shields.io/badge/docs-develop-brightgreen.svg)](http://vinniefalco.github.com/doc/webclient/index.html) | [![Matrix](https://img.shields.io/badge/matrix-develop-brightgreen.svg)](http://www.boost.org/development/tests/develop/developer/webclient.html)

## This is **NOT** an official Boost library.

## Aims of the Library

* Provide a one-stop high level c++ interface to all common web protocols from the point of view of the client
* Think libCurl in native c++
* Provide both synchronous and asynchronous interfaces to all operations
* Based on, and fully compatible with, the ASIO executor model
* Modelled on the very popular python requests library
* .netrc support


## Design Considerations

* When building for controlled platforms, use the native, vendor-approved APIs internally in order not to hinder publishing
* When building on uncontrolled platforms (or by specific build switches), use ASIO and Boost Beast as underlying technologies
* Whichever underlying API is selected, provide a seamless homogeneous interface to users.

# Structural thoughts

| component     | purpose       |
| ------------- | ------------- |
| internet_session | Provides execution environment, default settings and connection caches |
| http_connection_pool | Http clients *should* limit the number of concurrent connections per host |
| cookie_jar       | internet_session will maintain a cookie jar which http_requst tasks may or may not use |
| http_task        | Encapsulates the high level task to be carried out. e.g. a GET which may or may not tolerate redirects |
| http_request     | An indiviual request / response cycle against a host, possibly on a reusable connection |

Users should be free to create or specify an `internet_session` with each request, and should be allowed not
to specify one. If an internet_session is not specified, a default session, shared across the process
is made available automatically.

## CMake

    cmake -G "Visual Studio 16 2019" -A Win32 -B bin -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/msvc.cmake
    cmake -G "Visual Studio 16 2019" -A x64 -B bin64 -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/msvc.cmake

## License

Distributed under the Boost Software License, Version 1.0.
(See accompanying file [LICENSE_1_0.txt](LICENSE_1_0.txt) or copy at
https://www.boost.org/LICENSE_1_0.txt)
