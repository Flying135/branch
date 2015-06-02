#ArduPilot Project#

[![Gitter](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/diydrones/ardupilot?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

### The ArduPilot project is made up of: ###
>>ArduCopter (or APM:Copter) : [code](https://github.com/diydrones/ardupilot/tree/master/ArduCopter), [wiki](http://copter.ardupilot.com)

>>ArduPlane (or APM:Plane) : [code](https://github.com/diydrones/ardupilot/tree/master/ArduPlane), [wiki](http://plane.ardupilot.com)

>>ArduRover (or APMrover2) : [code](https://github.com/diydrones/ardupilot/tree/master/APMrover2), [wiki](http://rover.ardupilot.com)

>>Antenna Tracker : [code](https://github.com/diydrones/ardupilot/tree/master/AntennaTracker), [wiki](http://copter.ardupilot.com/wiki/common-antennatracker-introduction)

### User Support & Discussion Forums ###
>>APM Forum: [http://ardupilot.com/forum/index.php](http://ardupilot.com/forum/index.php)

>>Community Site: [http://diydrones.com](http://diydrones.com)

### Developer Information ###
>>Github repository: [https://github.com/diydrones/ardupilot](https://github.com/diydrones/ardupilot)

>>Main developer wiki: [http://dev.ardupilot.com](http://dev.ardupilot.com)

>>Developer email group: drones-discuss@googlegroups.com

### Contributors ###
>>[Github statistics](https://github.com/diydrones/ardupilot/graphs/contributors)

### How To Get Involved ###
>>The ArduPilot project is open source and we encourage participation and code contributions: [guidelines for contributors to the ardupilot codebase](http://dev.ardupilot.com/wiki/guidelines-for-contributors-to-the-apm-codebase)

>>We have an active group of Beta Testers especially for ArduCopter to help us find bugs: [release procedures](http://dev.ardupilot.com/wiki/release-procedures)

>>Desired Enhancements and Bugs can be posted to the [issues list](https://github.com/diydrones/ardupilot/issues).

>>Helping other users with log analysis on [diydrones.com](http://www.diydrones.com) and the [APM forums ](http://ardupilot.com/forum/index.php) is always appreciated:

>>There is a group of wiki editors as well in case documentation is your thing: ardu-wiki-editors@googlegroups.com

>>Developer discussions occur on drones-discuss@google-groups.com

### License ###
>>[Overview of license](http://dev.ardupilot.com/wiki/license-gplv3)

>>[Full Text](https://github.com/diydrones/ardupilot/blob/master/COPYING.txt)

###STM32F37x makefile libraries###
>>https://github.com/Maelok/stm32_libraries

###relative webs###
>>http://pixhawk.org/choice

>>http://ardupilot.com/

###how to change the board to another one###
>>first: add your board to AP_HAL_Boards

>>second: add your vars to the namespace, AP_HAL_Flying_Namespace.h 

>>third: finish including HAL_Flying_Class.h and HAL_Flying_Class.cpp

>>forth: then you can add the Devices to the fold under AP_HAL_Flying, such as GPIO.h GPIO.cpp and so on.

>>fifth: include you Devices drivers including *.h and *.cpp files to AP_HAL_Flying_Private.h

>>sixth: the other file can be finished  AP_HAL_Flying_Main.h

