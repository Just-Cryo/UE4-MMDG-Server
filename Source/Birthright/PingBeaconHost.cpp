#pragma once

#include "PingBeaconHost.h"
#include "OnlineBeaconHostObject.h"

APingBeaconHost::APingBeaconHost(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{
    //Set the beacon host state to allow requests
    BeaconState = EBeaconState::AllowRequests;
}

bool APingBeaconHost::Start()
{
    //Call our init to start up the network interface
    IsReady = InitHost();
    return IsReady;
}

void APingBeaconHost::AddHost(AOnlineBeaconHostObject* HostObject)
{
    /** Make sure we inited properly */
    if (IsReady)
    {
        RegisterHost(HostObject);
    }
}