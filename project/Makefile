all: template.class

template.class: template.java libsysinfo/libsysinfo.so
	javac template.java 

sysInfo.h: sysInfo.java
	javac -h . sysInfo.java 

cpuInfo.h: cpuInfo.java
	javac -h . cpuInfo.java 

libsysinfo/libsysinfo.so: libsysinfo/sysinfo.cc sysInfo.h cpuInfo.h
	$(MAKE) -C libsysinfo

