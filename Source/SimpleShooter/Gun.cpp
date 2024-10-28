// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root; // SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void AGun::PullTrigger()
{
	if(MuzzleFlash)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	}

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr) return;
	AController* OwnerController = OwnerPawn->GetController();
	if(OwnerController == nullptr) return;
	FVector ViewLocation(0.0f);
	FRotator ViewRotation(0.0f);
	OwnerController->GetPlayerViewPoint(ViewLocation, ViewRotation);

	// Rotation.Vector() 하면 해당 회전으로의 방향벡터 얻을 수 있음.
	FVector End = ViewLocation + ViewRotation.Vector() * MaxRange;
	// TODO: LineTrace
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(OwnerPawn);
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, ViewLocation, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
	if(bSuccess == true)
	{
		FVector ShotDirection = -ViewRotation.Vector();	// 총이 발사된 방향으로의 벡터, Vector.Rotation() 하면 해당 벡터의 회전을 얻을 수 있음.
		if(ImpactEffect != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		}
		AActor* HitActor = Hit.GetActor();
		if(HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			Hit.GetActor()->TakeDamage(Damage, DamageEvent, GetOwner()->GetInstigatorController(), GetOwner());
		}
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

