// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/FPSHUD.h"
#include "Widgets/SWeakWidget.h"

void AFPSHUD::BeginPlay()
{
	Super::BeginPlay();

	ShowGameMenu(StartingGameWidget);
	//ShowSettingsMenu();
}

void AFPSHUD::DrawHUD()
{
	Super::DrawHUD();

	if (!CrosshairTexture) return;

	FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	FVector2D CrosshairHalfSize(CrosshairTexture->GetSurfaceWidth() * 0.5f, CrosshairTexture->GetSurfaceHeight() * 0.5f);
	FVector2D CrosshairDrawPosition(Center.X - CrosshairHalfSize.X, Center.Y - CrosshairHalfSize.Y);

	FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTexture->GetResource(), FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}

void AFPSHUD::ShowSettingsMenu()
{
	SettingsWidget = SNew(SSettingsWidget).OwningHUD(this).TestInt(10);
	GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(SlateWidgetContainer, SWeakWidget).PossiblyNullContent(SettingsWidget.ToSharedRef()));

	PlayerOwner->bShowMouseCursor = true;
	PlayerOwner->SetInputMode(FInputModeUIOnly());
}

void AFPSHUD::HideSettingsMenu()
{
	GEngine->GameViewport->RemoveViewportWidgetContent(SlateWidgetContainer.ToSharedRef());

	PlayerOwner->bShowMouseCursor = false;
	PlayerOwner->SetInputMode(FInputModeGameOnly());
}

void AFPSHUD::ShowGameMenu(TSubclassOf<UFPSUserWidget> newGameWidget)
{
	// Check if a game menu has spawn RemoveFromParent
	if (GameWidgetContainer) {
		GameWidgetContainer->RemoveFromParent();
		GameWidgetContainer = nullptr;
	}

	// Spawn a newGameWidget and AddToViewport
	GameWidgetContainer = CreateWidget<UFPSUserWidget>(GetWorld(), newGameWidget);
	GameWidgetContainer->AddToViewport();
}
