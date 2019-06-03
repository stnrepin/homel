#!/bin/bash

CMAKE_VERSION=3.14.3
CMAKE_VERSION_DIR=v3.14

CMAKE_ARCHIVE=cmake-$CMAKE_VERSION-$CMAKE_OS.$CMAKE_ARCHIVE_EXT
CMAKE_URL=http://www.cmake.org/files/$CMAKE_VERSION_DIR/$CMAKE_ARCHIVE
CMAKE_DIR=$(pwd)/cmake-$CMAKE_VERSION

travis_retry wget -q --no-check-certificate $CMAKE_URL

mkdir -p $CMAKE_DIR

if [ "$CMAKE_ARCHIVE_EXT" == "zip" ]; then
    unzip -q $CMAKE_ARCHIVE -d $CMAKE_DIR
else
    tar --strip-components=1 -xzf $CMAKE_ARCHIVE -C $CMAKE_DIR
fi

