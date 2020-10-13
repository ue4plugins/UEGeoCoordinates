// Fill out your copyright notice in the Description page of Project Settings.


#include "SimulationSettings.h"
#include "GeoReferencingSubsystem.h"

#if WITH_EDITOR

void USimulationSettings::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	//Get the name of the property that was changed  
	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (GeoReferencingSubsystem != NULL)
	{
		if (PropertyName == GET_MEMBER_NAME_CHECKED(USimulationSettings, ProjectedCRS))
		{
			GeoReferencingSubsystem->SetProjectedCRS(ProjectedCRS);
		}
		if (PropertyName == GET_MEMBER_NAME_CHECKED(USimulationSettings, GeographicCRS))
		{
			GeoReferencingSubsystem->SetGeographicCRS(GeographicCRS);
		}
		if (PropertyName == GET_MEMBER_NAME_CHECKED(USimulationSettings, OriginProjectedCoordinates_X) ||
			PropertyName == GET_MEMBER_NAME_CHECKED(USimulationSettings, OriginProjectedCoordinates_Y) ||
			PropertyName == GET_MEMBER_NAME_CHECKED(USimulationSettings, OriginProjectedCoordinates_Z) )
		{
			GeoReferencingSubsystem->SetOriginProjectedCoordinates(OriginProjectedCoordinates_X, OriginProjectedCoordinates_Y, OriginProjectedCoordinates_Z);
		}
	}
	
	// Call the base class version  
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

#endif