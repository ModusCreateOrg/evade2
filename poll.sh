#!/usr/bin/env bash
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
    while TRUE; do
    if [[ `ls /dev/cu.usbmodem* | wc -l 2>/dev/null` -lt 2 ]]; then
        printf .
    else
	echo
	say "compile" 
	./cal.sh -v
	if [[ $? -gt 0 ]]; then
		sleep 1
		say "Error compiling!"
		sleep 10
	fi
    fi
    sleep 1
    done
fi

exit 0
if [[ "${machine}" == "Linux" ]]; then
    arduino_dir="`pwd`/tools/arduino-ide/linux"
    if [[ `ls /dev/ttyACM* | wc -l 2>/dev/null` -lt 1 ]]; then
        echo $usbErrMsg
        exit 1;
    fi
    usb_modem_port=`ls /dev/ttyACM* | head -n 1`
fi


