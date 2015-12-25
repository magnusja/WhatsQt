#!/usr/bin/env bash

prefix=""
if [[ $TRAVIS_OS_NAME == "osx" ]]; then
  prefix="-DCMAKE_PREFIX_PATH=$(echo /usr/local/Cellar/qt5/5.*/)"
fi

mkdir build
cd build

cmake ../ $prefix
make package -j2