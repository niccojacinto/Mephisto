// Fill out your copyright notice in the Description page of Project Settings.

#include "MephistoUE411.h"
#include "MyAnimInstance.h"


UMyAnimInstance::UMyAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Attacking = false;
}