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

usbErrMsg="ERROR: Could not find Arduboy on USB modem! \n \
Make sure it's powered on and you've hit the reset button"

arduino_dir=""
if [[ "${machine}" == "Mac" ]]; then
    arduino_dir="`pwd`/tools/arduino-ide/mac"
    if [[ `ls /dev/cu.usbmodem* | wc -l 2>/dev/null` -lt 2 ]]; then
        echo $usbErrMsg
        exit 1;
    fi
    usb_modem_port=`ls /dev/cu.usbmodem* | head -n 1`
fi

if [[ "${machine}" == "Linux" ]]; then
    arduino_dir="`pwd`/tools/arduino-ide/linux"
    if [[ `ls /dev/ttyACM* | wc -l 2>/dev/null` -lt 1 ]]; then
        echo $usbErrMsg
        exit 1;
    fi
    usb_modem_port=`ls /dev/ttyACM* | head -n 1`
fi
echo "ARDUINO_DIR=${arduino_dir}"


if [ -z $arduino_dir ]; then
    echo "ERROR! Could not find arduino dir for your platform (${unameOut})"
    exit 1
fi


cd Evade2/ 

#make clean;
make ARDUINO_DIR="${arduino_dir}"
if [[ $? -gt 0 ]]; then
    echo
    exit 1
fi 
echo
cd ..


# #usb_modem_port="/dev/cu.usbmodem1431"
# usb_modem_port=$1
hexFile=Evade2/build-leonardo/Evade2.hex

if [[ "${machine}" == "Mac" ]]; then
    stty -f "${usb_modem_port}" 1200
elif [[ "${machine}" == "Linux" ]]; then
    sudo usermod -aG dialout `whoami`
    sudo chmod a+rw ${usb_modem_port}
    stty -F "${usb_modem_port}" 1200
fi 

sleep 2

${arduino_dir}/hardware/tools/avr/bin/avrdude \
    -C${arduino_dir}/hardware/tools/avr/etc/avrdude.conf \
    -v -patmega32u4 \
    -cavr109 \
    -P${usb_modem_port} \
    -b57600 -D -Uflash:w:${hexFile}:i
if [[ $? -gt 0 ]]; then
	echo $usbErrMsg
fi



