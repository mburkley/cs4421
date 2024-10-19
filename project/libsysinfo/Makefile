MODULES=sysInfo cpuInfo pciInfo usbInfo
SOURCES=$(MODULES:=.cc)
HEADERS=$(MODULES:%=../%.h)

libsysinfo.so: $(SOURCES) $(HEADERS)
	gcc -fPIC -I .. -I /usr/lib/jvm/java-11-openjdk-amd64/include \
        -I /usr/lib/jvm/java-11-openjdk-amd64/include/linux -shared \
        -o libsysinfo.so $(SOURCES)

