// Fill out your copyright notice in the Description page of Project Settings.


#include "MG_Follower.h"
#include "Components/PointLightComponent.h"
#include "Materials/Material.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"

AMG_Follower::AMG_Follower()
{
	FollowerMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	SetRootComponent(FollowerMeshComp);

	PointLightComp = CreateDefaultSubobject<UPointLightComponent>(TEXT("FollowerLight"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> FollowerMeshAsset(TEXT("StaticMesh'/Game/_MaidensGambit/Models/Follower/Follower.Follower'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> FollowerMaterialAssetOne(TEXT("Material'/Game/StarterContent/Materials/M_Brick_Clay_New.M_Brick_Clay_New'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> FollowerMaterialAssetTwo(TEXT("Material'/Game/StarterContent/Props/Materials/M_StatueGlass.M_StatueGlass'"));

	FollowerMeshComp->SetNotifyRigidBodyCollision(true);
	FollowerMeshComp->SetGenerateOverlapEvents(true);
	FollowerMeshComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	if (FollowerMeshAsset.Succeeded())
	{
		FollowerMeshComp->SetStaticMesh(FollowerMeshAsset.Object);

		if (PointLightComp != nullptr)
		{
			PointLightComp->SetupAttachment(FollowerMeshComp);
			PointLightComp->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
			PointLightComp->SetIntensity(4500);
			PointLightComp->SetLightColor(FColor::Blue);
			PointLightComp->SetAttenuationRadius(300);
			PointLightComp->SetSourceRadius(20);
			PointLightComp->SetCastShadows(false);
		}
	}

	if (FollowerMaterialAssetOne.Succeeded()) {
		FollowerMeshComp->SetMaterial(0, FollowerMaterialAssetOne.Object);
	}
	if (FollowerMaterialAssetTwo.Succeeded()) {
		FollowerMeshComp->SetMaterial(1, FollowerMaterialAssetTwo.Object);
	}
}

void AMG_Follower::BeginPlay()
{
	Super::BeginPlay();

	TargetPosition = GetActorLocation();
}

void AMG_Follower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanMove)
	{
		SetActorLocation(FMath::Lerp(GetActorLocation(), TargetPosition, 0.1f));
	}
}

void AMG_Follower::OnProgress()
{
	Super::OnProgress();

	if (bCanMove)
	{
		TargetPosition = TargetActor->GetActorLocation();
	}
}

void AMG_Follower::SetTargetActor(class AActor* NewTarget)
{
	TargetActor = NewTarget;
	bCanMove = true;
}
