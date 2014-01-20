
#include <windows.h>
#include <stdio.h>
#include "tw_edu_sju_ee_eea_jni_scope_NIScope.h"
#define _MSC_VER  1200
#include "niScope.h"

#define MAX_STRING_SIZE 50

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_construct
(JNIEnv *env, jobject obj) {
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_destruct
(JNIEnv *env, jobject obj) {
}

JNIEXPORT jboolean JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_isAlive
(JNIEnv *env, jobject obj) {
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_test
(JNIEnv *env, jobject obj) {
    printf("Hello NIScope");
    ViSession vi = VI_NULL;
    ViStatus error = VI_SUCCESS;
    ViChar errorSource[MAX_FUNCTION_NAME_SIZE];
    ViChar errorMessage[MAX_ERROR_DESCRIPTION] = " ";

    // Variables used to get values from the GUI
    ViChar resourceName[MAX_STRING_SIZE];
    ViChar channelName[MAX_STRING_SIZE];
    ViInt32 actualRecordLength;
    ViReal64 actualSampleRate;

    // Default values used in this example
    ViReal64 timeout = 5.000;

    // Waveforms
    struct niScope_wfmInfo wfmInfo;
    ViReal64 *waveformPtr = NULL;

    // set default values
    strcpy(resourceName, "PXI1Slot4");
    strcpy(channelName, "0");
    // Obtain the resource name of the device from the user interface
    //    scanf("%s", &resourceName);
    //    scanf("%s", &channelName);

    // Open the NI-SCOPE instrument handle
    handleErr(niScope_init(resourceName, NISCOPE_VAL_FALSE, NISCOPE_VAL_FALSE, &vi));

    // Call auto setup, finds a signal and configures all necessary parameters
    handleErr(niScope_AutoSetup(vi));

    // Get the actual record length and actual sample rate that will be used
    handleErr(niScope_ActualRecordLength(vi, &actualRecordLength));

    handleErr(niScope_SampleRate(vi, &actualSampleRate));

    waveformPtr = (ViReal64*) malloc(sizeof (ViReal64) * actualRecordLength);

    // If memory allocation fails, return an error message
    if (waveformPtr == NULL)
        handleErr(NISCOPE_ERROR_INSUFFICIENT_MEMORY);

    // Read the data (Initiate the acquisition, and fetch the data)
    handleErr(niScope_Read(vi, channelName, timeout, actualRecordLength, waveformPtr, &wfmInfo));

    printf("haha");
    fflush(stdout);
    // Plot the waveform
    //    PlotWfms(waveformPtr, &wfmInfo, actualRecordLength, actualSampleRate);
//    if (&wfmInfo && waveformPtr)
//        asciiPlot(waveformPtr, wfmInfo.actualSamples);
    int i;
    for(i = 0; i < wfmInfo.actualSamples; i++) {
        printf("%f, ", waveformPtr[i]);
    }
    printf("Actual record length: %d\n", actualRecordLength);
    printf("Actual sample rate: %.2f\n", actualSampleRate);

Error:
    if (waveformPtr)
        free(waveformPtr);

    // Display messages
    if (error != VI_SUCCESS)
        niScope_errorHandler(vi, error, errorSource, errorMessage); // Intrepret the error
    else
        strcpy(errorMessage, "Acquisition successful!");

    printf("Error %x: %s\n", error, errorMessage);
    fflush(stdout);

    // Close the session
    if (vi)
        niScope_close(vi);

    return;
}