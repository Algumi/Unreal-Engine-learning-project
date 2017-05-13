// Copyright Foamy Sea 2017

#include "EscapeRoom.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();

	SetupInputComponent();
}

// Find attached physics component
void UGrabber::FindPhysicsHandleComponent() 
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{

	}
	else 
	{
		AActor *GrabberOwner = GetOwner();
		UE_LOG(LogTemp, Error, TEXT("HandleComponent is missing for %s "), *(GrabberOwner->GetName()));
	}
}

// Look for attached input component
void UGrabber::SetupInputComponent() {
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Input component is attached!"));
		// Bind the key for grabbing
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else if (!InputComponent)
	{
		AActor *GrabberOwner = GetOwner();
		UE_LOG(LogTemp, Error, TEXT("Input component is missing for %s "), *(GrabberOwner->GetName()));

	}
}



void UGrabber::Grab() 
{
	UE_LOG(LogTemp, Warning, TEXT("Grab key is pressed"));

	/// LINE TRACE and try to reach any actors with physics body collision channel set
	GetFirstPhysicsBodyInReach();

	/// If we hit something than attach a physics handle
		/// TODO attach physics handle
}

void UGrabber::Release() 
{
	UE_LOG(LogTemp, Warning, TEXT("Everything is released"));
	// TODO release physics handle
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if the physics handle is attached
		// move the object we are holding

	
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/// Get player viewpoint every tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	FVector LineTraceEnd = PlayerViewPointLocation +
		PlayerViewPointRotation.Vector() * Reach;

	/// Setup query parametres
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Ray-cast out to reach distance
	FHitResult LineTraceHit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT LineTraceHit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	AActor *ActorHit = LineTraceHit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("You are able to touch %s"), *(ActorHit->GetName()));
	}

	/// See what we hit
	return FHitResult();
}