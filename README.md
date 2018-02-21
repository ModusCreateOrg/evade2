![EVADE 2 by Modus Create](/img/repo_banner.png?raw=true "EVADE 2 by Modus Create")

# Evade 2

Evade 2 is an Arduboy game developed by Modus Create as a holiday gift to friends and family in December 2018.

The game took about 3 weeks to create, from start to finish.

Please see the Arduboy game we made last year, Evade.

This repository contains the source code to the game, which we're making freely available and open source, under the [MIT license](LICENSE.md).

We believe we pushed the Arduboy hardware in ways that will benefit future programming efforts.  Feel free to use the
source code here to enhance your own projects.  Or feel free to make your own improvements to Evade 2 for your own 
pleasure.

# IDE Setup

In order to compile the game and upload it to the Arduboy, we've used the Arduino IDE.  We don't use the IDE features except
to compile and upload our sketch (the game) to the device.

A nice quick start guide can be found here:
https://community.arduboy.com/t/quick-start-guide/2790

The following instructions are a brief summary of the steps found at the link above.

## Download and install the Arduino software

The IDE can be found here:
https://www.arduino.cc/en/Main/Software

The IDE download will be a .zip file.  Unzip it and run the install.sh file from within.  For Mac, unzip the file and drag the App to your
Applications folder.

## Install the Arduboy2 library

Launch the IDE and under the Sketch menu there is an Include Library menu item; select Manage Libraries... from there.

Search for "Arduboy" in the search field and press install on the Arduboy2 entry.

## Install support for Arduboy board

In the IDE, select File -> Preferences.  In the Settings tab, enter the following URL into the "Additional BOards ManagerURLs" field:

https://arduboy.github.io/board-support/package_arduboy_index.json

Click "OK" to save.

Then Select Tools > Board: "some name" > Boards Manager... 

In the search box at the top, enter "arduboy" (without the quotes) and click on the Install button for the "Arduboy by Arduboy Team" entry.

## External Editor

Select File -> Preferences and click the "Use external editor" checkbox.  You will then be able to use the editor of your choice
to edit the project sources.  You will only use the IDE to compile (the check button), or compile and upload (the right arrow button).
## Restarting the IDE

It is mandatory to restart the IDE any time you pull into your git working set.  The IDE keeps caches of various things like precompiled
header files, and it gets confused by changes to the directory structure.

In general, if you have any doubt, it doesn't hurt to restart the IDE.

## Connect your Arduboy via USB

On linux, you can see the device via ```ls /dev/tty*``` - it will be something like /dev/ttyACM0.

On Mac, the device will be something like /dev/cu.modemxxx.

## Open the project in the IDE

Launch the IDE and select File > Open... and naviate to the directory containing the .ino file and select that file.

## Select board type and port

From the IDE, select Tools > Board and choose "Arduboy"

Then select Tools > Port and select the /dev/ device you found via the ls command above.

## Upload the sketch

Click on the right arrow button in the IDE toolbar.  The sketch should compile and then upload to the device.

If you just want to compile, to check for warnings and errors, click the check button.

# (TBD code overview, links, screenshots)

# Credits

*Designed by* Jay Garcia

*Music by* Jay Garcia and Delio Brignoli

*Art by* Michael Tintiuc and Jay Garcia

*Programming by* Jay Garcia, Delio Birgnoli, Michael Tintiuc, and Mike Schwartz
