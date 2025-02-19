// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/ButtonWidget.h"

void UButtonWidget::SetText(int value)
{
	if (!Button || !Text) return;

	num = value;
	Text->SetText(FText::FromString("Button: " + FString::FromInt(num)));
	Button->OnClicked.AddDynamic(this, &UButtonWidget::OnButtonClick);
}

void UButtonWidget::OnButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Button Clicked: %d"), num);
}
