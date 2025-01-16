// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/FPSProjectGameMode.h"

void AFPSProjectGameMode::StartPlay()
{
    Super::StartPlay();

    // 1. To print to screen
    check(GEngine != nullptr);
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameModeBase!"));

    // 2. To print to console
    // UE_LOG(LogTemp, Warning, TEXT("Hello World, this is FPSGameModeBase!"));

    // 3. To print values
    // FString Name("TestName");
    // int TestNumber = 10;
    // bool BoolTest = true;
    // UE_LOG(LogTemp, Warning, TEXT("TestNumber: %i, TestString: %s, BoolTest: %d, TEXTTest: %s, ActorName: %s"), TestNumber, *Name, BoolTest, TEXT("This is a text"), *GetName());

    // 4. Modern way of printing
    // UE_LOGFMT(LogTemp, Warning, "TestNumber: {0}, TestString: {1}, BoolTest: {2}", TestNumber, Name, BoolTest);
}
