.PHONY: libsysinfo/libsysinfo.so

MODULES=sysInfo cpuInfo
HEADERS=$(MODULES:=.h)

MYPROJECT=template

all: $(HEADERS) template.class libsysinfo/libsysinfo.so

$(MYPROJECT).class: $(MYPROJECT).java libsysinfo/libsysinfo.so
	javac $<

$(HEADERS): %.h: %.java
	javac -h . $<

# sysInfo.h: sysInfo.java
#	javac -h . sysInfo.java 

# cpuInfo.h: cpuInfo.java
# 	javac -h . cpuInfo.java 

libsysinfo/libsysinfo.so:
	$(MAKE) -C libsysinfo

