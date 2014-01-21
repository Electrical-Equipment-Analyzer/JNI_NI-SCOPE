
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

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_read
(JNIEnv *env, jobject obj, jstring channelList, jdouble timeout, jint numSamples, jdoubleArray jwfm, jobject jwfmInfo) {
    ViReal64 wfm[env->GetArrayLength(jwfm)];
    struct niScope_wfmInfo wfmInfo;
    handleErrOverride(niScope_Read(getStruct(env, obj)->viSession, toChars(env, channelList), timeout, numSamples, wfm, &wfmInfo));
    env->SetDoubleArrayRegion(jwfm, 0, env->GetArrayLength(jwfm), (const jdouble*) wfm);
    jclass clazz = env->GetObjectClass(jwfmInfo);
    env->SetDoubleField(jwfmInfo, env->GetFieldID(clazz, "absoluteInitialX", "D"), wfmInfo.absoluteInitialX);
    env->SetDoubleField(jwfmInfo, env->GetFieldID(clazz, "relativeInitialX", "D"), wfmInfo.relativeInitialX);
    env->SetDoubleField(jwfmInfo, env->GetFieldID(clazz, "xIncrement", "D"), wfmInfo.xIncrement);
    env->SetIntField(jwfmInfo, env->GetFieldID(clazz, "actualSamples", "I"), wfmInfo.actualSamples);
    env->SetDoubleField(jwfmInfo, env->GetFieldID(clazz, "offset", "D"), wfmInfo.offset);
    env->SetDoubleField(jwfmInfo, env->GetFieldID(clazz, "gain", "D"), wfmInfo.gain);
    env->SetDoubleField(jwfmInfo, env->GetFieldID(clazz, "reserved1", "D"), wfmInfo.reserved1);
    env->SetDoubleField(jwfmInfo, env->GetFieldID(clazz, "reserved2", "D"), wfmInfo.reserved2);
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

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_test
(JNIEnv *env, jobject obj) {
    printf("Hello NIScope\n");
    fflush(stdout);

    //    ViSession vi = VI_NULL;
    ViStatus error = VI_SUCCESS;
    ViChar errorSource[MAX_FUNCTION_NAME_SIZE];
    ViChar errorMessage[MAX_ERROR_DESCRIPTION] = " ";

    // Variables used to get values from the GUI
    //    ViChar resourceName[MAX_STRING_SIZE];
    //    ViChar channelName[MAX_STRING_SIZE];
    ViInt32 actualRecordLength;
    ViReal64 actualSampleRate;

    // Default values used in this example
    ViReal64 timeout = 5.000;

    // Waveforms
    struct niScope_wfmInfo wfmInfo;
    ViReal64 *waveformPtr = NULL;

    // set default values
    //    strcpy(resourceName, "PXI1Slot4");
    //    strcpy(channelName, "0");

    ViRsrc resourceName = "PXI1Slot4";
    ViConstString channelList = "0,1";

    // Open the NI-SCOPE instrument handle
    //    handleErr(niScope_init(resourceName, NISCOPE_VAL_FALSE, NISCOPE_VAL_FALSE, &getStruct(env, obj)->viSession));

    // Call auto setup, finds a signal and configures all necessary parameters
    //    handleErr(niScope_AutoSetup(getStruct(env, obj)->viSession));

    // Get the actual record length and actual sample rate that will be used
    handleErr(niScope_ActualRecordLength(getStruct(env, obj)->viSession, &actualRecordLength));

    handleErr(niScope_SampleRate(getStruct(env, obj)->viSession, &actualSampleRate));

    waveformPtr = (ViReal64*) malloc(sizeof (ViReal64) * actualRecordLength * 2);

    // If memory allocation fails, return an error message
    if (waveformPtr == NULL)
        handleErr(NISCOPE_ERROR_INSUFFICIENT_MEMORY);

    // Read the data (Initiate the acquisition, and fetch the data)
    handleErr(niScope_Read(getStruct(env, obj)->viSession, channelList, timeout, actualRecordLength, waveformPtr, &wfmInfo));

    printf("Actual record length: %d\n", actualRecordLength);
    printf("Actual sample rate: %.2f\n", actualSampleRate);
    printf("wfmInfo.actualSamples %d\n", wfmInfo.actualSamples);
    int i;
    for (i = 0; i < wfmInfo.actualSamples; i++) {
        printf("%f, ", waveformPtr[i]);
    }
    printf("\n");
    for (i = wfmInfo.actualSamples; i < wfmInfo.actualSamples * 2; i++) {
        printf("%f, ", waveformPtr[i]);
    }
    printf("\n");

Error:
    if (waveformPtr)
        free(waveformPtr);

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