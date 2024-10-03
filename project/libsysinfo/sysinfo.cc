#include <string.h>

#include "cpuInfo.h"
#include "sysInfo.h"

// Example JNI function that returns an int
JNIEXPORT jint JNICALL Java_sysInfo_intExample
  (JNIEnv *env, jobject obj, jint num) {
   return num * num;
}

// Example JNI function that returns a string
JNIEXPORT jstring JNICALL Java_sysInfo_stringExample
    (JNIEnv *env, jobject obj, jstring string)
{
    const char *name = env->GetStringUTFChars(string, NULL);
    char msg[60] = "Hello ";
    jstring result;

    strcat(msg, name);
    env->ReleaseStringUTFChars(string, name);
    // puts(msg);
    result = env->NewStringUTF(msg);
    return result;
}

JNIEXPORT jint JNICALL Java_cpuInfo_coreCount
  (JNIEnv *env, jobject obj) {
   //  TODO get actual number of cores from /proc/cpuinfo
   return 8;
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

