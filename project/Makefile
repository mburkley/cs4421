.PHONY: libsysinfo/libsysinfo.so

MODULES=sysInfo cpuInfo pciInfo usbInfo diskInfo memInfo
HEADERS=$(MODULES:=.h)

MYPROJECT=template

all: $(HEADERS) template.class libsysinfo/libsysinfo.so

$(MYPROJECT).class: $(MYPROJECT).java libsysinfo/libsysinfo.so
	javac $<

$(HEADERS): %.h: %.java
	javac -h . $<

libsysinfo/libsysinfo.so:
	$(MAKE) -C libsysinfo

