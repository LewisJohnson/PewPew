// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EFireModes.generated.h"

UENUM(BlueprintType)
enum class EFireModes : uint8
{
	AUTO_FIRE UMETA(DisplayName = "Auto"),
	BURST_FIRE UMETA(DisplayName = "Burst"),
	SINGLE_FIRE UMETA(DisplayName = "Single Shot")
};