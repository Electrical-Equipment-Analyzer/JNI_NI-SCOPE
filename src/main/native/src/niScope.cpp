
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

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_initWithOptions
(JNIEnv *env, jobject obj, jstring resourceName, jboolean IDQuery, jboolean resetDevice, jstring optionString) {
    handleErrOverride(niScope_InitWithOptions((ViRsrc) toChars(env, resourceName), IDQuery, resetDevice, (ViConstString) toChars(env, optionString), &getStruct(env, obj)->viSession));
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

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_configureClock
(JNIEnv *env, jobject obj, jstring inputClockSource, jstring outputClockSource, jstring clockSyncPulseSource, jboolean masterEnabled) {
    handleErrOverride(niScope_ConfigureClock(getStruct(env, obj)->viSession, toChars(env, inputClockSource), toChars(env, outputClockSource), toChars(env, clockSyncPulseSource), masterEnabled));
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_exportSignal
(JNIEnv *env, jobject obj, jint signal, jstring signalIdentifier, jstring outputTerminal) {
    handleErrOverride(niScope_ExportSignal(getStruct(env, obj)->viSession, signal, toChars(env, signalIdentifier), toChars(env, outputTerminal)));
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_adjustSampleClockRelativeDelay
(JNIEnv *env, jobject obj, jdouble delay) {
    handleErrOverride(niScope_AdjustSampleClockRelativeDelay(getStruct(env, obj)->viSession, delay));
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_configureTriggerEdge
(JNIEnv *env, jobject obj, jstring triggerSource, jdouble level, jint slope, jint triggerCoupling, jdouble holdoff, jdouble delay) {
    handleErrOverride(niScope_ConfigureTriggerEdge(getStruct(env, obj)->viSession, toChars(env, triggerSource), level, slope, triggerCoupling, holdoff, delay));
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_configureTriggerHysteresis
(JNIEnv *env, jobject obj, jstring triggerSource, jdouble level, jdouble hysteresis, jint slope, jint triggerCoupling, jdouble holdoff, jdouble delay) {
    handleErrOverride(niScope_ConfigureTriggerHysteresis(getStruct(env, obj)->viSession, toChars(env, triggerSource), level, hysteresis, slope, triggerCoupling, holdoff, delay));
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_configureTriggerWindow
(JNIEnv *env, jobject obj, jstring triggerSource, jdouble lowLevel, jdouble highLevel, jint windowMode, jint triggerCoupling, jdouble holdoff, jdouble delay) {
    handleErrOverride(niScope_ConfigureTriggerWindow(getStruct(env, obj)->viSession, toChars(env, triggerSource), lowLevel, highLevel, windowMode, triggerCoupling, holdoff, delay));
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_configureTriggerSoftware
(JNIEnv *env, jobject obj, jdouble holdoff, jdouble delay) {
    handleErrOverride(niScope_ConfigureTriggerSoftware(getStruct(env, obj)->viSession, holdoff, delay));
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_sendSoftwareTriggerEdge
(JNIEnv *env, jobject obj, jint whichTrigger) {
    handleErrOverride(niScope_SendSoftwareTriggerEdge(getStruct(env, obj)->viSession, whichTrigger));
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_configureTriggerImmediate
(JNIEnv *env, jobject obj) {
    handleErrOverride(niScope_ConfigureTriggerImmediate(getStruct(env, obj)->viSession));
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_configureTriggerDigital
(JNIEnv *env, jobject obj, jstring triggerSource, jint slope, jdouble holdoff, jdouble delay) {
    handleErrOverride(niScope_ConfigureTriggerDigital(getStruct(env, obj)->viSession, toChars(env, triggerSource), slope, holdoff, delay));
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_configureTriggerVideo
(JNIEnv *env, jobject obj, jstring triggerSource, jboolean enableDCRestore, jint signalFormat, jint event, jint lineNumber, jint polarity, jint triggerCoupling, jdouble holdoff, jdouble delay) {
    handleErrOverride(niScope_ConfigureTriggerVideo(getStruct(env, obj)->viSession, toChars(env, triggerSource), enableDCRestore, signalFormat, event, lineNumber, polarity, triggerCoupling, holdoff, delay));
}

JNIEXPORT jdouble JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_configureEqualizationFilterCoefficients
(JNIEnv *env, jobject obj, jstring channel, jint numberOfCoefficients) {
    ViReal64 coefficients;
    handleErrOverride(niScope_ConfigureEqualizationFilterCoefficients(getStruct(env, obj)->viSession, toChars(env, channel), numberOfCoefficients, &coefficients));
    return coefficients;
}

JNIEXPORT jint JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_getFrequencyResponse
(JNIEnv *env, jobject obj, jstring channelName, jint bufferSize, jdoubleArray jfrequencies, jdoubleArray jamplitudes, jdoubleArray jphases) {
    ViReal64 frequencies[env->GetArrayLength(jfrequencies)];
    env->GetDoubleArrayRegion(jfrequencies, 0, env->GetArrayLength(jfrequencies),  (jdouble*) frequencies);
    ViReal64 amplitudes[env->GetArrayLength(jamplitudes)];
    env->GetDoubleArrayRegion(jamplitudes, 0, env->GetArrayLength(jamplitudes),  (jdouble*) amplitudes);
    ViReal64 phases[env->GetArrayLength(jphases)];
    env->GetDoubleArrayRegion(jphases, 0, env->GetArrayLength(jphases),  (jdouble*) phases);
    ViInt32 numberOfFrequencies;
    handleErrOverride(niScope_GetFrequencyResponse(getStruct(env, obj)->viSession, toChars(env, channelName), bufferSize, frequencies, amplitudes, phases, &numberOfFrequencies));
    return numberOfFrequencies;
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_configureAcquisition
(JNIEnv *env, jobject obj, jint acquisitionType) {
    handleErrOverride(niScope_ConfigureAcquisition(getStruct(env, obj)->viSession, acquisitionType));
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_initiateAcquisition
(JNIEnv *env, jobject obj) {
    handleErrOverride(niScope_InitiateAcquisition(getStruct(env, obj)->viSession));
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_abort
  (JNIEnv *env, jobject obj){
   handleErrOverride(niScope_Abort(getStruct(env, obj)->viSession));
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_commit
  (JNIEnv *env, jobject obj){
   handleErrOverride(niScope_Commit(getStruct(env, obj)->viSession)); 
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

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_fetchBinary8
  (JNIEnv *env, jobject obj, jstring channelList, jdouble timeout, jint numSamples, jbyteArray jwfm, jobjectArray jwfmInfo){
    ViInt8 wfm[env->GetArrayLength(jwfm)];
    niScope_wfmInfo wfmInfo[env->GetArrayLength(jwfmInfo)];
    handleErrOverride(niScope_FetchBinary8(getStruct(env, obj)->viSession, toChars(env, channelList), timeout, numSamples, wfm, wfmInfo));
    env->SetByteArrayRegion(jwfm, 0, env->GetArrayLength(jwfm), (const jbyte*) wfm);
    for (int i = 0; i < env->GetArrayLength(jwfmInfo); i++) {
        env->SetObjectArrayElement(jwfmInfo, i, wfmInfoTrans(env, obj, &wfmInfo[i]));
    } 
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_fetchBinary16
  (JNIEnv *env, jobject obj, jstring channelList, jdouble timeout, jint numSamples, jshortArray jwfm, jobjectArray jwfmInfo){
    ViInt16 wfm[env->GetArrayLength(jwfm)];
    niScope_wfmInfo wfmInfo[env->GetArrayLength(jwfmInfo)];
    handleErrOverride(niScope_FetchBinary16(getStruct(env, obj)->viSession, toChars(env, channelList), timeout, numSamples, wfm, wfmInfo));
    env->SetShortArrayRegion(jwfm, 0, env->GetArrayLength(jwfm), (const jshort*) wfm);
    for (int i = 0; i < env->GetArrayLength(jwfmInfo); i++) {
        env->SetObjectArrayElement(jwfmInfo, i, wfmInfoTrans(env, obj, &wfmInfo[i]));
    } 
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_fetchBinary32
  (JNIEnv *env, jobject obj, jstring channelList, jdouble timeout, jint numSamples, jintArray jwfm, jobjectArray jwfmInfo){
    ViInt32 wfm[env->GetArrayLength(jwfm)];
    niScope_wfmInfo wfmInfo[env->GetArrayLength(jwfmInfo)];
    handleErrOverride(niScope_FetchBinary32(getStruct(env, obj)->viSession, toChars(env, channelList), timeout, numSamples, wfm, wfmInfo));
    env->SetIntArrayRegion(jwfm, 0, env->GetArrayLength(jwfm), (const jint*) wfm);
    for (int i = 0; i < env->GetArrayLength(jwfmInfo); i++) {
        env->SetObjectArrayElement(jwfmInfo, i, wfmInfoTrans(env, obj, &wfmInfo[i]));
    }
}

JNIEXPORT jint JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_acquisitionStatus
  (JNIEnv *env, jobject obj){
   ViInt32 status;
   handleErrOverride(niScope_AcquisitionStatus(getStruct(env, obj)->viSession,&status));
   return status;
}

JNIEXPORT jint JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_actualNumWfms
(JNIEnv *env, jobject obj, jstring channelList) {
    ViInt32 numWfms;
    handleErrOverride(niScope_ActualNumWfms(getStruct(env, obj)->viSession, toChars(env, channelList), &numWfms));
    return numWfms;
}

JNIEXPORT jint JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_actualMeasWfmSize
  (JNIEnv *env, jobject obj, jint arrayMeasFunction){
    ViInt32 measWfmSize;
    handleErrOverride(niScope_ActualMeasWfmSize(getStruct(env, obj)->viSession,arrayMeasFunction,&measWfmSize));
    return measWfmSize;
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

JNIEXPORT jint JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_sampleMode
  (JNIEnv *env, jobject obj){
   ViInt32 sampleMode;
   handleErrOverride(niScope_SampleMode(getStruct(env, obj)->viSession, &sampleMode));
   return sampleMode;
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_addWaveformProcessing
  (JNIEnv *env, jobject obj, jstring channelList, jint measFunction){
   handleErrOverride(niScope_AddWaveformProcessing(getStruct(env, obj)->viSession,toChars(env, channelList),measFunction)); 
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_clearWaveformProcessing
  (JNIEnv *env, jobject obj, jstring channelList){
   handleErrOverride(niScope_ClearWaveformProcessing(getStruct(env, obj)->viSession,toChars(env, channelList))); 
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_clearWaveformMeasurementStats
  (JNIEnv *env, jobject obj, jstring channelList, jint measFunction){
   handleErrOverride(niScope_ClearWaveformMeasurementStats(getStruct(env, obj)->viSession,toChars(env, channelList),measFunction)); 
}

JNIEXPORT jdouble JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_readMeasurement
  (JNIEnv *env, jobject obj, jstring channelList, jdouble timeout, jint scalarMeasFunction){
    ViReal64 result;
    handleErrOverride(niScope_ReadMeasurement(getStruct(env, obj)->viSession,toChars(env, channelList),timeout,scalarMeasFunction,&result));
    return result;
    
}


JNIEXPORT jdouble JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_fetchMeasurement
  (JNIEnv *env, jobject obj, jstring channelList, jdouble timeout, jint scalarMeasFunction){
    ViReal64 result;
    handleErrOverride(niScope_FetchMeasurement(getStruct(env, obj)->viSession,toChars(env, channelList),timeout,scalarMeasFunction,&result));
    return result;
    
}
JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_reset
  (JNIEnv *env, jobject obj){
    handleErrOverride(niScope_reset(getStruct(env, obj)->viSession));
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_disable
  (JNIEnv *env, jobject obj){
    handleErrOverride(niScope_Disable(getStruct(env, obj)->viSession));
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_resetDevice
  (JNIEnv *env, jobject obj){
    handleErrOverride(niScope_ResetDevice(getStruct(env, obj)->viSession));  
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_probeCompensationSignalStart
  (JNIEnv *env, jobject obj){
   handleErrOverride(niScope_ProbeCompensationSignalStart(getStruct(env, obj)->viSession));  
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_probeCompensationSignalStop
  (JNIEnv *env, jobject obj){
   handleErrOverride(niScope_ProbeCompensationSignalStop(getStruct(env, obj)->viSession));  
}


JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_setAttributeViBoolean
(JNIEnv *env, jobject obj, jstring channelList, jint attributeId, jboolean value) {
    niScope_SetAttributeViBoolean(getStruct(env, obj)->viSession, toChars(env, channelList), attributeId, value);
}

JNIEXPORT jint JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_setDDCFilterCoefficients
  (JNIEnv *env, jobject obj, jstring channel, jint coefficientType, jint numCoefficients){
   ViInt32 coefficients;
   handleErrOverride(niScope_SetDDCFilterCoefficients(getStruct(env, obj)->viSession, toChars(env, channel),coefficientType,numCoefficients,&coefficients)) ;
   return coefficients;
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_calSetSerialDACVoltageEeprom
  (JNIEnv *env, jobject obj, jfloat serialDACVolts){
   handleErrOverride(niScope_CalSetSerialDACVoltageEeprom(getStruct(env, obj)->viSession,serialDACVolts));
}

JNIEXPORT void JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_calSetADCVoltageEeprom
  (JNIEnv *env, jobject obj, jfloat adcVoltageGain, jfloat adcVoltageOffset){
   handleErrOverride(niScope_CalSetADCVoltageEeprom(getStruct(env, obj)->viSession,adcVoltageGain,adcVoltageOffset)) ;
}

JNIEXPORT jfloat JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_calSetFREeprom
  (JNIEnv *env, jobject obj, jint numCoefficients){
    ViReal32 polynomialFitCoefficients;
    handleErrOverride(niScope_CalSetFREeprom(getStruct(env, obj)->viSession,numCoefficients,&polynomialFitCoefficients));
    return polynomialFitCoefficients;
}

JNIEXPORT jfloat JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_calGetSerialDACVoltageEeprom
  (JNIEnv *env, jobject obj){
    ViReal32 serialDACVolts;
    handleErrOverride(niScope_CalGetSerialDACVoltageEeprom(getStruct(env, obj)->viSession,&serialDACVolts));
    return serialDACVolts;
}

JNIEXPORT jfloat JNICALL Java_tw_edu_sju_ee_eea_jni_scope_NIScope_calGetFREeprom
  (JNIEnv *env, jobject obj, jint numCoefficients){
    ViReal32 polynomialFitCoefficients;
    handleErrOverride(niScope_CalGetFREeprom(getStruct(env, obj)->viSession,numCoefficients,&polynomialFitCoefficients));
    return polynomialFitCoefficients;
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