// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


AProjectileBase::AProjectileBase()
{
    PrimaryActorTick.bCanEverTick = false;

    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
    ProjectileMesh->SetupAttachment(RootComponent);
    ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
    ProjectileMovement->InitialSpeed = ProjectileMovement->MaxSpeed = MovementSpeed;
    InitialLifeSpan = 3.f;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherHitComp,
                            FVector NormalImpulse, const FHitResult& HitResult)
{
    AActor* Owner = GetOwner();
    if (!Owner) { return; }

    if (OtherActor && OtherActor != Owner && OtherActor != this)
    {
        UGameplayStatics::ApplyDamage(OtherActor, Damage, Owner->GetInstigatorController(),
                                      this, DamageType);
    }

    Destroy();
}