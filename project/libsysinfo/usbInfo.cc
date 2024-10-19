#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <array>
#include <cassert>
#include <unistd.h>

#include "usbInfo.h"

using namespace std;

struct USBDevice
{
    unsigned vendor;
    unsigned product;
};

struct USBBus
{
    static const int maxDevice = 32;
    int deviceCount;
    USBDevice device[maxDevice];
};

class USBInfo
{
public:
    void read();
    int busCount () { return _busCount; }
    int deviceCount (int bus) { return _bus[bus].deviceCount; }
    int vendorID (int bus, int device) { return _bus[bus].device[device].vendor; }
    int productID (int bus, int device) { return _bus[bus].device[device].product; }
    static const int maxBus = 64;

private:
    int _busCount;
    USBBus _bus[maxBus];
    void _parseDevice (char buffer[]);
};

USBInfo usb;

void USBInfo::_parseDevice (char buffer[])
{
    string line = buffer;
    // istringstream stream(line);
    
    string part = "0x"+line.substr(4,3);
    // cout<<"subs 4="+line.substr(4,3)<<endl;
    int bus = stoi (part,0,16);

    part = "0x"+line.substr(15,3);
    // cout<<"subs 15="+line.substr(15,3)<<endl;
    int device = stoi (part,0,16);

    part = "0x"+line.substr(23,4);
    // cout<<"subs 23="+line.substr(23,4)<<endl;
    _bus[bus].device[device].vendor = stoi (part,0,16);

    part = "0x"+line.substr(28,4);
    // cout<<"subs 28="+line.substr(28,4)<<endl;
    _bus[bus].device[device].product = stoi (part,0,16);

    cout<<"bus="<<bus<<", dev="<<device<<endl;
    if (bus > _busCount)
        _busCount = bus;

    if (device > _bus[bus].deviceCount)
        _bus[bus].deviceCount = device;
    cout<<"busus="<<_busCount<<", devs="<<_bus[bus].deviceCount<<endl;


    // stream >> "Bus " << bus << " Device "<<device<<": ID :"<<hex<<product<<":"<<vendor;
    
    #if 0
    int bus = location >> 8;
    assert (bus < maxBus);
    int device = (location & 0xf8) >> 3;
    int function = location & 0x7;
    cout<<"b="<<bus<<",d="<<device<<",f="<<function<<endl;

    // Does this bus already have devices?  If not, increment the bus count
    if (_bus[bus].deviceCount == 0)
        _busCount++;

    // Does this device already have any functions?  If not increment the device count
    if (_bus[bus].device[device].functionCount == 0)
        _bus[bus].deviceCount++;

    // Increment the function count for the device
    _bus[bus].device[device].functionCount++;

    // if (device >= _bus[bus].deviceCount)
    //     _bus[bus].deviceCount = device + 1;
    _bus[bus].device[device].function[function].present = true;
    // _bus[bus].deviceCount++;
    // _bus[bus].device[device].functionCount++;
    _bus[bus].device[device].function[function].vendor = ident >> 16;
    _bus[bus].device[device].function[function].product = ident & 0xffff;
    #endif
}

void USBInfo::read()
{
    std::array<char, 1024> buffer;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("lsusb", "r"), pclose);

    if (!pipe) {
        throw std::runtime_error("Failed to execute lsusb!");
    }

    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr)
        _parseDevice (buffer.data());
}

JNIEXPORT void JNICALL Java_usbInfo_read (JNIEnv *env, jobject obj) {
    usb.read();
}

JNIEXPORT jint JNICALL Java_usbInfo_busCount (JNIEnv *env, jobject obj) {
    return usb.busCount ();
}

JNIEXPORT jint JNICALL Java_usbInfo_deviceCount (JNIEnv *env, jobject obj, jint bus) {
    return usb.deviceCount (bus);
}

JNIEXPORT jint JNICALL Java_usbInfo_vendorID (JNIEnv *env, jobject obj, jint bus, jint device) {
    return usb.vendorID (bus, device);
}

JNIEXPORT jint JNICALL Java_usbInfo_productID (JNIEnv *env, jobject obj, jint bus, jint device) {
    return usb.productID (bus, device);
}

