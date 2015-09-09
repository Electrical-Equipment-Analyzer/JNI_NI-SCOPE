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
public class Test extends TestCase {

    public Test(String testName) {
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

    // TODO add test methods here. The name must begin with 'test'. For example:
    public void test() {

        NIScope niScope = null;
        try {
            niScope = new NIScope();
            // Open the NI-SCOPE instrument handle
            niScope.init("Dev1", false, false);

            // Call auto setup, finds a signal and configures all necessary parameters
            niScope.autoSetup();

            // Get the actual record length and actual sample rate that will be used
            int actualRecordLength = niScope.actualRecordLength();
            double sampleRate = niScope.sampleRate();

            // Read the data (Initiate the acquisition, and fetch the data)
            double waveform[] = new double[actualRecordLength * 2];
            NIScope.WFMInfo wfmInfo[] = new NIScope.WFMInfo[2];
            niScope.read("0,1", 5, actualRecordLength, waveform, wfmInfo);

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
