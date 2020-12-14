// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MG_Endgoal.generated.h"

UCLASS()
class MAIDENSGAMBIT_API AMG_Endgoal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMG_Endgoal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* GoalMeshComp;

	UPROPERTY(VisibleAnywhere)
		class UPointLightComponent* PointLightComp;

	UPROPERTY()
	FName NextLevel;

	UFUNCTION()
	void OnActorOverlapBegin(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
