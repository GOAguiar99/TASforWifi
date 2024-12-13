//
// Copyright (C) 2020 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


#ifndef __INET_TASGate_H
#define __INET_TASGate_H

#include "inet/common/clock/ClockUserModuleMixin.h"
#include "inet/queueing/base/PacketGateBase.h"

namespace inet {

extern template class ClockUserModuleMixin<queueing::PacketGateBase>;

namespace queueing {

class INET_API TASGate : public ClockUserModuleMixin<PacketGateBase>
{
  public:
    static simsignal_t guardBandStateChangedSignal;

  protected:
    //Novos parametros
    int numHosts;
    int hostOrder; //Ordem de abertura
    clocktime_t openDuration; // Duração aberto
    clocktime_t period; // Periodo

    int index = 0;
    bool initiallyOpen = false;
    clocktime_t initialOffset;
    clocktime_t offset;
    clocktime_t totalDuration = 0;
    bool scheduleForAbsoluteTime = false;
    bool enableImplicitGuardBand = true;
    int openSchedulingPriority = 0;
    int closeSchedulingPriority = 0;
    bool isInGuardBand_ = false;
    int periodCounter_ = 0;


    ClockEvent *changeTimer = nullptr;

  protected:
    virtual void initialize(int stage) override;
    virtual void finish() override;
    virtual void handleMessage(cMessage *message) override;
    virtual void handleParameterChange(const char *name) override;
    virtual bool canPacketFlowThrough(Packet *packet) const override;

    virtual void initializeGating();
    virtual void scheduleChangeTimer();
    virtual void processChangeTimer();

    virtual void updateIsInGuardBand();

  public:
    virtual ~TASGate() { cancelAndDelete(changeTimer); }

    virtual clocktime_t getInitialOffset() const { return initialOffset; }
    virtual bool getInitiallyOpen() const { return initiallyOpen; }

    virtual bool isInGuardBand() const { return isInGuardBand_; }

    virtual void open() override;
    virtual void close() override;

    virtual void handleCanPushPacketChanged(cGate *gate) override;
    virtual void handleCanPullPacketChanged(cGate *gate) override;
};

} // namespace queueing
} // namespace inet

#endif

