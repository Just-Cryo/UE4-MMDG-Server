#pragma once

#include "CoreMinimal.h"
#include "OnlineBeaconHost.h"
#include "PingBeaconHost.generated.h"

class AOnlineBeaconHostObject;

UCLASS(Blueprintable, BlueprintType, transient, notplaceable, config = Engine)
class APingBeaconHost : public AOnlineBeaconHost
{
    GENERATED_UCLASS_BODY()

public:
    /** Blueprint accessor to init the beacon host */
    UFUNCTION(BlueprintCallable, Category = "PingBeaconHost")
        bool Start();

    /** A blueprint helper to add our PingBeaconHostObject */
    UFUNCTION(BlueprintCallable, Category = "PingBeaconHost")
        void AddHost(AOnlineBeaconHostObject* HostObject);

        /** You can also remove a host if you so wish to as well */
        /** You can remove it with: UnregisterHost(const FString& BeaconType) */

protected:
    /** If we successfully started are not */
    bool IsReady;
};