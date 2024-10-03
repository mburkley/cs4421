#include "sysInfo.h"
#include <string.h>

// Test function, TODO delete
JNIEXPORT jint JNICALL Java_sysInfo_intMethod
  (JNIEnv *env, jobject obj, jint num) {
   return num * num;
}

JNIEXPORT jint JNICALL Java_cpuInfo_intMethod
  (JNIEnv *env, jobject obj, jint num) {
   return num * num;
}

JNIEXPORT jstring JNICALL Java_sysInfo_stringMethod
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

// int main(){}
