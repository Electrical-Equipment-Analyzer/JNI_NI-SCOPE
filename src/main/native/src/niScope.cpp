
#include "NativeUtils.h"
#include "tw_edu_sju_ee_eea_jni_scope_NIScope.h"

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_construct
(JNIEnv *env, jobject obj) {
    niScope *niScope_struct = (niScope *) malloc(sizeof (*niScope_struct));
    env->SetLongField(obj, env->GetFieldID(env->GetObjectClass(obj), "nativeStruct", "J"), (jlong) niScope_struct);
    niScope_struct->viSession = VI_NULL;
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_destruct
(JNIEnv *env, jobject obj) {
    struct niScope *niScope_struct = getStruct(env, obj);
    niScope_struct->viSession = VI_NULL;
    free(niScope_struct);
}

JNIEXPORT jboolean JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_isAlive
(JNIEnv *env, jobject obj) {
    return (getStruct(env, obj)->viSession != VI_NULL);
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_init
(JNIEnv *env, jobject obj, jstring resourceName, jboolean IDQuery, jboolean resetDevice) {
    handleErrOverride(niScope_init((ViRsrc) toChars(env, resourceName), IDQuery, resetDevice, &getStruct(env, obj)->viSession));
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_close
(JNIEnv *env, jobject obj) {
    niScope_close(getStruct(env, obj)->viSession);
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_autoSetup
(JNIEnv *env, jobject obj) {
    handleErrOverride(niScope_AutoSetup(getStruct(env, obj)->viSession));
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_configureVertical
(JNIEnv *env, jobject obj, jstring channelList, jdouble range, jdouble offset, jint coupling, jdouble probeAttenuation, jboolean enabled) {
    handleErrOverride(niScope_ConfigureVertical(getStruct(env, obj)->viSession, toChars(env, channelList), range, offset, coupling, probeAttenuation, enabled));
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_configureChanCharacteristics
(JNIEnv *env, jobject obj, jstring channelList, jdouble inputImpedance, jdouble maxInputFrequency) {
    handleErrOverride(niScope_ConfigureChanCharacteristics(getStruct(env, obj)->viSession, toChars(env, channelList), inputImpedance, maxInputFrequency));
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_configureHorizontalTiming
(JNIEnv *env, jobject obj, jdouble minSampleRate, jint minNumPts, jdouble refPosition, jint numRecords, jboolean enforceRealtime) {
    handleErrOverride(niScope_ConfigureHorizontalTiming(getStruct(env, obj)->viSession, minSampleRate, minNumPts, refPosition, numRecords, enforceRealtime));
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_configureTriggerImmediate
(JNIEnv *env, jobject obj) {
    handleErrOverride(niScope_ConfigureTriggerImmediate(getStruct(env, obj)->viSession));
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_configureAcquisition
(JNIEnv *env, jobject obj, jint acquisitionType) {
    handleErrOverride(niScope_ConfigureAcquisition(getStruct(env, obj)->viSession, acquisitionType));
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_initiateAcquisition
(JNIEnv *env, jobject obj) {
    handleErrOverride(niScope_InitiateAcquisition(getStruct(env, obj)->viSession));
}

jobject wfmInfoTrans(JNIEnv *env, jobject obj, struct niScope_wfmInfo* wfmInfo) {
    jclass clazz = env->FindClass("tw/edu/sju/ee/eea/jni/scope/NIScope$WFMInfo");
    jmethodID constructor = env->GetMethodID(clazz, "<init>", "()V");
    jobject jwfmInfo = env->NewObject(clazz, constructor);
    env->SetDoubleField(jwfmInfo, env->GetFieldID(clazz, "absoluteInitialX", "D"), wfmInfo->absoluteInitialX);
    env->SetDoubleField(jwfmInfo, env->GetFieldID(clazz, "relativeInitialX", "D"), wfmInfo->relativeInitialX);
    env->SetDoubleField(jwfmInfo, env->GetFieldID(clazz, "xIncrement", "D"), wfmInfo->xIncrement);
    env->SetIntField(jwfmInfo, env->GetFieldID(clazz, "actualSamples", "I"), wfmInfo->actualSamples);
    env->SetDoubleField(jwfmInfo, env->GetFieldID(clazz, "offset", "D"), wfmInfo->offset);
    env->SetDoubleField(jwfmInfo, env->GetFieldID(clazz, "gain", "D"), wfmInfo->gain);
    env->SetDoubleField(jwfmInfo, env->GetFieldID(clazz, "reserved1", "D"), wfmInfo->reserved1);
    env->SetDoubleField(jwfmInfo, env->GetFieldID(clazz, "reserved2", "D"), wfmInfo->reserved2);
    return jwfmInfo;
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_read
(JNIEnv *env, jobject obj, jstring channelList, jdouble timeout, jint numSamples, jdoubleArray jwfm, jobjectArray jwfmInfo) {
    ViReal64 wfm[env->GetArrayLength(jwfm)];
    niScope_wfmInfo wfmInfo[env->GetArrayLength(jwfmInfo)];
    handleErrOverride(niScope_Read(getStruct(env, obj)->viSession, toChars(env, channelList), timeout, numSamples, wfm, wfmInfo));
    env->SetDoubleArrayRegion(jwfm, 0, env->GetArrayLength(jwfm), (const jdouble*) wfm);
    for (int i = 0; i < env->GetArrayLength(jwfmInfo); i++) {
        env->SetObjectArrayElement(jwfmInfo, i, wfmInfoTrans(env, obj, &wfmInfo[i]));
    }
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_fetch
(JNIEnv *env, jobject obj, jstring channelList, jdouble timeout, jint numSamples, jdoubleArray jwfm, jobjectArray jwfmInfo) {
    ViReal64 wfm[env->GetArrayLength(jwfm)];
    niScope_wfmInfo wfmInfo[env->GetArrayLength(jwfmInfo)];
    handleErrOverride(niScope_Fetch(getStruct(env, obj)->viSession, toChars(env, channelList), timeout, numSamples, wfm, wfmInfo));
    env->SetDoubleArrayRegion(jwfm, 0, env->GetArrayLength(jwfm), (const jdouble*) wfm);
    for (int i = 0; i < env->GetArrayLength(jwfmInfo); i++) {
        env->SetObjectArrayElement(jwfmInfo, i, wfmInfoTrans(env, obj, &wfmInfo[i]));
    }
}

JNIEXPORT jint JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_actualNumWfms
(JNIEnv *env, jobject obj, jstring channelList) {
    ViInt32 numWfms;
    handleErrOverride(niScope_ActualNumWfms(getStruct(env, obj)->viSession, toChars(env, channelList), &numWfms));
    return numWfms;
}

JNIEXPORT jint JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_actualRecordLength
(JNIEnv *env, jobject obj) {
    ViInt32 actualRecordLength;
    handleErrOverride(niScope_ActualRecordLength(getStruct(env, obj)->viSession, &actualRecordLength));
    return actualRecordLength;
}

JNIEXPORT jdouble JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_sampleRate
(JNIEnv *env, jobject obj) {
    ViReal64 actualSampleRate;
    handleErrOverride(niScope_SampleRate(getStruct(env, obj)->viSession, &actualSampleRate));
    return actualSampleRate;
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_setAttributeViBoolean
(JNIEnv *env, jobject obj, jstring channelList, jint attributeId, jboolean value) {
    niScope_SetAttributeViBoolean(getStruct(env, obj)->viSession, toChars(env, channelList), attributeId, value);
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_test
(JNIEnv *env, jobject obj) {
    printf("Hello NIScope\n");
    fflush(stdout);

    ViSession vi = getStruct(env, obj)->viSession;
    ViStatus error = VI_SUCCESS;
    ViChar errorSource[MAX_FUNCTION_NAME_SIZE];
    ViChar errorMessage[MAX_ERROR_DESCRIPTION] = " ";

    ViRsrc resourceName = "PXI1Slot4";
    ViConstString channelName = "0,1";

    //    printf("Actual record length: %d\n", actualRecordLength);
    //    printf("Actual sample rate: %.2f\n", actualSampleRate);
    //    printf("wfmInfo.actualSamples %d\n", wfmInfoPtr[0].actualSamples);
    //    int i;
    //    for (i = 0; i < wfmInfoPtr->actualSamples; i++) {
    //        printf("%f, ", waveformPtr[i]);
    //    }
    //    printf("\n");
    //    for (i = wfmInfoPtr->actualSamples; i < wfmInfoPtr->actualSamples * 2; i++) {
    //        printf("%f, ", waveformPtr[i]);
    //    }
    //    printf("\n");

Error:

    //    if (wfmInfoPtr)
    //        free(wfmInfoPtr);
    //    if (waveformPtr)
    //        free(waveformPtr);

    // Display messages
    if (error != VI_SUCCESS) {
        printf("%s\n", errorSource);
        niScope_errorHandler(getStruct(env, obj)->viSession, error, errorSource, errorMessage); // Intrepret the error
    } else {
        strcpy(errorMessage, "Acquisition successful!");
    }
    printf("Error %x: %s\n", error, errorMessage);
    fflush(stdout);

    // Close the session
    if (getStruct(env, obj)->viSession)
        niScope_close(getStruct(env, obj)->viSession);

    return;
}