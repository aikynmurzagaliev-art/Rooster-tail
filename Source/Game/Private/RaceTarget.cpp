//Kleith's Game


#include "RaceTarget.h"
#include "Components/SphereComponent.h"
#include "Cat.h"
#include "Kismet/GameplayStatics.h"
#include "ProgressManager.h"


ARaceTarget::ARaceTarget()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(RootComponent);



}

void ARaceTarget::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ARaceTarget::OnOverlapBegin);
	
}

void ARaceTarget::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	ACat* Player = Cast<ACat>(OtherActor);
	if (!Player) return;

	AProgressManager* Manager = Cast<AProgressManager>(
		UGameplayStatics::GetActorOfClass(GetWorld(), AProgressManager::StaticClass())
	);

	if (Manager) {
		Manager->EndRace(true);
	}
}


