// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CppBPFunctionLib.generated.h"

/**
 * 
 */
UCLASS()
class BIRTHRIGHT_API UCppBPFunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable)
		static bool StartGameServer(const FString Process, const FString Params);
	UFUNCTION(BlueprintPure, Category = "Custom", meta = (Keywords = "Port Number"))
		static FString GetPortNumber(AGameModeBase* CurrentGameMode);

	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Quit Server"))
		static void QuitServer();
};
