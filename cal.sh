#!/usr/bin/env bash

#clear
echo " __________________________________________"
echo " |               Evade 2                  |"
echo " |      Compilation and Deployment        |"
echo " |             ---------                  |"
echo " | This process will require a restart of |"
echo " | your Arduboy device. Make sure you     |"
echo " | have a thin object (e.g. a toothipick) |"
echo " | close to the reset button.             |"
echo " |                                        |"
echo " |   * Your Arduboy should be <ON>. *     |"
echo " |                                        |"
echo " | Warning:                               |"
echo " | Previously used toothpicks may cause   |"
echo " | unexpected issues.                     |"
echo " __________________________________________"
read -p "Press any key (while holding on to the toothpick)... "
echo

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

#make clean ARDUINO_DIR="${arduino_dir}"
make ARDUINO_DIR="${arduino_dir}"
if [[ $? -gt 0 ]]; then
    echo
    exit 1
fi 
echo
cd ..

program_size=`${arduino_dir}/hardware/tools/avr/bin/avr-size --mcu=atmega32u4 -C \
    --format=avr Evade2/build-leonardo/Evade2.elf | grep Program | awk '{print $2}'`

if [[ ${program_size} -gt 28672 ]]; then
    echo "***** ERROR!!"
    echo "Program size (${program_size} bytes) is larger than maximum 28,672 bytes!"
    exit 1;

else 
    percent=$(awk "BEGIN { pc=100*${program_size}/28672; i=int(pc); print i }")
    echo "Program size is ${program_size} bytes (${percent}%) of a maximum 28,672 bytes!"
fi

# This is where upload begins.
#clear
echo " ******************************************"
echo " *        RESET YOUR ARDUBOY NOW!         *"
echo " ******************************************"
echo "5 seconds left..."
echo
sleep 4

echo "1 second left. Is the toothpick in already?"
echo
sleep 1

usbErrMsg="ERROR: Could not find Arduboy on USB modem! \n \
Make sure it's powered on and you've hit the reset button then restart this script"

if [[ "${machine}" == "Mac" ]]; then
    if [[ `ls -ra /dev/cu.usbmodem* | wc -l 2>/dev/null` -lt 1 ]]; then
        echo -e $usbErrMsg
        exit 1;
    fi
    usb_modem_port=`ls -rat /dev/cu.usbmodem* | tail -n 1`
    stty -f "${usb_modem_port}" 1200
elif [[ "${machine}" == "Linux" ]]; then
    sudo usermod -aG dialout `whoami`
    sudo chmod a+rw ${usb_modem_port}
    if [[ `ls /dev/ttyACM* | wc -l 2>/dev/null` -lt 1 ]]; then
        echo -e $usbErrMsg
        exit 1;
    fi
    usb_modem_port=`ls -rat /dev/ttyACM* | head -n 1`
    stty -F "${usb_modem_port}" 1200
fi

# #usb_modem_port="/dev/cu.usbmodem1431"
# usb_modem_port=$1
hexFile=Evade2/build-leonardo/Evade2.hex

${arduino_dir}/hardware/tools/avr/bin/avrdude \
    -C${arduino_dir}/hardware/tools/avr/etc/avrdude.conf \
    -v -patmega32u4 \
    -cavr109 \
    -P${usb_modem_port} \
    -b57600 -D -Uflash:w:${hexFile}:i
if [[ $? -gt 0 ]]; then
	echo -e $usbErrMsg
    exit 1
fi

echo "Program size is ${program_size} bytes (${percent}%) of a maximum 28,672 bytes!"

echo "*IMPORTANT!*"
echo "You must power cycle your Arduino!"
echo
if [[ "${machine}" == "Mac" ]]; then
    if [[ ${1} != "" ]]; then
	say "firmware flashed"
    fi	
fi


