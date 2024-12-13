//        output socketOut @labels(ITransportPacket/down);

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

#include "FTMReceiverApp.h"
#include "FTMPacket_m.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/Simsignals.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/transportlayer/common/L4PortTag_m.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"
#include "inet/linklayer/ieee80211/mac/Ieee80211Frame_m.h"

namespace inet {

Define_Module(FTMReceiverApp);

void FTMReceiverApp::initialize(int stage)
{
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        // init statistics
        numEchoed = 0;
        WATCH(numEchoed);
    }
}

void FTMReceiverApp::handleMessageWhenUp(cMessage *msg)
{
    socket.processMessage(msg);
}

//clocktime_t FTMReceiverApp::getClockTime()
//{
//    socket.processMessage(msg);
//}

void FTMReceiverApp::socketDataArrived(UdpSocket *socket, Packet *pk)
{
    // determine its source address/port
    L3Address remoteAddress = pk->getTag<L3AddressInd>()->getSrcAddress();
    int srcPort = pk->getTag<L4PortInd>()->getSrcPort();
    pk->clearTags();
    pk->trim();

    // Extract clockTime from the received packet
    const auto& payload = pk->peekAtFront<FTMApplicationPacket>();
    clocktime_t ClockTime1 = payload->getClockTime1();  // Retrieve clock time from sender

    // Get the receiver's current clock time
    clocktime_t ClockTime2 = getClockTime();

    // Calculate clock offset
    clocktime_t clockOffset = ClockTime2 - ClockTime1;

    EV_INFO << "(MESTRE) Received T1: " << ClockTime1 << endl;
    EV_INFO << "(MESTRE) Receiver T2: " << ClockTime2 << endl;
    EV_INFO << "Clock Offset: " << clockOffset << endl;

    //send new packet
    delete pk;
    std::ostringstream str;
    str << "SynResponse" << "-" << numEchoed;
    Packet *packet = new Packet(str.str().c_str());

    const auto& payload2 = makeShared<FTMApplicationPacket>();
    payload2->setSequenceNumber(numEchoed);
    payload2->setChunkLength(B(par("messageLength")));
    payload2->setClockTime1(ClockTime1);
    payload2->setClockTime2(ClockTime2);
    payload2->setClockTime3(getClockTime());


    packet->insertAtBack(payload2);

    // Statistics or further processing
    numEchoed++;
    emit(packetSentSignal, packet);
    socket->sendTo(packet, remoteAddress, srcPort);
}





void FTMReceiverApp::socketErrorArrived(UdpSocket *socket, Indication *indication)
{
    EV_WARN << "Ignoring UDP error report " << indication->getName() << endl;
    delete indication;
}

void FTMReceiverApp::socketClosed(UdpSocket *socket)
{
    if (operationalState == State::STOPPING_OPERATION)
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void FTMReceiverApp::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();

    char buf[40];
    sprintf(buf, "echoed: %d pks", numEchoed);
    getDisplayString().setTagArg("t", 0, buf);
}

void FTMReceiverApp::finish()
{
    ApplicationBase::finish();
}

void FTMReceiverApp::handleStartOperation(LifecycleOperation *operation)
{
    socket.setOutputGate(gate("socketOut"));
    int localPort = par("localPort");
    socket.bind(localPort);
    MulticastGroupList mgl = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this)->collectMulticastGroups();
    socket.joinLocalMulticastGroups(mgl);
    socket.setCallback(this);
}

void FTMReceiverApp::handleStopOperation(LifecycleOperation *operation)
{
    socket.close();
    delayActiveOperationFinish(par("stopOperationTimeout"));
}

void FTMReceiverApp::handleCrashOperation(LifecycleOperation *operation)
{
    if (operation->getRootModule() != getContainingNode(this)) // closes socket when the application crashed only
        socket.destroy(); // TODO  in real operating systems, program crash detected by OS and OS closes sockets of crashed programs.
    socket.setCallback(nullptr);
}

} // namespace inet
