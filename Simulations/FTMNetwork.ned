//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package wifisync.simulations;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.WirelessHost;
import inet.node.wireless.AccessPoint;
import inet.physicallayer.wireless.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import inet.visualizer.contract.IIntegratedVisualizer;


import inet.common.MessageDispatcher;
import inet.common.lifecycle.NodeStatus;
import inet.linklayer.contract.IEthernetInterface;
import inet.linklayer.contract.IMacForwardingTable;
import inet.linklayer.contract.IMacRelayUnit;
import inet.linklayer.contract.IWirelessInterface;
import inet.linklayer.ethernet.contract.IEthernetLayer;
import inet.mobility.contract.IMobility;
import inet.networklayer.common.InterfaceTable;


network FTMNetwork
{
    parameters:
        int numHosts;
    submodules:
        visualizer: <default(firstAvailableOrEmpty("IntegratedCanvasVisualizer"))> like IIntegratedVisualizer if typename != "" {
            parameters:
                @display("p=100,300;is=s");
        }
        configurator: Ipv4NetworkConfigurator {
            parameters:
                @display("p=100,100;is=s");
                config = xml("<config><interface hosts='*' address='145.236.1.x' netmask='255.255.0.0'/></config>");
        }
        radioMedium: Ieee80211ScalarRadioMedium {
            parameters:
                @display("p=100,200;is=s");
        }
        hostMestre: WirelessHost {
            @display("r=,,#707070;p=427,339");
//              wlan[*].mgmt.typename = "Ieee80211MgmtStaSimplified";
//              wlan[*].agent.typename = "";
            wlan[*].mgmt.typename = "Ieee80211MgmtSta";
            wlan[*].agent.typename = "Ieee80211AgentSta";
//            clock.typename = "OscillatorBasedClock";
//            clock.oscillator.typename = default("IdealOscillator");


        }
        host[numHosts]: WirelessHost {
            @display("r=,,#707070");
//              wlan[*].mgmt.typename = "Ieee80211MgmtStaSimplified";
//              wlan[*].agent.typename = "";
            wlan[*].mgmt.typename = "Ieee80211MgmtSta";
            wlan[*].agent.typename = "Ieee80211AgentSta";
//            clock.typename = "OscillatorBasedClock";
//            clock.oscillator.typename = default("RandomDriftOscillator");


        }
        ap: AccessPoint{
            @display("p=277,232;r=,,#707070");
            wlan[*].mgmt.typename = "Ieee80211MgmtAp";
            wlan[*].mac.dcf.channelAccess.pendingQueue.typename = "TimeAwareShaperWifi";
        }
}

