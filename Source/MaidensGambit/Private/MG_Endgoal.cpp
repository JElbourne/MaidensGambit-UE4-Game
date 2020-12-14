// Fill out your copyright notice in the Description page of Project Settings.


#include "MG_Endgoal.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "MG_Player.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMG_Endgoal::AMG_Endgoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerRoot"));
	SetRootComponent(SceneComp);

	GoalMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EndGoalMesh"));
	GoalMeshComp->SetupAttachment(RootComponent);
	GoalMeshComp->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));
	GoalMeshComp->SetNotifyRigidBodyCollision(true);
	GoalMeshComp->SetGenerateOverlapEvents(true);
	GoalMeshComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	GoalMeshComp->OnComponentBeginOverlap.AddDynamic(this, &AMG_Endgoal::OnActorOverlapBegin);

	PointLightComp = CreateDefaultSubobject<UPointLightComponent>(TEXT("PlayerLight"));
	PointLightComp->SetupAttachment(GoalMeshComp);
	PointLightComp->SetRelativeLocation(FVector(0.f, 0.f, 137.f));
	PointLightComp->SetIntensity(4500);
	PointLightComp->SetLightColor(FColor::Yellow);
	PointLightComp->SetAttenuationRadius(300);
	PointLightComp->SetSourceRadius(20);
	PointLightComp->SetCastShadows(false);

	NextLevel = TEXT("MainLevel");

	static ConstructorHelpers::FObjectFinder<UStaticMesh> GoalMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	if (GoalMeshAsset.Succeeded())
	{
		GoalMeshComp->SetStaticMesh(GoalMeshAsset.Object);
	}
}

// Called when the game starts or when spawned
void AMG_Endgoal::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMG_Endgoal::OnActorOverlapBegin(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMG_Player* Player = Cast<AMG_Player>(OtherActor);
	if (Player != nullptr)
	{
		if (Player->Followers.Num() == Player->FollowersToCollect)
		{
			UGameplayStatics::OpenLevel(this, NextLevel, false);
		}
	}
}

