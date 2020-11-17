// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LSActor.generated.h"

UCLASS()
class LOCALSPACETOUCH_API ALSActor : public AActor
{
	GENERATED_BODY()
	TArray<TEnumAsByte<EObjectTypeQuery> > objts; 
	bool bshouldmove = false;
	FHitResult hitresult;
public:	
	// Sets default values for this actor's properties
	ALSActor();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UMobileTouchActorComponent* mMobileTouchcom;
	UPROPERTY(VisibleDefaultsOnly, Category = ALSActor)
		class UStaticMeshComponent* Localcoord;
	UPROPERTY(VisibleDefaultsOnly, Category = ALSActor)
		class USceneComponent* defaultroot;
	UPROPERTY(VisibleDefaultsOnly, Category = ALSActor)
		class USceneComponent* follower;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = ALSActor)
		class AActor* puppet;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangespeed, float, a);
	UPROPERTY(BlueprintAssignable, Category = ALSActor)
	FOnChangespeed onchangespeedevent;
};
