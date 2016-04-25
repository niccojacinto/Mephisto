// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class MEPHISTOUE411_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackBools)
	bool Attacking;

	UMyAnimInstance(const FObjectInitializer& ObjectInitializer);
};
