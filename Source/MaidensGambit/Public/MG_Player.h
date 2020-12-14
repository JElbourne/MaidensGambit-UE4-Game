// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MG_Follower.h"
#include "MG_Player.generated.h"

UCLASS()
class MAIDENSGAMBIT_API AMG_Player : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMG_Player();

	UPROPERTY(VisibleAnywhere)
	FVector TargetPosition;

	UPROPERTY(VisibleAnywhere)
	bool bCanMove;

	UPROPERTY()
	FTimerHandle ResetMoveHandle;

	UPROPERTY()
	int FollowersToCollect;

	UPROPERTY()
	TArray<AMG_Follower*> Followers;

private:

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* PlayerMeshComp;

	UPROPERTY(VisibleAnywhere)
	class UPointLightComponent* PointLightComp;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollision;

	UPROPERTY()
	TArray<AActor*> Progressors;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UFUNCTION()
	void OnActorOverlapBegin(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable)
	bool CanMoveAhead(FVector PositionCheck);

	UFUNCTION()
	void SetupMove(FVector NextPosition, FVector CheckPosition);

	UFUNCTION()
	void ResetMove();

	UFUNCTION()
	void MoveUp();

	UFUNCTION()
	void MoveDown();

	UFUNCTION()
	void MoveLeft();

	UFUNCTION()
	void MoveRight();

};
