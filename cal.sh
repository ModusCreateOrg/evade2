#!/usr/bin/env bash

which git 
if [ $? -gt 0 ]; then 
    echo "ERROR:\nCould not find git in your \$PATH"
    exit 1
fi

echo "Grabbing git submodules"
git submodule init; git submodule update;

unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
    CYGWIN*)    machine=Cygwin;;
    MINGW*)     machine=MinGw;;
    *)          machine="UNKNOWN:${unameOut}"
esac

arduino_dir=""
if [[ "${machine}" == "Mac" ]]; then
    arduino_dir="`pwd`/tools/arduino-ide/mac"
fi

if [[ "${machine}" == "Linux" ]]; then
    arduino_dir="`pwd`/tools/arduino-ide/linux"
fi
echo "ARDUINO_DIR=${arduino_dir}"


if [ -z $arduino_dir ]; then
    echo "ERROR! Could not find arduino dir for your platform (${unameOut})"
    exit 1
fi


cd Evade2/ 
make ARDUINO_DIR="${arduino_dir}" clean
make ARDUINO_DIR="${arduino_dir}"
