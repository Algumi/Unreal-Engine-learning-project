// Copyright Foamy Sea 2017

#include "EscapeRoom.h"
#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner(); // The door that opens
}

void UOpenDoor::DoorOpen()
{
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}


void UOpenDoor::DoorClose()
{
	Owner->SetActorRotation(FRotator(0.f, 0, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the trigger volume every frame
	if (GetTotalMassOfActorsOnPlate() > 50.f) // TODO make into a parameter
	{
		DoorOpen();
		DoorLastOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - DoorLastOpenTime >= DoorCloseDelay)
	{
		DoorClose();
	}
	
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {

}

