#include "sysInfo.h"
#include <string.h>

JNIEXPORT jint JNICALL Java_sysInfo_intMethod
  (JNIEnv *env, jobject obj, jint num) {
   return num * num;
}

int main(){}
