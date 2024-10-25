MODULES=sysInfo cpuInfo pciInfo usbInfo diskInfo memInfo
SOURCES=$(MODULES:=.cc)
HEADERS=$(MODULES:%=../%.h)

#  Location of openjdk headers.  Change this according to your 
#  version and architecture
OPENJDK=/usr/lib/jvm/java-11-openjdk-amd64/include

libsysinfo.so: $(SOURCES) $(HEADERS)
	g++ -fPIC -I .. -I $(OPENJDK) \
        -I $(OPENJDK)/linux -shared \
        -Wno-ignored-attributes \
        -o libsysinfo.so $(SOURCES)

