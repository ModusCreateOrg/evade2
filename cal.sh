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
#    usb_modem_port=`ls /dev/cu.usbmodem* | head -n 1`
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

make clean;
make ARDUINO_DIR="${arduino_dir}"
if [[ $? -gt 0 ]]; then
    echo
    exit 1
fi 
echo
cd ..


#usb_modem_port="/dev/cu.usbmodem1431"
usb_modem_port=$1
hexFile=Evade2/build-leonardo/Evade2.hex

stty -f "${usb_modem_port}" 1200
sleep 2
${arduino_dir}/hardware/tools/avr/bin/avrdude \
    -C${arduino_dir}/hardware/tools/avr/etc/avrdude.conf \
    -v -patmega32u4 \
    -cavr109 \
    -P${usb_modem_port} \
    -b57600 -D -Uflash:w:${hexFile}:i




