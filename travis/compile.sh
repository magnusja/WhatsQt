#!/usr/bin/env bash

prefix=""
if [[ $TRAVIS_OS_NAME == "osx" ]]; then
  export PATH=$PATH:$(echo /usr/local/Cellar/qt5/5.*/)/bin
  prefix="-DCMAKE_PREFIX_PATH=$(echo /usr/local/Cellar/qt5/5.*/)"
fi

if [[ $TRAVIS_OS_NAME == "linux" ]]; then
  source /opt/qt55/bin/qt55-env.sh
  prefix="-DCMAKE_PREFIX_PATH=$(echo /opt/qt5*/lib/cmake/)"
  export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$(echo /opt/qt5*/lib/)"
fi

mkdir build
cd build

cmake ../ $prefix

if [[ $TRAVIS_OS_NAME == "osx" ]]; then
    make package -j2
else
    make package -j2
fi