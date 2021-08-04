#include "PingBeacon.h"

DEFINE_LOG_CATEGORY(FBeaconLog);

APingBeacon::APingBeacon(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{
}

void APingBeacon::OnFailure()
{
    Super::OnFailure();

    /** This is where you would call the delegate for failure if you had one */
    UE_LOG(FBeaconLog, Log, TEXT("Beacon Connection failure"));
}

/** The rpc client ping implementation */
void APingBeacon::ClientPing_Implementation()
{
    UE_LOG(FBeaconLog, Log, TEXT("Ping RPC Called"));

    //Get our end time in Ticks
    int64 endTime = FDateTime::Now().GetTicks();
    //Find the difference in ticks.
    int64 diff = endTime - startTime;

    //Divide diff by 10,000 to convert to Milliseconds
    //And cast to int32 while we are at
    int32 ms = (int32)diff / 10000;

    //Broadcast the ping complete
    if (OnPingComplete.IsBound()) {
        
        UE_LOG(FBeaconLog, Log, TEXT("BEING BROADCAST"));

        OnPingComplete.Broadcast(GetWorld()->URL.Port);
    }
    else {

        UE_LOG(FBeaconLog, Log, TEXT("NOT BOUND"));
    }

    //For looping simply call Ready() again from right here
    // Ready();
}

/** The rpc client ready implementation */
void APingBeacon::Ready_Implementation()
{
    UE_LOG(FBeaconLog, Log, TEXT("Ready RPC Called"));
    //Set our initial start time in ticks
    startTime = FDateTime::Now().GetTicks();
    //Call server pong rpc
    ServerPong(FString::FromInt(GetWorld()->URL.Port));
}

bool APingBeacon::ServerPong_Validate(const FString& portn)
{
    return true;
}

/** ServerPong rpc implementation **/
void APingBeacon::ServerPong_Implementation(const FString& portn)
{
    UE_LOG(FBeaconLog, Log, TEXT("Pong RPC Called"));
    //Send ping rpc back to client
    ACustomCppGameMode* GM = Cast<ACustomCppGameMode>(GetWorld()->GetAuthGameMode());
    if (IsValid(GM)) {
        GM->FServerPong.Broadcast(FText::FromString("Test:"+ portn));
    }
    ClientPing();
}

/** Our blueprint helper for stuff **/
bool APingBeacon::Start(FString address, int32 port, const bool portOverride)
{
    //Address must be an IP or valid domain name such as epicgames.com or 127.0.0.1
    //Do not include a port in the address! Beacons use a different port then the standard 7777 for connection
    FURL url(nullptr, *address, ETravelType::TRAVEL_Absolute);

    //overriding it with a user specified port?
    if (portOverride)
    {
        url.Port = port;
    }
    //if not overriding just pull the config for it based on the beacon host ListenPort
    else
    {
        int32 portConfig;
        GConfig->GetInt(TEXT("/Script/OnlineSubsystemUtils.OnlineBeaconHost"), TEXT("ListenPort"), portConfig, GEngineIni);
        url.Port = portConfig;
    }

    //Tell our beacon client to begin connection request to server address with our beacon port
    return InitClient(url);
}

/** Our blueprint helper for disconnecting and destroying the beacon */
void APingBeacon::Disconnect()
{
    DestroyBeacon();
}