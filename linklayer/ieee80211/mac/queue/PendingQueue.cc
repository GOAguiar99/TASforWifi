//
// Copyright (C) 2016 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


#include "inet/common/packet/Packet.h"
#include "inet/linklayer/ieee80211/mac/Ieee80211Frame_m.h"
#include "inet/queueing/function/PacketClassifierFunction.h"
#include "inet/queueing/function/PacketComparatorFunction.h"

#include "inet/applications/FTM/FTMPacket_m.h"

#include "inet/common/INETDefs.h"
#include "inet/common/packet/Packet.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/networklayer/arp/ipv4/ArpPacket_m.h"

namespace inet {
namespace ieee80211 {

static int compareMgmtOverData(Packet *a, Packet *b)
{
    int aPri = dynamicPtrCast<const Ieee80211MgmtHeader>(a->peekAtFront<Ieee80211MacHeader>()) ? 1 : 0; // TODO there should really exist a high-performance isMgmtFrame() function!
    int bPri = dynamicPtrCast<const Ieee80211MgmtHeader>(b->peekAtFront<Ieee80211MacHeader>()) ? 1 : 0;
    return bPri - aPri;
}

Register_Packet_Comparator_Function(MgmtOverDataComparator, compareMgmtOverData);

static int compareMgmtOverMulticastOverUnicast(Packet *a, Packet *b)
{
    const auto& aHeader = a->peekAtFront<Ieee80211MacHeader>();
    const auto& bHeader = b->peekAtFront<Ieee80211MacHeader>();
    int aPri = dynamicPtrCast<const Ieee80211MgmtHeader>(aHeader) ? 2 : aHeader->getReceiverAddress().isMulticast() ? 1 : 0;
    int bPri = dynamicPtrCast<const Ieee80211MgmtHeader>(bHeader) ? 2 : bHeader->getReceiverAddress().isMulticast() ? 1 : 0;
    return bPri - aPri;
}

Register_Packet_Comparator_Function(MgmtOverMulticastOverUnicastComparator, compareMgmtOverMulticastOverUnicast);

static int classifyMgmtOverData(Packet *packet)
{
    const auto& header = packet->peekAtFront<Ieee80211MacHeader>();
    if (dynamicPtrCast<const Ieee80211MgmtHeader>(header))
        return 0;
    else
        return 1;
}

Register_Packet_Classifier_Function(MgmtOverDataClassifier, classifyMgmtOverData);

static std::map<inet::MacAddress, int> macToQueue = {
    { inet::MacAddress("10:00:00:00:00:01"), 1 },
    { inet::MacAddress("10:00:00:00:00:02"), 2 },
    { inet::MacAddress("10:00:00:00:00:03"), 3 },
    { inet::MacAddress("10:00:00:00:00:04"), 4 },
    { inet::MacAddress("10:00:00:00:00:05"), 5 },
    { inet::MacAddress("10:00:00:00:00:06"), 6 },
    { inet::MacAddress("10:00:00:00:00:07"), 7 },
    { inet::MacAddress("10:00:00:00:00:08"), 8 },
    { inet::MacAddress("10:00:00:00:00:09"), 9 }
};

static int TASClassifier(Packet *packet)
{
    if (!packet->hasAtFront<Ieee80211TwoAddressHeader>()) {
        EV_ERROR << "Invalid packet header." << endl;
        return 0;
    }

    const auto& header = packet->peekAtFront<Ieee80211TwoAddressHeader>();

    // Check if it is a management frame
    if (auto mgmtHeader = dynamicPtrCast<const Ieee80211MgmtHeader>(header)) {
        EV_WARN << "Management frame detected. Assigning to queue 0." << endl;
        return 0;
    }

    std::string packetName = packet->getName();

    if (packetName.find("Sync") != std::string::npos) {
        EV_INFO << "Sync packet detected by name. Assigning to queue 1." << endl;
        return 1; // Assign to queue 1 if it's a Sync packet
    }

    // MAC-based queue assignment
    auto srcMacAddress = header->getTransmitterAddress();
    auto it = macToQueue.find(srcMacAddress);

    if (it != macToQueue.end()) {
        EV_INFO << "Packet from " << srcMacAddress << " assigned to queue " << it->second << "." << endl;
        return it->second;
    } else {
        EV_WARN << "Packet from " << srcMacAddress << " not found in MAC-to-Queue mapping. Assigning to default queue 0." << endl;
        return 0;
    }
}




Register_Packet_Classifier_Function(TASClassifiers, TASClassifier);


static int classifyMgmtOverMulticastOverUnicast(Packet *packet)
{
    const auto& header = packet->peekAtFront<Ieee80211MacHeader>();
    if (dynamicPtrCast<const Ieee80211MgmtHeader>(header))
        return 0;
    else if (header->getReceiverAddress().isMulticast())
        return 1;
    else
        return 2;
}

Register_Packet_Classifier_Function(MgmtOverMulticastOverUnicastClassifier, classifyMgmtOverMulticastOverUnicast);

} /* namespace inet */
} /* namespace ieee80211 */

