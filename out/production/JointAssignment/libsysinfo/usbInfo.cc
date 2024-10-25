/*
 *  USB information class.  Executes lsusb and parses output into arrays of buses and
 *  devices.  Parsing is crude and just expects particular fields to be at particular
 *  locations in the output.
 *
 *  Copyright (c) 2024 Mark Burkley (mark.burkley@ul.ie)
 */

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
    
    string part = "0x"+line.substr(4,3);
    int bus = stoi (part,0,16);

    part = "0x"+line.substr(15,3);
    int device = stoi (part,0,16);

    part = "0x"+line.substr(23,4);
    _bus[bus].device[device].vendor = stoi (part,0,16);

    part = "0x"+line.substr(28,4);
    _bus[bus].device[device].product = stoi (part,0,16);

    // cout<<"bus="<<bus<<", dev="<<device<<endl;
    if (bus > _busCount)
        _busCount = bus;

    if (device > _bus[bus].deviceCount)
        _bus[bus].deviceCount = device;
    // cout<<"busus="<<_busCount<<", devs="<<_bus[bus].deviceCount<<endl;
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

