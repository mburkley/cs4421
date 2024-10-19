# cs4421
This code supports the module CS4421 computer organisation end of block project.

To build from the command line, cd into the project directory and type "make".  To run, type "./run.sh".

In the project directory, there are a number of Java classes defined (cpuInfo, usbInfo, pciInfo) that provide methods to get information about
system devices.  The file template.java demonstrates how to use the info classes.

Students should create their own Java classes to retrieve system information using the classes provied and implement
code that analyses and presents the data.

The library libsysinfo creates a shared-object library that provides Java Native Interface (JNI) methods that can be
called from Java.  This library is written in C++ and can be used as is without modification.  Students are not expected
to understand or modify this library, but can if they wish.  If there any features missing that you would like to see,
please ask and I will add them.

