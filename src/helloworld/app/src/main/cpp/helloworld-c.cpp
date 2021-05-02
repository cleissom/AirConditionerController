#include <jni.h>


extern "C" JNIEXPORT jstring JNICALL Java_com_example_helloworldndk_MainActivity_getMessage
        (JNIEnv *env, jobject thisObj) {
   return env->NewStringUTF("Hello from native code!");
};