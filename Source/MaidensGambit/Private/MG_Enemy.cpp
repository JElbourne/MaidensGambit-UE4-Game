// Fill out your copyright notice in the Description page of Project Settings.


#include "MG_Enemy.h"
#include "Components/PointLightComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"

AMG_Enemy::AMG_Enemy()
{
	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("EnemyRoot"));
	SetRootComponent(SceneComp);

	TrackMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrackMesh"));
	TrackMeshComp->SetupAttachment(RootComponent);
	TrackMeshComp->SetWorldScale3D(FVector(5.0f, 0.1f, 0.05f));
	TrackMeshComp->SetRelativeLocation(FVector(250.f, 0.f, 0.f));
	
	EnemyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
	EnemyMeshComp->SetupAttachment(RootComponent);
	EnemyMeshComp->SetRelativeLocation(FVector(50.f, 0.f, 10.f));
	EnemyMeshComp->SetGenerateOverlapEvents(true);
	EnemyMeshComp->OnComponentBeginOverlap.AddDynamic(this, &AMG_Enemy::CheckOverlapping);

	PointLightComp = CreateDefaultSubobject<UPointLightComponent>(TEXT("EnemyLight"));
	PointLightComp->SetupAttachment(EnemyMeshComp);
	PointLightComp->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	PointLightComp->SetIntensity(4500);
	PointLightComp->SetLightColor(FColor::Orange);
	PointLightComp->SetAttenuationRadius(300);
	PointLightComp->SetSourceRadius(20);
	PointLightComp->SetCastShadows(false);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> TrackMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> EnemyMeshAsset(TEXT("StaticMesh'/Game/_MaidensGambit/Models/Blade/Blade.Blade'"));

	if (TrackMeshAsset.Succeeded())
	{
		TrackMeshComp->SetStaticMesh(TrackMeshAsset.Object);
	}

	if (EnemyMeshAsset.Succeeded())
	{
		EnemyMeshComp->SetStaticMesh(EnemyMeshAsset.Object);
	}


	MoveTicks = 4;
}

void AMG_Enemy::BeginPlay()
{
	Super::BeginPlay();

	StartPosition = EnemyMeshComp->GetRelativeLocation();
}

void AMG_Enemy::OnProgress()
{
	if (MovingForward)
	{
		if (CurrentMoveTicks == MoveTicks)
		{
			MovingForward = false;
			CurrentMoveTicks--;
		}
		else
		{
			CurrentMoveTicks++;
		}
	}
	else
	{
		if (CurrentMoveTicks == 0)
		{
			MovingForward = true;
			CurrentMoveTicks++;
		}
		else
		{
			CurrentMoveTicks--;
		}
	}
}

void AMG_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector ModifiedForwardVector = GetActorForwardVector() * (CurrentMoveTicks * 100);
	FVector TargetLocation = StartPosition + ModifiedForwardVector;
	EnemyMeshComp->SetRelativeLocation(FMath::Lerp(EnemyMeshComp->GetRelativeLocation(), TargetLocation, 0.1f));
}

void AMG_Enemy::CheckOverlapping(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

