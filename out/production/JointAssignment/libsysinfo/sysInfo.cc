/*
 *  Example JNI class
 *
 *  Copyright (c) 2024 Mark Burkley (mark.burkley@ul.ie)
 */

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

