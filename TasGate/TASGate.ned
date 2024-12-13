//
// Copyright (C) 2020 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


package inet.queueing.gate;

import inet.queueing.base.PacketGateBase;
import inet.queueing.contract.IPacketGate;

//
// This module allows or forbids packets to pass through depending on whether
// the gate is open or closed. The gate is open and closed according to the list
// of change times periodically.
//
simple TASGate extends PacketGateBase like IPacketGate
{
    parameters:
        int numHosts;
        int hostOrder;
        double openDuration @unit(s) = default(0.1s); // Duracao aberto
        double period @unit(s) = default(0.1s); // Duracao aberto

        string clockModule = default("");
        bool initiallyOpen @mutable = default(true);
        double offset @unit(s) = default(0s);
        bool scheduleForAbsoluteTime = default(true);
        int openSchedulingPriority = default(0);
        int closeSchedulingPriority = default(0);
        bool enableImplicitGuardBand = default(true);

        @class(TASGate);
        @signal[guardBandStateChanged](type=bool);
        @statistic[guardBandState](title="guard band state"; type=enum; enum=ON, OFF; source=guardBandStateChanged; record=vector; interpolationmode=sample-hold);
}

