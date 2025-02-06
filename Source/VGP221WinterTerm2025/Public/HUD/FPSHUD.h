// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "GUI/Slate/SSettingsWidget.h"
#include "GUI/FPSUserWidget.h"
#include "FPSHUD.generated.h"

/**
 * 
 */
UCLASS()
class VGP221WINTERTERM2025_API AFPSHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	UTexture2D* CrosshairTexture;
	
public:
	virtual void BeginPlay() override;

	// 1. HUD method of making UI
	virtual void DrawHUD() override;

	// 2. Slates method of making UI
	TSharedPtr<class SSettingsWidget> SettingsWidget;
	TSharedPtr<class SWidget> SlateWidgetContainer;

	void ShowSettingsMenu();
	void HideSettingsMenu();

	// 3. UMG method for making UI
	UPROPERTY(EditAnywhere)
	TSubclassOf<UFPSUserWidget> StartingGameWidget;

	UPROPERTY()
	UFPSUserWidget* GameWidgetContainer;

	void ShowGameMenu(TSubclassOf<UFPSUserWidget> newGameWidget);
};
