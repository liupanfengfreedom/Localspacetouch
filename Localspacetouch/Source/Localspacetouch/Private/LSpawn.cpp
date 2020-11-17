// Fill out your copyright notice in the Description page of Project Settings.


#include "LSpawn.h"
#include "MobileTouchActorComponent.h"
#include "Engine.h"
#include "Components/ChildActorComponent.h"
#include "LSActor.h"

// Sets default values
ALSpawn::ALSpawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	defaultroot = CreateDefaultSubobject<USceneComponent>(TEXT("defaultroot"));
	defaultroot->SetupAttachment(RootComponent);
	mLocalspacejoystick = CreateDefaultSubobject<UChildActorComponent>(TEXT("mLocalspacejoystick"));
	mLocalspacejoystick->SetupAttachment(defaultroot);
	mLocalspacejoystick->SetRelativeLocation(FVector(0));
	mLocalspacejoystick->SetRelativeRotation(FRotator(0));
	mLocalspacejoystick->SetChildActorClass(ALSActor::StaticClass());
}

// Called when the game starts or when spawned
void ALSpawn::BeginPlay()
{
	Super::BeginPlay();
	ALSActor *lsa = Cast<ALSActor>(mLocalspacejoystick->GetChildActor());
	lsa->puppet = this;
	mMobileTouchcom = lsa->mMobileTouchcom;
}

// Called every frame
void ALSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorWorldOffset(GetActorForwardVector()*1.5f);
}

// Called to bind functionality to input
void ALSpawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

