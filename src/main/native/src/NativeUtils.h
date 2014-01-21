/* 
 * File:   NativeUtils.h
 * Author: Leo
 *
 * Created on 2013年11月25日, 下午 11:31
 */

#include <windows.h>
#include <jni.h>
#define _MSC_VER  1200
#include "niScope.h"

#ifndef NATIVEUTILS_H
#define	NATIVEUTILS_H

#ifdef	__cplusplus
extern "C" {
#endif

    struct niScope {
        ViSession viSession;
    };

    const char * toChars(JNIEnv *, jstring);
    struct niScope * getStruct(JNIEnv *, jobject);
    void errorCheck(JNIEnv *, jobject, ViStatus, ViChar []);

#define handleErrOverride(fCall) {\
    ViStatus error = VI_SUCCESS;ViChar errorSource[MAX_FUNCTION_NAME_SIZE];\
    handleErr(fCall);Error:errorCheck(env, obj, error, errorSource);}

#ifdef	__cplusplus
}
#endif

#endif	/* NATIVEUTILS_H */

