#!/usr/bin/env bash

if [[ $TRAVIS_OS_NAME == "osx" ]] ; then
  brew update
  brew install qt5
else

  sudo apt-get update -qq
  sudo apt-get install -y libprotobuf-dev protobuf-compiler cmake bc

  sudo apt-get install -y qt5-default qttools5-dev
fi