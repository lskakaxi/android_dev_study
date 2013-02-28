#include <string.h>
#include <jni.h>

jstring JNICALL Java_com_example_bttest_MainActivity_stringFromJNI
  (JNIEnv *env, jobject thiz)
{
	return (*env)->NewStringUTF(env, "hello from jni, lskakaxi!");
}

void test()
{
}
