#!/bin/bash

# Install CMake
#
CMAKE_OS=Darwin-x86_64
CMAKE_ARCHIVE_EXT=tar.gz
source ${TRAVIS_BUILD_DIR}/ci/travis/install_cmake.sh

export PATH=$CMAKE_DIR/CMake.app/Contents/bin:$PATH

