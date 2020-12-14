// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MG_Progressor.h"
#include "MG_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class MAIDENSGAMBIT_API AMG_Enemy : public AMG_Progressor
{
	GENERATED_BODY()

public:
	AMG_Enemy();
	
private:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* TrackMeshComp;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* EnemyMeshComp;

	UPROPERTY(VisibleAnywhere)
	class UPointLightComponent* PointLightComp;

	UPROPERTY()
	int MoveTicks;

	UPROPERTY()
	int CurrentMoveTicks;

	UPROPERTY()
	FVector StartPosition;

	UPROPERTY()
	bool MovingForward;

protected:

	virtual void BeginPlay() override;

	virtual void OnProgress() override;

public:

	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void CheckOverlapping(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
