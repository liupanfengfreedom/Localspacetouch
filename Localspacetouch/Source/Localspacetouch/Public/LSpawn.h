// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LSpawn.generated.h"

UCLASS()
class LOCALSPACETOUCH_API ALSpawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALSpawn();
	UPROPERTY(VisibleDefaultsOnly, Category = ALSActor)
		class USceneComponent* defaultroot;
	UPROPERTY(VisibleDefaultsOnly, Category = ALSActor)
		class UChildActorComponent* mLocalspacejoystick;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UMobileTouchActorComponent* mMobileTouchcom;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
