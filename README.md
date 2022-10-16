# Calgopp
## C++ library for signal processing
Copyright (c) 2022 Pawel Gmurczyk

Documentation:
* [Reference](https://pawelekg95.github.io/calgopp/)

# CI status

| ![linux_badge] | ![quality_badge] |
| :------------: | :--------------: |

[linux_badge]: https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black
[quality_badge]: https://github.com/pawelekg95/calgopp/actions/workflows/calgopp_CI.yml/badge.svg

# Introduction
Calgopp is scientific and technical computing library written in C++ for embedded devices (but not only).
It was inspired by Python [SciPy](https://scipy.org/).

Signal handling:
* creating signal objects from C-style arrays
* possibility to create it from STL containers
* adding, deleting, modifying objects

Signal processing:
* transforms (Fourier, Jacymirski)
* filtering
* wavelets

GPU utilization
* computation parallelization

# Installation

### CMake
To include calgopp simple put:

```
include(FetchContent)
FetchContent_Declare(
    calgopp
    GIT_REPOSITORY  https://github.com/pawelekg95/calgopp.git
    GIT_TAG         main
)

FetchContent_GetProperties(calgopp)
FetchContent_Populate(calgopp)

add_subdirectory(${calgopp_SOURCE_DIR}/lib ${calgopp_BINARY_DIR})
```

in your top level CMakeLists.txt and in CMakeLists.txt of every module that is supposed to link with
calgopp:

````
target_link_libraries(<your_module>
    PUBLIC calgopp::<submodule>
)
````

To enable GPU parallelization set CMake variable GPU_PARALLEL to 1:
````
set(GPU_PARALLEL 1)
````

# Usage
See `test` directory for examples.
