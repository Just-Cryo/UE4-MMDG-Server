// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CustomCppGameMode.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPongEvent, FText, Command);

UCLASS(Blueprintable, BlueprintType, transient, notplaceable)
class BIRTHRIGHT_API ACustomCppGameMode : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	/** Provide a Blueprint binding for the OnClient event */
	UPROPERTY(BlueprintAssignable, Category = "PingBeacon")
		FPongEvent FServerPong;
};
