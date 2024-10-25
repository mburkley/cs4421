/*
 *  PCI device information class implementation.  Reads PCI device details from
 *  /proc/bus/pci/devices and parses into structs by bus, device and function.
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

#include "pciInfo.h"

using namespace std;

struct PCIBar
{
    int start;
    int end;
};

struct PCIFunction
{
    bool present;
    unsigned vendor;
    unsigned product;
    PCIBar bar[6];
};

struct PCIDevice
{
    static const int maxFunction = 8;
    int functionCount;
    PCIFunction function[maxFunction];
};

struct PCIBus
{
    static const int maxDevice = 32;
    int deviceCount;
    PCIDevice device[maxDevice];
};

class PCIInfo
{
public:
    void read();
    int busCount () { return _busCount; }
    int deviceCount (int bus) { return _bus[bus].deviceCount; }
    int functionCount (int bus, int device) { return _bus[bus].device[device].functionCount; }
    int functionPresent (int bus, int device, int function) { return _bus[bus].device[device].function[function].present; }
    int vendorID (int bus, int device, int function) { return _bus[bus].device[device].function[function].vendor; }
    int productID (int bus, int device, int function) { return _bus[bus].device[device].function[function].product; }
    static const int maxBus = 64;

private:
    int _busCount;
    PCIBus _bus[maxBus];
    void _parseDevice (char buffer[]);
};

PCIInfo pci;

void PCIInfo::_parseDevice (char buffer[])
{
    string line = buffer;
    istringstream stream(line);
    int location;
    unsigned int ident;
    
    stream >> hex >> location >> ident;
    // cout << "loc=" << hex << location << ", id=" << ident << endl;
    
    int bus = location >> 8;
    assert (bus < maxBus);
    int device = (location & 0xf8) >> 3;
    int function = location & 0x7;
    // cout<<"b="<<bus<<",d="<<device<<",f="<<function<<endl;

    // Does this bus already have devices?  If not, increment the bus count
    if (_bus[bus].deviceCount == 0)
        _busCount++;

    // Does this device already have any functions?  If not increment the device count
    if (_bus[bus].device[device].functionCount == 0)
        _bus[bus].deviceCount++;

    // Increment the function count for the device
    _bus[bus].device[device].functionCount++;

    _bus[bus].device[device].function[function].present = true;
    _bus[bus].device[device].function[function].vendor = ident >> 16;
    _bus[bus].device[device].function[function].product = ident & 0xffff;
}

void PCIInfo::read()
{
    std::array<char, 4096> buffer;
    std::unique_ptr<FILE, decltype(&fclose)> stat(fopen("/proc/bus/pci/devices", "r"), fclose);

    if (!stat) {
        throw std::runtime_error("Failed to open /proc/bus/pci/devices !");
    }

    while (fgets(buffer.data(), static_cast<int>(buffer.size()), stat.get()) != nullptr)
        _parseDevice (buffer.data());
}

JNIEXPORT void JNICALL Java_pciInfo_read (JNIEnv *env, jobject obj) {
    pci.read();
}

JNIEXPORT jint JNICALL Java_pciInfo_busCount (JNIEnv *env, jobject obj) {
    return pci.busCount ();
}

JNIEXPORT jint JNICALL Java_pciInfo_deviceCount (JNIEnv *env, jobject obj, jint bus) {
    return pci.deviceCount (bus);
}

JNIEXPORT jint JNICALL Java_pciInfo_functionCount (JNIEnv *env, jobject obj, jint bus, jint device) {
    return pci.functionCount (bus, device);
}

JNIEXPORT jint JNICALL Java_pciInfo_functionPresent (JNIEnv *env, jobject obj, jint bus, jint device, jint function) {
    return pci.functionPresent (bus, device, function);
}

JNIEXPORT jint JNICALL Java_pciInfo_vendorID (JNIEnv *env, jobject obj, jint bus, jint device, jint function) {
    return pci.vendorID (bus, device, function);
}

JNIEXPORT jint JNICALL Java_pciInfo_productID (JNIEnv *env, jobject obj, jint bus, jint device, jint function) {
    return pci.productID (bus, device, function);
}

