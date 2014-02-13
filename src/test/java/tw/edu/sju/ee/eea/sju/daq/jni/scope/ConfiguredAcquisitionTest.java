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
package tw.edu.sju.ee.eea.sju.daq.jni.scope;

import java.util.Arrays;
import java.util.logging.Level;
import java.util.logging.Logger;
import junit.framework.TestCase;
import tw.edu.sju.ee.eea.jni.scope.NIScope;
import tw.edu.sju.ee.eea.jni.scope.NIScopeException;

/**
 *
 * @author Leo
 */
public class ConfiguredAcquisitionTest extends TestCase {

    public ConfiguredAcquisitionTest(String testName) {
        super(testName);
    }

    @Override
    protected void setUp() throws Exception {
        super.setUp();
    }

    @Override
    protected void tearDown() throws Exception {
        super.tearDown();
    }

    public void test() {

        String channelList = "0,1";

        NIScope niScope = null;
        try {
            niScope = new NIScope();
            // Open the NI-SCOPE instrument handle
            niScope.init("PXI1Slot4", false, false);

            // Configure the acquisition type
            niScope.configureAcquisition(NIScope.VAL_NORMAL);

            // Configure the vertical parameters
            niScope.configureVertical(channelList, 10, 0, NIScope.VAL_DC, 1, true);

            // Configure the channel characteristics
            niScope.configureChanCharacteristics(channelList, NIScope.VAL_1_MEG_OHM, 0);

            // Configure the horizontal parameters
            niScope.configureHorizontalTiming(12800, 1024, 50.0, 1, true);

            niScope.setAttributeViBoolean(channelList, NIScope.ATTR_ENABLE_TIME_INTERLEAVED_SAMPLING, false);

            niScope.configureTriggerImmediate();

            // Initiate the acquisition
            niScope.initiateAcquisition();

            int actualNumWfms = niScope.actualNumWfms(channelList);
            int actualRecordLength = niScope.actualRecordLength();

            // Allocate space for the waveform and waveform info according to the 
            // record length and number of waveforms
            NIScope.WFMInfo wfmInfo[] = new NIScope.WFMInfo[actualNumWfms];
            double waveform[] = new double[actualRecordLength * actualNumWfms];

            // Fetch the data
            niScope.fetch(channelList, 5, actualRecordLength, waveform, wfmInfo);

            double sampleRate = niScope.sampleRate();

            System.out.println("Actual record length: " + actualRecordLength);
            System.out.println("Actual sample rate: " + sampleRate);

            for (int i = 0; i < wfmInfo.length; i++) {
                System.out.println(wfmInfo[i]);
            }
            
            System.out.println(Arrays.toString(Arrays.copyOfRange(waveform, 0, actualRecordLength)));
            System.out.println(Arrays.toString(Arrays.copyOfRange(waveform, actualRecordLength, actualRecordLength * 2)));

        } catch (NIScopeException ex) {
            Logger.getLogger(Test.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            niScope.close();
        }
        niScope = null;
        System.gc();
    }
}
