/*
 * Copyright (C) 2014 Leo
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
package tw.edu.sju.ee.eea.jni.scope;

import java.io.IOException;
import java.util.Arrays;
import java.util.logging.Level;
import java.util.logging.Logger;
import tw.edu.sju.ee.eea.jni.util.NativeUtils;

/**
 *
 * @author Leo
 */
public class NIScope {

    static {
        try {
            NativeUtils.loadLibraryFromJar("jniNIScope");
        } catch (IOException ex) {
            Logger.getLogger(NIScope.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    //**************************************************************************
    //Java Object
    private long nativeStruct;

    public NIScope() {
        construct();
    }

    @Override
    protected void finalize() throws Throwable {
        this.destruct();
        super.finalize();
    }

    private void warning(String msg) {
        Logger.getLogger(NIScope.class.getName()).log(Level.WARNING, msg);
    }

    //**************************************************************************
    //Native Object
    private native void construct();

    private native void destruct();

    public native boolean isAlive();

    //**************************************************************************
    //419
    public static final int ATTR_ENABLE_TIME_INTERLEAVED_SAMPLING = IVI.SPECIFIC_PUBLIC_ATTR_BASE + 128;

    //486
    public static final int VAL_DC = IVIScope.VAL_DC;

    //500
    public static final double VAL_1_MEG_OHM = 1000000.0;

    //562
    public static final int VAL_NORMAL = IVIScope.VAL_NORMAL;

    public static final String VAL_IMMEDIATE = "VAL_IMMEDIATE";

    //988
    public static class WFMInfo {

        double absoluteInitialX;
        double relativeInitialX;
        double xIncrement;
        int actualSamples;
        double offset;
        double gain;
        double reserved1;
        double reserved2;

        @Override
        public String toString() {
            return "WFMInfo{" + "absoluteInitialX=" + absoluteInitialX + ", relativeInitialX=" + relativeInitialX + ", xIncrement=" + xIncrement + ", actualSamples=" + actualSamples + ", offset=" + offset + ", gain=" + gain + ", reserved1=" + reserved1 + ", reserved2=" + reserved2 + '}';
        }

    }

    //**************************************************************************
    //855
    public native void init(String resourceName, boolean IDQuery, boolean resetDevice) throws NIScopeException;

    public native void initWithOptions(String resourceName, boolean IDQuery, boolean resetDevice, String optionString) throws NIScopeException;

    public native void close();

    public native void autoSetup() throws NIScopeException;

    //Vertical Subsystem Configuration -----------------------------------------
    public native void configureVertical(String channelList, double range, double offset, int coupling, double probeAttenuation, boolean enabled) throws NIScopeException;

    public native void configureChanCharacteristics(String channelList, double inputImpedance, double maxInputFrequency) throws NIScopeException;

    //Horizontal Subsystem Configuration ---------------------------------------
    public static class HorizontalTiming {

        public double minSampleRate = 10000;
        public int minNumPts = 1024;
        public double refPosition = 50;
        public int numRecords = 1;
        public boolean enforceRealtime = false;

    }

    public void configureHorizontalTiming(HorizontalTiming ht) throws NIScopeException {
        configureHorizontalTiming(ht.minSampleRate, ht.minNumPts, ht.refPosition, ht.numRecords, ht.enforceRealtime);
    }

    public native void configureHorizontalTiming(double minSampleRate, int minNumPts, double refPosition, int numRecords, boolean enforceRealtime) throws NIScopeException;

    public native void configureClock(String inputClockSource, String outputClockSource, String clockSyncPulseSource, boolean masterEnabled) throws NIScopeException;

    public native void exportSignal(int signal, String signalIdentifier, String outputTerminal) throws NIScopeException;

    public native void adjustSampleClockRelativeDelay(double delay) throws NIScopeException;

    public static void main(String[] args) {
        Trigger.Edge edge = new Trigger.Edge();

        System.out.println(Arrays.toString(edge.getClass().getFields()));
    }

    public abstract static class Trigger {

        public enum Slope {

            NEGATIVE, POSITIVE
        }

        public enum Coupling {

            AC, DC, GND
        }

        private Trigger() {
        }

        public abstract void configure(NIScope niScope) throws NIScopeException;

        @Override
        public String toString() {
            return getClass().getSimpleName();
        }

        public static class Edge extends Trigger {

            public int triggerSource = 0;
            public double level = 0;
            public Slope slope = Slope.NEGATIVE;
            public Coupling triggerCoupling = Coupling.DC;
            public double holdoff = 0;
            public double delay = 0;

            @Override
            public void configure(NIScope niScope) throws NIScopeException {
                niScope.configureTriggerEdge(String.valueOf(triggerSource), level, slope.ordinal(), triggerCoupling.ordinal(), holdoff, delay);
            }

        }

        public static class Immediate extends Trigger {

            @Override
            public void configure(NIScope niScope) throws NIScopeException {
                niScope.configureTriggerImmediate();
            }
        }

    }

    public void configureTrigger(Trigger trigger) throws NIScopeException {
        trigger.configure(this);
    }

    public native void configureTriggerEdge(String triggerSource, double level, int slope, int triggerCoupling, double holdoff, double delay) throws NIScopeException;

    public native void configureTriggerHysteresis(String triggerSource, double level, double hysteresis, int slope, int triggerCoupling, double holdoff, double delay) throws NIScopeException;

    public native void configureTriggerWindow(String triggerSource, double lowLevel, double highLevel, int windowMode, int triggerCoupling, double holdoff, double delay) throws NIScopeException;

    public native void configureTriggerSoftware(double holdoff, double delay) throws NIScopeException;

    public native void sendSoftwareTriggerEdge(int whichTrigger) throws NIScopeException;

    public native void configureTriggerImmediate() throws NIScopeException;

    public native void configureTriggerDigital(String triggerSource, int slope, double holdoff, double delay) throws NIScopeException;

    public native void configureTriggerVideo(String triggerSource, boolean enableDCRestore, int signalFormat, int event, int lineNumber, /* ignored if not applicable */ int polarity, int triggerCoupling, double holdoff, double delay) throws NIScopeException;

    public native double configureEqualizationFilterCoefficients(String channel, int numberOfCoefficients) throws NIScopeException;

    public native int getFrequencyResponse(String channelName, int bufferSize, double[] frequencies, double[] amplitudes, double[] phases) throws NIScopeException;

    //Waveform Acquisition Subsystem -------------------------------------------
    public native void configureAcquisition(int acquisitionType) throws NIScopeException;

    public native void initiateAcquisition() throws NIScopeException;

    public native void abort() throws NIScopeException;

    public native void commit() throws NIScopeException;

    //1031
    public native void read(String channelList, double timeout, int numSamples, double[] wfm, WFMInfo[] wfmInfo) throws NIScopeException;

    public native void fetch(String channelList, double timeout, int numSamples, double[] wfm, WFMInfo[] wfmInfo) throws NIScopeException;

    public native void fetchBinary8(String channelList, double timeout, int numSamples, byte wfm[], WFMInfo[] wfmInfo) throws NIScopeException;

    public native void fetchBinary16(String channelList, double timeout, int numSamples, short wfm[], WFMInfo[] wfmInfo) throws NIScopeException;

    //1059
    public native void fetchBinary32(String channelList, double timeout, int numSamples, int wfm[], WFMInfo[] wfmInfo) throws NIScopeException;
    //1066

    //1073
    //1081
    public enum acquisitionStatus {

        COMPLETE,
        IN_PROGRESS,
        STATUS_UNKNOWN;

        static acquisitionStatus valueOf(int val) {
            switch (val) {
                case 0:
                    return IN_PROGRESS;
                case 1:
                    return COMPLETE;
                default:
                    return STATUS_UNKNOWN;
            }
        }

    }

    public acquisitionStatus getAcquisitionStatus() throws NIScopeException {
        return acquisitionStatus.valueOf(acquisitionStatus());
    }

    public native int acquisitionStatus() throws NIScopeException;

    public native int actualNumWfms(String channelList) throws NIScopeException;

    public native int actualMeasWfmSize(int arrayMeasFunction) throws NIScopeException;

    //1092
    public native int actualRecordLength() throws NIScopeException;

    public native double sampleRate() throws NIScopeException;

    public native int sampleMode() throws NIScopeException;

    /*--- Waveform Measurement Functions ----------------------------------------*/
    public native void addWaveformProcessing(String channelList, int measFunction) throws NIScopeException;

    public native void clearWaveformProcessing(String channelList) throws NIScopeException;

    public native void slearWaveformMeasurementStats(String channelList, int measFunction) throws NIScopeException;

    public native double readMeasurement(String channelList, double timeout, int scalarMeasFunction) throws NIScopeException;

    public native double fetchMeasurement(String channelList, double timeout, int scalarMeasFunction) throws NIScopeException;

    //1125
    //1136
    public native void reset() throws NIScopeException;

    public native void disable() throws NIScopeException;

    public native void resetDevice() throws NIScopeException;

    //1155
    //1162
    public native void probeCompensationSignalStart() throws NIScopeException;

    public native void probeCompensationSignalStop() throws NIScopeException;
    //1170

    //1176
    //1181
    //1186
    //1192
    //1194
    /*--- Typesafe Get, Set, and Check Attribute Functions ---------------------*/
    /* Note that the Get functions take a channelList but they return a single
     value.  Therefore, these functions return an error if the return value differs
     among the channels specified in the list. */
    //1200
    //1221
    public native void setAttributeViBoolean(String channelList, int attributeId, boolean value) throws NIScopeException;

    //1225
    /*--- NI-5620 Specific Functions ----------------------------------------*/
    public native int setDDCFilterCoefficients(String channel, int coefficientType, int numCoefficients) throws NIScopeException;

    public native void calSetSerialDACVoltageEeprom(float serialDACVolts) throws NIScopeException;

    public native void calSetADCVoltageEeprom(float adcVoltageGain, float adcVoltageOffset) throws NIScopeException;

    public native float calSetFREeprom(int numCoefficients) throws NIScopeException;

    public native float calGetSerialDACVoltageEeprom() throws NIScopeException;

    //1248
    public native float calGetFREeprom(int numCoefficients) throws NIScopeException;

    //1257
    //1260
    //1264
    //1269
    //1275
    //1281
    //1288
    //**************************************************************************
    //Test----------------------------------------------------------------------
    public native void test();
}
