

#include "NativeUtils.h"

const char * toChars(JNIEnv *env, jstring string) {
    return (string == NULL ? NULL : env->GetStringUTFChars(string, NULL));
}

struct niScope * getStruct(JNIEnv *env, jobject obj) {
    return (struct niScope *) (env->GetLongField(obj, env->GetFieldID(env->GetObjectClass(obj), "nativeStruct", "J")));
}


//ViStatus error = VI_SUCCESS;
//ViChar errorSource[MAX_FUNCTION_NAME_SIZE];

void errorCheck(JNIEnv *env, jobject obj, ViStatus error, ViChar errorSource[MAX_FUNCTION_NAME_SIZE]) {
    if (error != VI_SUCCESS) {
        ViChar errorMessage[MAX_ERROR_DESCRIPTION] = " ";
        niScope_errorHandler(getStruct(env, obj)->viSession, error, errorSource, errorMessage);
        if (error < VI_SUCCESS) {
            env->ThrowNew(env->FindClass("tw/edu/sju/ee/eea/jni/scope/NIScopeException"), errorMessage);
        } else {
            jmethodID jmid = env->GetMethodID(env->GetObjectClass(obj), "warning", "(Ljava/lang/String;)V");
            env->CallVoidMethod(obj, jmid, env->NewStringUTF(errorMessage));
        }
    }
}