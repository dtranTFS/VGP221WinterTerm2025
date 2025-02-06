// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/FPSUserWidget.h"

void UFPSUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetHealthBar(1.0f);
	SetText(0);

	if (!ButtonWidgetPrefab) return;

	for (int i = 0; i < 4; i++) {
		// Spawn using a class. Aka, hardcoding
		// UUserWidget* widget = CreateWidget(this, UButtonWidget::StaticClass());
		UUserWidget* widget = CreateWidget(this, ButtonWidgetPrefab);
		ButtonContainer->AddChildToVerticalBox(widget);

		UButtonWidget* button = Cast<UButtonWidget>(widget); // Similar to GetComponent()
		button->SetText(i);
	}
}

void UFPSUserWidget::SetHealthBar(float percentage)
{
	if (!HealthBar) return;

	HealthBar->SetPercent(percentage);
}

void UFPSUserWidget::SetText(int amount)
{
	if (!ScoreText) return;

	UIScore += amount;
	ScoreText->SetText(FText::FromString("Score: " + FString::FromInt(amount)));
}
