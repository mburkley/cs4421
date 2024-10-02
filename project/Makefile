all: sysInfo.class sysInfo.h libsysinfo/libsysinfo.so

sysInfo.class:
	javac sysInfo.java 

sysInfo.h:
	javac -h . sysInfo.java 

libsysinfo/libsysinfo.so:
	$(MAKE) -C libsysinfo

