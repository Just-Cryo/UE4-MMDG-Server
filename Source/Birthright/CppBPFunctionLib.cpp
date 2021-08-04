// Fill out your copyright notice in the Description page of Project Settings.


#include "CppBPFunctionLib.h"
#include "GameFramework/GameModeBase.h"

bool UCppBPFunctionLib::StartGameServer(const FString Process, const FString Params) {
	FPlatformProcess::CreateProc(*Process, *Params, true, false, false, nullptr, 0, nullptr, nullptr);
	//system(TCHAR_TO_ANSI(*In));
	return true;
}



FString UCppBPFunctionLib::GetPortNumber(AGameModeBase* CurrentGameMode)
{
	FString PortNumber;
	PortNumber = FString::FromInt(CurrentGameMode->GetWorld()->URL.Port);
	return PortNumber;
}
void UCppBPFunctionLib::QuitServer()
{
	GIsRequestingExit = true;
}