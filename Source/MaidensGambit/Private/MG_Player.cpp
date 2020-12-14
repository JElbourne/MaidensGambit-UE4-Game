// Fill out your copyright notice in the Description page of Project Settings.


#include "MG_Player.h"
#include "Components/PointLightComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MG_Progressor.h"
#include "MaidensGambitPlayerController.h"
#include "MaidensGambitGameMode.h"


// Sets default values
AMG_Player::AMG_Player()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerRoot"));
	SetRootComponent(SceneComp);

	PlayerMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerMeshComp->SetupAttachment(RootComponent);
	PlayerMeshComp->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));
	PlayerMeshComp->SetNotifyRigidBodyCollision(true);
	PlayerMeshComp->SetGenerateOverlapEvents(true);
	PlayerMeshComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	PlayerMeshComp->OnComponentBeginOverlap.AddDynamic(this, &AMG_Player::OnActorOverlapBegin);

	PointLightComp = CreateDefaultSubobject<UPointLightComponent>(TEXT("PlayerLight"));
	PointLightComp->SetupAttachment(PlayerMeshComp);
	PointLightComp->SetRelativeLocation(FVector(0.f, 0.f, 137.f));
	PointLightComp->SetIntensity(4500);
	PointLightComp->SetLightColor(FColor::Green);
	PointLightComp->SetAttenuationRadius(300);
	PointLightComp->SetSourceRadius(20);
	PointLightComp->SetCastShadows(false);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CheckerBox"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetRelativeLocation(FVector(100.f, 0.f, 50.f));
	BoxCollision->SetNotifyRigidBodyCollision(true);
	BoxCollision->SetCollisionProfileName(TEXT("MG_Custom"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlayerMeshAsset(TEXT("StaticMesh'/Game/_MaidensGambit/Models/Player/Player_Cylinder_003.Player_Cylinder_003'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> PlayerMaterialAsset(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Brushed_Nickel.M_Metal_Brushed_Nickel'"));

	if (PlayerMeshAsset.Succeeded())
	{
		PlayerMeshComp->SetStaticMesh(PlayerMeshAsset.Object);
	}

	if (PlayerMaterialAsset.Succeeded()) {
		PlayerMeshComp->SetMaterial(0, PlayerMaterialAsset.Object);
	}

	bCanMove = true;
	TargetPosition = FVector(-150.f,-150.f,0.f);

}

// Called when the game starts or when spawned
void AMG_Player::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
	if (GameMode != nullptr)
	{
		AMaidensGambitGameMode* MG_GameMode = Cast<AMaidensGambitGameMode>(GameMode);
		if (MG_GameMode != nullptr)
		{
			FollowersToCollect = MG_GameMode->FollowersToCollect;
		}
	}

	RootComponent->SetWorldRotation(FRotator(0.f, 0.f, 0.f));
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMG_Progressor::StaticClass(), Progressors);

}

// Called every frame
void AMG_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//RootComponent->MoveComponent(TargetPosition, FQuat(0.f, 0.f, 0.f, 0.f), false);
	
	//FLatentActionInfo LatentInfo;
	//UKismetSystemLibrary::MoveComponentTo(RootComponent, TargetPosition, FRotator(0.f, 0.f, 0.f), false, false, 0.1f, false, EMoveComponentAction::Type::Move, LatentInfo);
	SetActorLocation(FMath::Lerp(GetActorLocation(), TargetPosition, 0.1f));
}

void AMG_Player::OnActorOverlapBegin(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMG_Follower* Follower = Cast<AMG_Follower>(OtherActor);
	if (Follower != nullptr)
	{
		if (!Followers.Contains(Follower))
		{
			if (Followers.Num() > 0)
			{
				AMG_Follower* LastFollower = Followers.Last();
				Follower->SetTargetActor(LastFollower);
			}
			else
			{
				Follower->SetTargetActor(this);
			}

			Followers.Add(Follower);
		}
	}
}

bool AMG_Player::CanMoveAhead(FVector PositionCheck)
{
	BoxCollision->SetRelativeLocation(PositionCheck);

	TArray<AActor*> OverlappingActors;
	BoxCollision->GetOverlappingActors(OverlappingActors);
	
	return (OverlappingActors.Num() == 0);
	//return true;
}

void AMG_Player::SetupMove(FVector NextPosition, FVector CheckPosition)
{
	if (CanMoveAhead(CheckPosition) && bCanMove)
	{
		TargetPosition = NextPosition;
		bCanMove = false;
		GetWorld()->GetTimerManager().SetTimer(ResetMoveHandle, this, &AMG_Player::ResetMove, 0.5f, false, 0.5f);
		if (Progressors.Num() > 0)
		{
			for (AActor* ProgressorActor : Progressors)
			{
				AMG_Progressor* Progressor = Cast<AMG_Progressor>(ProgressorActor);
				if (Progressor != nullptr)
				{
					Progressor->OnProgress();
				}
			}
		}
	}
}

void AMG_Player::ResetMove()
{
	bCanMove = true;
	GetWorld()->GetTimerManager().ClearTimer(ResetMoveHandle);
}

void AMG_Player::MoveUp()
{
	FVector CurrentLocation = GetActorLocation();
	FVector NextPosition = FVector(CurrentLocation.X + 100.f, CurrentLocation.Y, CurrentLocation.Z);
	FVector CheckPosition = FVector(100.f, 0.f, 50.f);
	SetupMove(NextPosition, CheckPosition);
}

void AMG_Player::MoveDown()
{
	FVector CurrentLocation = GetActorLocation();
	FVector NextPosition = FVector(CurrentLocation.X - 100.f, CurrentLocation.Y, CurrentLocation.Z);
	FVector CheckPosition = FVector(-100.f, 0.f, 50.f);
	SetupMove(NextPosition, CheckPosition);
}

void AMG_Player::MoveLeft()
{
	FVector CurrentLocation = GetActorLocation();
	FVector NextPosition = FVector(CurrentLocation.X, CurrentLocation.Y - 100.f, CurrentLocation.Z);
	FVector CheckPosition = FVector(0.f, -100.f, 50.f);
	SetupMove(NextPosition, CheckPosition);
}

void AMG_Player::MoveRight()
{
	FVector CurrentLocation = GetActorLocation();
	FVector NextPosition = FVector(CurrentLocation.X, CurrentLocation.Y + 100.f, CurrentLocation.Z);
	FVector CheckPosition = FVector(0.f, 100.f, 50.f);
	SetupMove(NextPosition, CheckPosition);
}

// Called to bind functionality to input
void AMG_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("MoveUp", IE_Released, this, &AMG_Player::MoveUp);
	PlayerInputComponent->BindAction("MoveDown", IE_Released, this, &AMG_Player::MoveDown);
	PlayerInputComponent->BindAction("MoveLeft", IE_Released, this, &AMG_Player::MoveLeft);
	PlayerInputComponent->BindAction("MoveRight", IE_Released, this, &AMG_Player::MoveRight);
}
