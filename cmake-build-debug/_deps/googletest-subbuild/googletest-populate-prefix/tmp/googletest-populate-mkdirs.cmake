# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/pavelzolin/Desktop/ADS6/ADS-5/cmake-build-debug/_deps/googletest-src"
  "/Users/pavelzolin/Desktop/ADS6/ADS-5/cmake-build-debug/_deps/googletest-build"
  "/Users/pavelzolin/Desktop/ADS6/ADS-5/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix"
  "/Users/pavelzolin/Desktop/ADS6/ADS-5/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "/Users/pavelzolin/Desktop/ADS6/ADS-5/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "/Users/pavelzolin/Desktop/ADS6/ADS-5/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "/Users/pavelzolin/Desktop/ADS6/ADS-5/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/pavelzolin/Desktop/ADS6/ADS-5/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/pavelzolin/Desktop/ADS6/ADS-5/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
