// Fill out your copyright notice in the Description page of Project Settings.


#include "MG_Progressor.h"

// Sets default values
AMG_Progressor::AMG_Progressor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMG_Progressor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMG_Progressor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMG_Progressor::OnProgress()
{

}

