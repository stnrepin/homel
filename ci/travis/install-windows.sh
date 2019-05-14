#!/bin/bash

# Install CMake
#
CMAKE_OS=win64-x64
CMAKE_ARCHIVE_EXT=zip
source ${TRAVIS_BUILD_DIR}/ci/travis/install_cmake.sh

export PATH=$CMAKE_DIR/cmake-$CMAKE_VERSION-$CMAKE_OS/bin:$PATH

# Remove sh (requested by MinGW)
#
SH_PATH=$(which sh)
rm $SH_PATH

