#!/bin/bash

# Install CMake
#
CMAKE_OS=Linux-x86_64
CMAKE_ARCHIVE_EXT=tar.gz
source ${TRAVIS_BUILD_DIR}/scripts/ci/travis/install_cmake.sh

export PATH=$CMAKE_DIR/bin:$PATH

