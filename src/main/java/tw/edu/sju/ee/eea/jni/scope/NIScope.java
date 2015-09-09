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

    //866
    public native void close();

    //869
    public native void autoSetup() throws NIScopeException;

    //871
    //Vertical Subsystem Configuration -----------------------------------------
    public native void configureVertical(String channelList, double range, double offset, int coupling, double probeAttenuation, boolean enabled) throws NIScopeException;

    public native void configureChanCharacteristics(String channelList, double inputImpedance, double maxInputFrequency) throws NIScopeException;

    //886
    //Horizontal Subsystem Configuration ---------------------------------------
    public native void configureHorizontalTiming(double minSampleRate, int minNumPts, double refPosition, int numRecords, boolean enforceRealtime) throws NIScopeException;

    //943
    public native void configureTriggerImmediate() throws NIScopeException;

    //976
    //Waveform Acquisition Subsystem -------------------------------------------
    public native void configureAcquisition(int acquisitionType) throws NIScopeException;

    public native void initiateAcquisition() throws NIScopeException;

    //1031
    public native void read(String channelList, double timeout, int numSamples, double[] wfm, WFMInfo[] wfmInfo) throws NIScopeException;

    public native void fetch(String channelList, double timeout, int numSamples, double[] wfm, WFMInfo[] wfmInfo) throws NIScopeException;

    //1084
    public native int actualNumWfms(String channelList) throws NIScopeException;

    //1092
    public native int actualRecordLength() throws NIScopeException;

    public native double sampleRate() throws NIScopeException;

    //1221
    public native void setAttributeViBoolean(String channelList, int attributeId, boolean value) throws NIScopeException;

    //**************************************************************************
    //Test----------------------------------------------------------------------
    public native void test();
}
