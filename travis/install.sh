#!/usr/bin/env bash

if [[ $TRAVIS_OS_NAME == "osx" ]] ; then
  brew update > /dev/null
  brew install qt5

  brew unlink cmake
  brew upgrade cmake
else

  sudo apt-get update -qq
  sudo apt-get install -y cmake

  sudo apt-get install -y qt5-default qttools5-dev
fi