/*
 *  Disk information class.  Executes df and parses output into an of mounted disk
 *  partitions with capacity, used and free byte counts.
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

#include "diskInfo.h"

using namespace std;

struct DiskPartition
{
    string name;
    long total;
    long used;
    long available;
};

class DiskInfo
{
public:
    void read();
    int diskCount () { return _diskCount; }
    string& name (int disk) { return _disk[disk].name; }
    long total (int disk) { return _disk[disk].total; }
    long used (int disk) { return _disk[disk].used; }
    long available (int disk) { return _disk[disk].available; }
    static const int maxDisk = 100;

private:
    int _diskCount;
    DiskPartition _disk[maxDisk];
    void _parseDisk (char buffer[]);
    int _stoi (string& s);
};

DiskInfo diskInfo;

int DiskInfo::_stoi (string& s)
{
    int ival;

    try {
        ival = stoi (s);
    }
    catch(exception &err) {
        ival = 0;
    }

    return ival;
}

void DiskInfo::_parseDisk (char buffer[])
{
    string line = buffer;
    int ival;

    istringstream stream(line);
    string name;
    long total;
    long used;
    long available;
    stream >> name >> total >> used >> available;

    // cout<<"disk="<<name<<", total="<<total<<", used="<<used<<", avail="<<available<<endl;

    // Ignore the header line
    if (name == "Filesystem")
        return;

    _disk[_diskCount].name = name;
    _disk[_diskCount].total = total;
    _disk[_diskCount].used = used;
    _disk[_diskCount].available = available;
    _diskCount++;
    // if (disk > _diskCount)
    //     _diskCount = disk;
}

void DiskInfo::read()
{
    std::array<char, 4096> buffer;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("df", "r"), pclose);

    if (!pipe) {
        throw std::runtime_error("Failed to execute df!");
    }

    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr)
        _parseDisk (buffer.data());
}

JNIEXPORT void JNICALL Java_diskInfo_read (JNIEnv *env, jobject obj) {
    diskInfo.read();
}

JNIEXPORT jint JNICALL Java_diskInfo_diskCount (JNIEnv *env, jobject obj) {
    return diskInfo.diskCount ();
}

JNIEXPORT jstring JNICALL Java_diskInfo_getName (JNIEnv *env, jobject obj, jint disk) {
    jstring result;
    result = env->NewStringUTF(diskInfo.name (disk).c_str());
    return result;
}

JNIEXPORT jlong JNICALL Java_diskInfo_getTotal (JNIEnv *env, jobject obj, jint disk) {
    return diskInfo.total (disk);
}

JNIEXPORT jlong JNICALL Java_diskInfo_getUsed (JNIEnv *env, jobject obj, jint disk) {
    return diskInfo.used (disk);
}

JNIEXPORT jlong JNICALL Java_diskInfo_getAvailable (JNIEnv *env, jobject obj, jint disk) {
    return diskInfo.available (disk);
}

