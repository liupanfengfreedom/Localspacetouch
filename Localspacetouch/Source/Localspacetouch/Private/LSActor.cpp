// Fill out your copyright notice in the Description page of Project Settings.


#include "LSActor.h"
#include "MobileTouchActorComponent.h"
#include "Engine.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
ALSActor::ALSActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//StaticMesh'/Engine/BasicShapes/Plane.Plane'
	static ConstructorHelpers::FObjectFinder<UStaticMesh> planemesh(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	PrimaryActorTick.bCanEverTick = true;
	defaultroot = CreateDefaultSubobject<USceneComponent>(TEXT("defaultroot"));
	defaultroot->SetupAttachment(RootComponent);
	Localcoord = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Localcoord"));
	Localcoord->SetupAttachment(defaultroot);
	Localcoord->SetRelativeLocation(FVector(0));
	Localcoord->SetRelativeRotation(FRotator(0));
	Localcoord->SetAbsolute(false, true, false);
	Localcoord->SetStaticMesh(planemesh.Object);
	Localcoord->SetCollisionProfileName("BlockAll");
	Localcoord->SetCollisionObjectType(ECollisionChannel::ECC_Destructible);
	Localcoord->SetWorldScale3D(FVector(100));
	Localcoord->SetVisibility(false);
	follower = CreateDefaultSubobject<USceneComponent>(TEXT("follower"));
	follower->SetupAttachment(Localcoord);
	follower->SetRelativeLocation(FVector(0));
	follower->SetRelativeRotation(FRotator(0));
}

// Called when the game starts or when spawned
void ALSActor::BeginPlay()
{
	Super::BeginPlay();

	objts.Add(EObjectTypeQuery::ObjectTypeQuery6);
	mMobileTouchcom = NewObject<UMobileTouchActorComponent>();
	mMobileTouchcom->OnTouch1PressedEvent.BindLambda([=](FVector vector) {
		check(puppet);
		bool b = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorForObjects(objts, true, hitresult);
		if (b)
		{
			bshouldmove = true;
			FVector hpr = hitresult.ImpactPoint - GetActorLocation();
			hpr.Z = 0;
			FVector dir = puppet->GetActorForwardVector();
			dir.Z = 0;
			follower->SetRelativeLocation(hpr-(dir*100));
			follower->SetWorldRotation(puppet->GetActorRotation());
		}
	});
	mMobileTouchcom->OnTouch1ReleasedEvent.BindLambda([=](FVector vector) {
		bshouldmove = false;
	});
	mMobileTouchcom->OnFingerTouch1MovedEvent.BindLambda([=](FVector deltaposition) {
		onchangespeedevent.Broadcast(deltaposition.Size());
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(deltaposition.Size()));

	}
	);
}

// Called every frame
void ALSActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bshouldmove)
	{
		bool b = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorForObjects(objts, true, hitresult);
		if (!b)
		{
			return;
		}
		FTransform transform = follower->GetRelativeTransform();
		FVector hpr = hitresult.ImpactPoint - GetActorLocation();
		float dis = FVector::Dist(hpr, transform.GetLocation());
#define keepdis 2
		if (dis > keepdis)
		{
			float factor = UKismetMathLibrary::FClamp(dis - keepdis, 0, 999999);
			FRotator rotator = UKismetMathLibrary::FindLookAtRotation(transform.GetLocation(), hpr);
			FRotator currentrotator = UKismetMathLibrary::RLerp(
				transform.Rotator(),
				rotator,
				0.9f,
				true
			);
			follower->SetRelativeRotation(currentrotator);
			FVector direction = follower->GetForwardVector();
			follower->AddWorldOffset(direction * factor);
			currentrotator.Roll = 0;
			currentrotator.Pitch = 0;
			puppet->SetActorRotation(currentrotator);
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::FromInt(dis));


		}
	}
}

