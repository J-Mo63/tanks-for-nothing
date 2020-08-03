// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


AProjectileBase::AProjectileBase()
{
    PrimaryActorTick.bCanEverTick = false;

    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
    RootComponent = ProjectileMesh;
    ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
    ProjectileMovement->InitialSpeed = ProjectileMovement->MaxSpeed = MovementSpeed;
    InitialLifeSpan = 3.f;

    TrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System"));
    TrailParticle->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
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
        UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());
        UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
        GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HitShake);
        Destroy();
    }
}