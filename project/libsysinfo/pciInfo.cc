#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <array>
#include <unistd.h>

#include "PCIInfo.h"

using namespace std;

struct PCIBar
{
    int start;
    int end;
};

struct PCIFunction
{
    PCIBar bar[6];
};

struct PCIDevice
{
    int vendor;
    int device;
    int functionCount;
    PCIFunction[8];
}

struct PCIBus
{
    int deviceCount;
    PCIDevice device[32];
};

class PCIInfo
{
public:
    void read();
    int busCount () { return _busCount; }
    int deviceCount (int bus) { return _bus[bus].deviceCount; }
    int functionCount (int bus, int device) return _bus[bus].device[device].functionCount; }

private:
    static const int _maxBus = 64;
    // static const int _maxDevices = 64;
    int _busCount;
    PCIBus _bus[_maxBus];

};

PCIInfo pci;

void PCIInfo::_parseInfo (string& key, string &value)
{
}

void PCIInfo::_parseDevice (char buffer[])
{
    string line = buffer;
    istringstream stream(line);
    int ident;
    int vendor;
    stream >> hex >> ident >> hex >> vendor; // stat.user >> nice >> stat.system >> stat.idle;
    cout << "id=" << hex << ident << endl;
}

void PCIInfo::read(int seconds)
{
    std::array<char, 1024> buffer;
    std::unique_ptr<FILE, decltype(&fclose)> stat(fopen("/proc/bus/pci/devices", "r"), fclose);

    if (!stat) {
        throw std::runtime_error("Failed to open /proc/bus/pci/devices !");
    }

    while (fgets(buffer.data(), static_cast<int>(buffer.size()), stat.get()) != nullptr)
        _parseDevice (buffer.data());
}

JNIEXPORT void JNICALL Java_PCIInfo_read (JNIEnv *env, jobject obj) {
    cpu.read();
}

