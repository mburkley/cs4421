MODULES=sysInfo cpuInfo pciInfo usbInfo
SOURCES=$(MODULES:=.cc)
HEADERS=$(MODULES:%=../%.h)

#  Location of openjdk headers.  Change this according to your 
#  version and architecture
OPENJDK=/usr/lib/jvm/java-21-openjdk-amd64/include

libsysinfo.so: $(SOURCES) $(HEADERS)
	gcc -fPIC -I .. -I $(OPENJDK) \
        -I $(OPENJDK)/linux -shared \
        -o libsysinfo.so $(SOURCES)

