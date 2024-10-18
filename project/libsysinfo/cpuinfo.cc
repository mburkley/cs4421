#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <array>

#include "cpuInfo.h"

using namespace std;

class cpuInfo
{
public:
    void read();
    int getCoresPerSocket() { return _coresPerSocket; }
    int getSocketCount() { return _socketCount; }
    int getSocketCount() { return _socketCount; }
private:
    string _architecture;
    string _model;
    int _vaddrbits;
    int _paddrbits;
    bool _littleEndian;
    int _threadsPerCore;
    int _coresPerSocket;
    int _socketCount;
    int _l1dCachseSize;
    int _l1iCacheSize;
    int _l2CacheSize;
    int _l3CacheSize;
    void _parse (string&, string &);
};

cpuInfo cpu;

void cpuInfo::_parse (string& key, string &value)
{
    if (key == "Architecture")
        _architecture = value;
    else if (key == "Byte Order")
        _littleEndian == (key == "Little Endian");
    else if (key == "Thread(s) per core")
        _threadsPerCore = stoi (value);
    else if (key == "Core(s) per socket")
        _coresPerSocket = stoi (value);
    else if (key == "Socket(s)")
        _socketCount = stoi (value);
    else if (key == "L1d cache")
        _l1dCacheSize = stoi (value);
    else if (key == "L1i cache")
        _l1iCacheSize = stoi (value);
    else if (key == "L2 cache")
        _l2CacheSize = stoi (value);
    else if (key == "L3 cache")
        _l3CacheSize = stoi (value);
}

void cpuInfo::read()
{
    std::array<char, 128> buffer;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("lscpu", "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        string line = buffer.data();
        int delim = line.find(':');
        if (delim == string::npos)
            continue;
        string key = line.substr (0, delim);
        delim++;
        while (buffer[delim] == ' ')
            delim++;
        string value = line.substr (delim, string::npos);
        cout << "K:" << key << "=V:"<<value;
        _parse (key, value);
    }
}

JNIEXPORT void JNICALL Java_cpuInfo_read (JNIEnv *env, jobject obj) {
    cpu.read();
}

JNIEXPORT jint JNICALL Java_cpuInfo_coresPerSocket
  (JNIEnv *env, jobject obj) {
   return cpu.getCoresPerSocket();
}

JNIEXPORT jint JNICALL Java_cpuInfo_socketCount
  (JNIEnv *env, jobject obj) {
   return cpu.getSocketCount();
}

JNIEXPORT jstring JNICALL Java_cpuInfo_getModel
    (JNIEnv *env, jobject obj)
{
    const char *model = "Intel(R) Core(TM) i5-9400F CPU @ 2.90GHz";

    jstring result = env->NewStringUTF(model);
    return result;
}

JNIEXPORT jint JNICALL Java_cpuInfo_getBusy
  (JNIEnv *env, jobject obj, jint core) {
   //  TODO return the busy percent for a specified core
   return 25;
}

JNIEXPORT jint JNICALL Java_cpuInfo_getIdle
  (JNIEnv *env, jobject obj, jint core) {
   //  TODO return the idle percent for a specified core
   return 75;
}

