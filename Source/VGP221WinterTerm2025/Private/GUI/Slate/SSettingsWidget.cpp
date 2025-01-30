// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/Slate/SSettingsWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSettingsWidget::Construct(const FArguments& InArgs)
{
	OwningHUD = InArgs._OwningHUD;
	MyInt = InArgs._TestInt;

	const FMargin ContentPadding = FMargin(500.0f, 300.0f);
	const FMargin ButtonPadding = FMargin(10.0f);

	FSlateFontInfo TitleTextStyle = FCoreStyle::Get().GetFontStyle("EmbassedText");
	TitleTextStyle.Size = 60.0f;

	FSlateFontInfo ButtonTextStyle = TitleTextStyle;
	ButtonTextStyle.Size = 40.0f;

	const FText TitleText = FText::FromString("Settings Menu");

	const FText ResumeText = FText::FromString("Resume");
	const FText SettingsText = FText::FromString("Settings");
	const FText QuitText = FText::FromString("Quit");
	
	ChildSlot
	[
		SNew(SOverlay)
		+SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			// Background overlay
			SNew(SImage)
			.ColorAndOpacity(FColor::Black)
		]
		+SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(ContentPadding)
		[
			// Title Text
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Font(TitleTextStyle)
				.Text(TitleText)
				.Justification(ETextJustify::Center)
			]
			+SVerticalBox::Slot()
			.Padding(ButtonPadding)
			[
				// Resume Button
				SNew(SButton)
				.OnClicked(this, &SSettingsWidget::OnResumeClicked)
				[
					SNew(STextBlock)
					.Font(ButtonTextStyle)
					.Text(ResumeText)
					.Justification(ETextJustify::Center)
				]
			]
			+SVerticalBox::Slot()
			.Padding(ButtonPadding)
			[
				// Settings Button
				SNew(SButton)
				.OnClicked(this, &SSettingsWidget::OnSettingsClicked)
				[
					SNew(STextBlock)
					.Font(ButtonTextStyle)
					.Text(SettingsText)
					.Justification(ETextJustify::Center)
				]
			]
			+SVerticalBox::Slot()
			.Padding(ButtonPadding)
			[
				// Quit Button
				SNew(SButton)
				.OnClicked(this, &SSettingsWidget::OnQuitClicked)
				[
					SNew(STextBlock)
					.Font(ButtonTextStyle)
					.Text(QuitText)
					.Justification(ETextJustify::Center)
				]
			]
		]
	];
}
FReply SSettingsWidget::OnResumeClicked() const
{
	if (OwningHUD.IsValid()) {
		OwningHUD->HideSettingsMenu();
	}

	UE_LOG(LogTemp, Warning, TEXT("MyInt: %i"), MyInt);

	return FReply::Handled();
}
FReply SSettingsWidget::OnSettingsClicked() const
{
	UE_LOG(LogTemp, Warning, TEXT("TODO: Spawn Settings if you want"));

	return FReply::Handled();
}
FReply SSettingsWidget::OnQuitClicked() const
{
	if (OwningHUD.IsValid()) {
		if (APlayerController* PC = OwningHUD->PlayerOwner) {
			PC->ConsoleCommand("quit");
		}
	}
	return FReply::Handled();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
