/*
 *  Mem information class.  Executes df and parses output into an of mounted mem
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

#include "memInfo.h"

using namespace std;

class MemInfo
{
public:
    void read();
    long total () { return _total; }
    long used () { return _used; }

private:
    long _total;
    long _used;
    void _parseMem (char buffer[]);
    int _stoi (string& s);
};

MemInfo memInfo;

int MemInfo::_stoi (string& s)
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

void MemInfo::_parseMem (char buffer[])
{
    string line = buffer;
    int ival;

    if (buffer[0] == ' ')
        return;

    istringstream stream(line);
    string name;
    long total;
    long used;
    stream >> name >> total >> used;

    if (name != "Mem:")
        return;

    cout<<"total="<<total<<", used="<<used<<endl;

    _total = total;
    _used = used;
}

void MemInfo::read()
{
    std::array<char, 4096> buffer;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("free", "r"), pclose);

    if (!pipe) {
        throw std::runtime_error("Failed to execute free!");
    }

    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr)
        _parseMem (buffer.data());
}

JNIEXPORT void JNICALL Java_memInfo_read (JNIEnv *env, jobject obj) {
    memInfo.read();
}

JNIEXPORT jint JNICALL Java_memInfo_getTotal (JNIEnv *env, jobject obj) {
    return memInfo.total ();
}

JNIEXPORT jint JNICALL Java_memInfo_getUsed (JNIEnv *env, jobject obj) {
    return memInfo.used ();
}

