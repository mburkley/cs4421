.PHONY: libsysinfo/libsysinfo.so

MODULES=sysInfo cpuInfo pciInfo usbInfo diskInfo memInfo
HEADERS=$(MODULES:=.h)

MYPROJECT=template

all: $(HEADERS) $(MYPROJECT).class libsysinfo/libsysinfo.so

# junk
#
$(MYPROJECT).class: $(MYPROJECT).java libsysinfo/libsysinfo.so
	javac $<

$(HEADERS): %.h: %.java
	javac -h . $<

libsysinfo/libsysinfo.so:
	$(MAKE) -C libsysinfo

