#include <android/log.h>
#include <string.h>
#include <jni.h>

JNIEnv* jniEnv;



jstring JNICALL Java_com_example_bttest_MainActivity_stringFromJNI
  (JNIEnv *env, jobject thiz)
{
	return (*env)->NewStringUTF(env, "hello from jni, lskakaxi!");
}

int GetInstance(jclass obj_class, jobject *obj) {
	if (obj_class == NULL) return 0;
	jmethodID construction_id = (*jniEnv)->GetMethodID(jniEnv, obj_class, "<init>", "()V");
	if (construction_id == 0) return -1;
	*obj = (*jniEnv)->NewObject(jniEnv, obj_class, construction_id);
	if (*obj) return -2;

	return 1;
}

int InitCCallJava() {
	jobject bt_adapter;
	int bt_status;
	jclass BluetoothAdapter;
	jmethodID getDefaultAdapter;
	jmethodID isEnabled;
	jmethodID bt_disable;

	__android_log_print(ANDROID_LOG_INFO, "lskakaxi", "InitCCallJava begin");
	if (jniEnv == NULL)
		return 0;
	BluetoothAdapter = (*jniEnv)->FindClass(jniEnv, "android/bluetooth/BluetoothAdapter");
	if (BluetoothAdapter == NULL)
		return -1;
	__android_log_print(ANDROID_LOG_INFO, "lskakaxi", "BluetoothAdapter find ok, [%p]", BluetoothAdapter);

	getDefaultAdapter = (*jniEnv)->GetStaticMethodID(jniEnv,
			BluetoothAdapter, "getDefaultAdapter", "()Landroid/bluetooth/BluetoothAdapter;");
	bt_adapter = (*jniEnv)->CallStaticObjectMethod(jniEnv, BluetoothAdapter, getDefaultAdapter);
	isEnabled = (*jniEnv)->GetMethodID(jniEnv, BluetoothAdapter, "isEnabled", "()Z");
	bt_disable = (*jniEnv)->GetMethodID(jniEnv, BluetoothAdapter, "disable", "()Z");
	bt_status = (*jniEnv)->CallBooleanMethod(jniEnv, bt_adapter, isEnabled);
	__android_log_print(ANDROID_LOG_INFO, "lskakaxi", "BT status is %d", bt_status);
	if (bt_status)
		bt_status = (*jniEnv)->CallBooleanMethod(jniEnv, bt_adapter, bt_disable);
	__android_log_print(ANDROID_LOG_INFO, "lskakaxi", "BT status is %d", bt_status);


	(*jniEnv)->DeleteLocalRef(jniEnv, bt_adapter);
	return 1;
}
void Java_com_example_bttest_MainActivity_test()
{
	__android_log_print(ANDROID_LOG_INFO, "lskakaxi", "JNIEnv[%p]", jniEnv);
	InitCCallJava();
}

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	JNIEnv *env = NULL;
	jint ret = -1;

	if ((*vm)->GetEnv(vm, (void **)&env, JNI_VERSION_1_4) != JNI_OK) {
		__android_log_print(ANDROID_LOG_ERROR, "lskakaxi", "get JNIEnv error!");
		goto fail;
	}
	__android_log_print(ANDROID_LOG_INFO, "lskakaxi", "JNIEnv[%p]", env);
    jniEnv = env;
	ret = JNI_VERSION_1_4;
fail:
	return ret;
}
