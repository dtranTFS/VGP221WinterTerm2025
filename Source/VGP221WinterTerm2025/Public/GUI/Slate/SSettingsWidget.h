// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/FPSHUD.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class VGP221WINTERTERM2025_API SSettingsWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSettingsWidget)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class AFPSHUD>, OwningHUD)
	SLATE_ARGUMENT(int, TestInt)
	SLATE_END_ARGS()

	/*
	* unique_ptr = one of kind, can't be copied
	* - Manage reources of class. Variables
	* 
	* shared_ptr = Multipl ownership
	* - If multiple classes are looking at memory, we don't want them to get error or for
	*	the memory to get deleted. Eg. Sharing player health to other classes
	* 
	* weak_ptr = No one owns this pointer
	* - Observer patterns
	* - Helps avoid circular dependicies
	*/

	TWeakObjectPtr<class AFPSHUD> OwningHUD;

	int MyInt;

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FReply OnResumeClicked() const;
	FReply OnSettingsClicked() const;
	FReply OnQuitClicked() const;
};
