#pragma once

#include "OnlineBeaconHostObject.h"
#include "CoreMinimal.h"
#include "APingBeaconHostObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClientConnect, APingBeacon*, NewClientActor);

UCLASS(Blueprintable, BlueprintType, transient, notplaceable, config = Engine)
class APingBeaconHostObject : public AOnlineBeaconHostObject
{
    GENERATED_UCLASS_BODY()

        //~ Begin AOnlineBeaconHost Interface
        /** You can do stuff in this one if you want, but we just use the super for this example */
        virtual AOnlineBeaconClient* SpawnBeaconActor(class UNetConnection* ClientConnection) override;
    virtual void OnClientConnected(class AOnlineBeaconClient* NewClientActor, class UNetConnection* ClientConnection) override;
    //~ End AOnlineBeaconHost Interface

    /** In case you ever want to do other things */
    virtual bool Init();

    /**
        Other override functions of the AOnlineBeaconHostObject:

        /**
         * Disconnect a given client from the host
         *
         * param ClientActor the beacon client to disconnect
         */
    virtual void DisconnectClient(AOnlineBeaconClient* ClientActor);

    /**
     * Notification that a client has been disconnected from the host in some way (timeout, client initiated, etc)
     *
     * param LeavingClientActor actor that has disconnected
     */
    virtual void NotifyClientDisconnected(AOnlineBeaconClient* LeavingClientActor);

    /**
     * Called when this class is unregistered by the beacon host
     * Do any necessary cleanup.
     */
    virtual void Unregister();
public:
    /** Provide a Blueprint binding for the OnClient event */
    UPROPERTY(BlueprintAssignable, Category = "PingBeacon")
        FOnClientConnect OnClientJoin;
    
};