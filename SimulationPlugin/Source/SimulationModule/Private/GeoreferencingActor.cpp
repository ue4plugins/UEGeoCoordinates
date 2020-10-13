// Fill out your copyright notice in the Description page of Project Settings.


#include "GeoreferencingActor.h"
#include "GeoReferencingSubsystem.h"

// Sets default values
AGeoreferencingActor::AGeoreferencingActor()
{
 	PrimaryActorTick.bCanEverTick = false;
}

void AGeoreferencingActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	this->GeoReferencingSubsystem = GetWorld()->GetSubsystem<UGeoReferencingSubsystem>();
	if (GeoReferencingSubsystem != NULL)
	{
		GeoReferencingSubsystem->RegisterGeoReferencingActor(this);
	}
}

void AGeoreferencingActor::Destroyed()
{
	this->GeoReferencingSubsystem = GetWorld()->GetSubsystem<UGeoReferencingSubsystem>();
	if (GeoReferencingSubsystem != NULL)
	{
		GeoReferencingSubsystem->UnregisterGeoReferencingActor();
	}
	Super::Destroyed();
}

#if WITH_EDITOR
void AGeoreferencingActor::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	//Get the name of the property that was changed  
	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (GeoReferencingSubsystem != NULL)
	{
		if (PropertyName == GET_MEMBER_NAME_CHECKED(AGeoreferencingActor, ProjectedCRS))
		{
			GeoReferencingSubsystem->SetProjectedCRS(ProjectedCRS);
		}
		if (PropertyName == GET_MEMBER_NAME_CHECKED(AGeoreferencingActor, GeographicCRS))
		{
			GeoReferencingSubsystem->SetGeographicCRS(GeographicCRS);
		}
		if (PropertyName == GET_MEMBER_NAME_CHECKED(AGeoreferencingActor, OriginProjectedCoordinates_X) ||
			PropertyName == GET_MEMBER_NAME_CHECKED(AGeoreferencingActor, OriginProjectedCoordinates_Y) ||
			PropertyName == GET_MEMBER_NAME_CHECKED(AGeoreferencingActor, OriginProjectedCoordinates_Z))
		{
			GeoReferencingSubsystem->SetOriginProjectedCoordinates(OriginProjectedCoordinates_X, OriginProjectedCoordinates_Y, OriginProjectedCoordinates_Z);
		}
	}

	// Call the base class version  
	Super::PostEditChangeProperty(PropertyChangedEvent);
}


#endif