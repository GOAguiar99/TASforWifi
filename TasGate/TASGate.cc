//
// Copyright (C) 2020 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#include "inet/queueing/gate/TASGate.h"
#include "inet/common/ModuleAccess.h"

namespace inet {
namespace queueing {

Define_Module(TASGate);

simsignal_t TASGate::guardBandStateChangedSignal = registerSignal("guardBandStateChanged");

void TASGate::initialize(int stage)
{
    ClockUserModuleMixin::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        initiallyOpen = par("initiallyOpen");
        initialOffset = par("offset");
        numHosts = par("numHosts");
        hostOrder = par("hostOrder");
        openDuration = par("openDuration");
        period = par("period");

        scheduleForAbsoluteTime = par("scheduleForAbsoluteTime");
        changeTimer = new ClockEvent("ChangeTimer");
        enableImplicitGuardBand = par("enableImplicitGuardBand");
        openSchedulingPriority = par("openSchedulingPriority");
        closeSchedulingPriority = par("closeSchedulingPriority");
        WATCH(isInGuardBand_);
    }
    else if (stage == INITSTAGE_QUEUEING)
        initializeGating();
    else if (stage == INITSTAGE_LAST)
        emit(guardBandStateChangedSignal, isInGuardBand_);
}

void TASGate::finish()
{
    emit(guardBandStateChangedSignal, isInGuardBand_);
}

void TASGate::handleParameterChange(const char *name)
{
    if (!strcmp(name, "offset"))
        initialOffset = par("offset");
    else if (!strcmp(name, "initiallyOpen"))
        initiallyOpen = par("initiallyOpen");
    else if (!strcmp(name, "numHosts"))
        numHosts = par("numHosts");
    else if (!strcmp(name, "hostOrder"))
        hostOrder = par("hostOrder");
    else if (!strcmp(name, "openDuration"))
        openDuration = par("openDuration");
    else if (!strcmp(name, "period"))
        period = par("period");

    initializeGating();
}

void TASGate::handleMessage(cMessage *message)
{
    if (message == changeTimer) {
        processChangeTimer();
        scheduleChangeTimer();
    }
    else
        throw cRuntimeError("Unknown message");
}

void TASGate::open()
{
    PacketGateBase::open();
    updateIsInGuardBand();
}

void TASGate::close()
{
    PacketGateBase::close();
    updateIsInGuardBand();
}

void TASGate::initializeGating()
{
    index = 0;
    isOpen_ = initiallyOpen;
    periodCounter_ = 0;

    EV_WARN << "############################## INICIANDO GATING ##############################" << EV_ENDL;

    // Handle special case: hostOrder = 0 means gate should remain open forever
    if (hostOrder == 0) {
        isOpen_ = true;
        EV_WARN << "################## Gate set to always open ##################" << EV_ENDL;
        return;
    }

    // Calculate offset for staggered opening
    offset = (hostOrder - 1) * openDuration;

    if (changeTimer->isScheduled())
        cancelClockEvent(changeTimer);

    EV_WARN << "############################## OFFSET = " << offset << " ##############################" << EV_ENDL;
    EV_WARN << "############################## Finalizando GATING ##############################" << EV_ENDL;

    scheduleChangeTimer();
}


void TASGate::scheduleChangeTimer()
{
    EV_WARN << "############################## INICIANDO SCHEDULER ##############################" << EV_ENDL;

    clocktime_t scheduleTime;
    if (isOpen_)
        scheduleTime = openDuration;
    else{
        if(periodCounter_ < 1){
            scheduleTime = openDuration * (hostOrder - 1);
        }
        else if(periodCounter_ > 0){
            scheduleTime = period - openDuration;

        }}

    EV_WARN << "############################## Calculando scheduleTime ##############################" << EV_ENDL;
    EV_WARN << "isOpen_: " << isOpen_ << ", openDuration: " << openDuration << ", period: " << period << ", numHosts: " << numHosts << ", hostOrder: " << hostOrder << EV_ENDL;
    EV_WARN << "scheduleTime: " << scheduleTime << EV_ENDL;
    EV_WARN << "Current Clock Time: " << getClockTime() << EV_ENDL;

    changeTimer->setSchedulingPriority(isOpen_ ? closeSchedulingPriority : openSchedulingPriority);

    if (scheduleForAbsoluteTime) {
        clocktime_t absoluteTime = getClockTime() + scheduleTime;
        EV_WARN << "Scheduling event at absolute time: " << absoluteTime << EV_ENDL;
        scheduleClockEventAt(absoluteTime, changeTimer);
    } else {
        EV_WARN << "Scheduling event after: " << scheduleTime << EV_ENDL;
        scheduleClockEventAfter(scheduleTime, changeTimer);
    }

    EV_WARN << "############################## FINALIZANDO SCHEDULER ##############################" << EV_ENDL;
}





void TASGate::processChangeTimer()
{
    EV_INFO << "Processing change timer. Current periodCounter_: " << periodCounter_ << EV_ENDL;
    if (isOpen_)
        close();
    else
        open();

    // Increment the period counter after each cycle
    periodCounter_++;
    EV_INFO << "After processing change timer, periodCounter_ incremented to " << periodCounter_ << EV_ENDL;
}

bool TASGate::canPacketFlowThrough(Packet *packet) const
{
    ASSERT(isOpen_);
    if (std::isnan(bitrate.get()))
        return PacketGateBase::canPacketFlowThrough(packet);
    else if (packet == nullptr)
        return false;
    else {
        if (enableImplicitGuardBand) {
            clocktime_t flowEndTime = getClockTime() + s((packet->getDataLength() + extraLength) / bitrate).get() + SIMTIME_AS_CLOCKTIME(extraDuration);
            return !changeTimer->isScheduled() || flowEndTime <= getArrivalClockTime(changeTimer);
        }
        else
            return PacketGateBase::canPacketFlowThrough(packet);
    }
}

void TASGate::updateIsInGuardBand()
{
    bool newIsInGuardBand = false;
    if (isOpen_) {
        auto packet = provider != nullptr ? provider->canPullPacket(inputGate->getPathStartGate()) : nullptr;
        newIsInGuardBand = packet != nullptr && !canPacketFlowThrough(packet);
    }
    if (isInGuardBand_ != newIsInGuardBand) {
        isInGuardBand_ = newIsInGuardBand;
        EV_INFO << "Changing guard band state" << EV_FIELD(isInGuardBand_) << EV_ENDL;
        emit(guardBandStateChangedSignal, isInGuardBand_);
    }
}

void TASGate::handleCanPushPacketChanged(cGate *gate)
{
    PacketGateBase::handleCanPushPacketChanged(gate);
    updateIsInGuardBand();
}

void TASGate::handleCanPullPacketChanged(cGate *gate)
{
    PacketGateBase::handleCanPullPacketChanged(gate);
    updateIsInGuardBand();
}

} // namespace queueing
} // namespace inet
