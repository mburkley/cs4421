all: sysInfo.class

sysInfo.class: sysInfo.java libsysinfo/libsysinfo.so
	javac sysInfo.java 

sysInfo.h: sysInfo.java
	javac -h . sysInfo.java 

libsysinfo/libsysinfo.so: libsysinfo/sysinfo.cc sysInfo.h
	$(MAKE) -C libsysinfo

