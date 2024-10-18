libsysinfo.so: sysinfo.cc cpuinfo.cc ../sysInfo.h ../cpuInfo.h
	gcc -fPIC -I .. -I /usr/lib/jvm/java-11-openjdk-amd64/include \
        -I /usr/lib/jvm/java-11-openjdk-amd64/include/linux -shared \
        -o libsysinfo.so sysinfo.cc cpuinfo.cc

