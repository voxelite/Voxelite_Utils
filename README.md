# Voxelite Utils

General utilities used by different parts of Voxelite project

## Libraries

| Name | License | Version |
|------|---------|---------|
| [OpenSSL](https://www.openssl.org/) + [cmake](https://github.com/viaduck/openssl-cmake) | [Apache License 2.0](https://github.com/openssl/openssl/blob/master/LICENSE) + [MIT](https://github.com/viaduck/openssl-cmake/blob/master/LICENSE) | branch: [`OpenSSL_0_9_6-stable`](https://github.com/openssl/openssl/tree/OpenSSL_0_9_6-stable) |

All libraries are used as `static library` to maximize optimization and limit problems with deployment and versions.

## Testing

Run `ctest` in build directory.

Executable of tests have prefix `t_` (test `abc` would be executable `t_abc`).
After creating new test, add it to [`tests/CMakeLists.txt`](tests/CMakeLists.txt) as `add_subdirectory(abc)` (where `abc` is name of your test).

To setup tests in CLion IDE, create new Run Configuration with Name=`CTest`, Working Directory=`$CMakeCurrentBuildDir$` and Executable pointing to your `ctest` executable.
On Linux it will be `/bin/ctest`, on Windows probably `C:\CMake\bin\ctest.exe` 
