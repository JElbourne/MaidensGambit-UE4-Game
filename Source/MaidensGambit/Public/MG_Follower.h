// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MG_Progressor.h"
#include "MG_Follower.generated.h"

/**
 * 
 */
UCLASS()
class MAIDENSGAMBIT_API AMG_Follower : public AMG_Progressor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMG_Follower();

	UPROPERTY(EditAnywhere)
		class UStaticMesh* FollowerStaticMesh;

private:

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* FollowerMeshComp;

	UPROPERTY(VisibleAnywhere)
		class UPointLightComponent* PointLightComp;

	UPROPERTY()
		bool bCanMove;

	UPROPERTY()
		FVector TargetPosition;

	UPROPERTY()
		class AActor* TargetActor;

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	virtual void OnProgress() override;

	UFUNCTION()
	void SetTargetActor(class AActor* NewTarget);
};
