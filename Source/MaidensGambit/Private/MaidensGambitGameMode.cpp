// Copyright Epic Games, Inc. All Rights Reserved.

#include "MaidensGambitGameMode.h"
#include "MaidensGambitPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraActor.h"
#include "MG_Player.h"
#include "MG_Enemy.h"
#include "MG_Endgoal.h"
#include "MG_Follower.h"

AMaidensGambitGameMode::AMaidensGambitGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMaidensGambitPlayerController::StaticClass();

	DefaultPawnClass = AMG_Player::StaticClass();
}

void AMaidensGambitGameMode::BeginPlay()
{
	FActorSpawnParameters SpawnParams;
	//GetWorld()->SpawnActor<AMG_Player>(AMG_Player::StaticClass(), FVector(-150.f, -150.f, 0.f), FRotator(0.f, 0.f, 0.f), SpawnParams);
	GetWorld()->SpawnActor<AMG_Enemy>(AMG_Enemy::StaticClass(), FVector(-100.f, 50.f, 0.f), FRotator(0.f, 0.f, 0.f), SpawnParams);

	GetWorld()->SpawnActor<AMG_Endgoal>(AMG_Endgoal::StaticClass(), FVector(-250.f, 250.f, 0.f), FRotator(0.f, 0.f, 0.f), SpawnParams);

	FollowersToCollect = 2;
	GetWorld()->SpawnActor<AMG_Follower>(AMG_Follower::StaticClass(), FVector(250.f, -250.f, 0.f), FRotator(0.f, 0.f, 0.f), SpawnParams);
	GetWorld()->SpawnActor<AMG_Follower>(AMG_Follower::StaticClass(), FVector(250.f, 250.f, 0.f), FRotator(0.f, 0.f, 0.f), SpawnParams);
}
