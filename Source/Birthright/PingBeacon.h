#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "OnlineBeaconClient.h"
#include "CustomCppGameMode.h"
#include "PingBeacon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeaconPingComplete, int32, TimeMS);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FServerPongEvent, FText, command);

DECLARE_LOG_CATEGORY_EXTERN(FBeaconLog, Log, All);

/**
 * Simple ping client beacon class
 */
 /** the config = engine is for if you want to use config based properties. Engine = Engine.ini */
UCLASS(Blueprintable, BlueprintType, transient, notplaceable, config = Engine)
class APingBeacon : public AOnlineBeaconClient
{    
    GENERATED_UCLASS_BODY()


    //~ Begin AOnlineBeaconClient Interface
    virtual void OnFailure() override;
    //~ End AOnlineBeaconClient Interface



    /** Send a ping RPC to the client */
    UFUNCTION(client, reliable)
    virtual void ClientPing();

    /** Let's us know the beacon is ready so we can prep the initial start time for ping round trip */
    UFUNCTION(client, reliable)
    virtual void Ready();

    /** Send a pong RPC to the host */
    UFUNCTION(server, reliable, WithValidation)
    virtual void ServerPong(const FString& portn);

    /** Provide Blueprint Access to Start the Beacon*/
    UFUNCTION(BlueprintCallable, Category = "PingBeacon")
    bool Start(FString address, int32 port, const bool portOverride);

    /** Provide Blueprint access to disconnect and destroy the client beacon */
    UFUNCTION(BlueprintCallable, Category = "PingBeacon")
    void Disconnect();

public:
    /** Provide a Blueprint binding for the OnPingComplete event */
    UPROPERTY(BlueprintAssignable, Category = "PingBeacon")
    FOnBeaconPingComplete OnPingComplete;

    UPROPERTY(BlueprintAssignable, Category = "PingBeacon")
        FServerPongEvent OnServerPong;



    /** Need to add one also for a failure. That is up to you though! */

protected:
    /** Holds our initial start time in Ticks from FDateTime.Now().GetTicks() */
    int64 startTime;
};