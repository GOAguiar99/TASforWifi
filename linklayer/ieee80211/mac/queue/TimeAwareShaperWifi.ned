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

package inet.linklayer.ieee80211.mac.queue;



import inet.queueing.classifier.PacketClassifier;
import inet.queueing.queue.CompoundPacketQueueBase;
import inet.queueing.queue.PacketQueue;
import inet.queueing.scheduler.PriorityScheduler;
import inet.queueing.contract.IPacketGate;
import ned.IdealChannel;


module TimeAwareShaperWifi extends CompoundPacketQueueBase
{
    parameters:
        packetCapacity = default(-1); // -1 means unlimited
        int NumNodes = default(9); // number of nodes

    submodules:
        TASclassifier: PacketClassifier {
            parameters:
                classifierClass = default("inet::ieee80211::TASClassifiers"); // MgmtOverDataClassifier, MgmtOverMulticastOverUnicastClassifier, ...
                @display("p=100,200");
        }
        managementQueue: PacketQueue {
            parameters:
                @display("p=383,137");
        }
        queue[NumNodes]: PacketQueue {
            @display("p=400,300,column,50"); // Coluna de queues, espaçamento de 50
        }
        mgmtgate: <default("PeriodicGate")> like IPacketGate {
            parameters:
                @display("p=686,137");
        }
        hostsgates[NumNodes]: <default("TASGate")> like IPacketGate {
            @display("p=600,300,column,50"); // Coluna de gates ao lado das queues
        }
        prioritizer: PriorityScheduler {
            parameters:
                reverseOrder = default(true);
                @display("p=969,200");
        }
    connections:
        in --> TASclassifier.in;
        TASclassifier.out++ --> managementQueue.in;
        managementQueue.out --> mgmtgate.in;
        mgmtgate.out --> prioritizer.in++;


        for i=0..NumNodes - 1 {
            TASclassifier.out++ --> queue[i].in;
            queue[i].out --> hostsgates[i].in;
            hostsgates[i].out --> prioritizer.in++;
        }


        prioritizer.out --> out;
}
