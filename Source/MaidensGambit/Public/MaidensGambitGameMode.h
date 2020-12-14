// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MaidensGambitGameMode.generated.h"

UCLASS(minimalapi)
class AMaidensGambitGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMaidensGambitGameMode();

	UPROPERTY()
	int FollowersToCollect;

protected:

	virtual void BeginPlay() override;

};



