#!/usr/bin/env bash

if [[ $TRAVIS_OS_NAME == "osx" ]] ; then
  brew update > /dev/null
  brew install qt5

  brew unlink cmake
  brew upgrade cmake
else
  # We need Qt5.5.x: https://launchpad.net/~beineri/+archive/ubuntu/opt-qt551-trusty
  sudo apt-add-repository -y ppa:beineri/opt-qt551-trusty

  sudo apt-get update -qq
  sudo apt-get install -y cmake rpm

  # install from ppa
  sudo apt-get install -y qt55webengine qt55webchannel qt55tools qt55base qt55multimedia
fi