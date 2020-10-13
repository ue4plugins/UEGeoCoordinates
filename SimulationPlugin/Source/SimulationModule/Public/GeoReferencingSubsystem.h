// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "proj.h"
#include "GeographicCoordinates.h"
#include "LargeCoordinates.h"
#include "GeoReferencingSubsystem.generated.h"

class AGeoreferencingActor;
/**
 *
 */
UCLASS()
class SIMULATIONMODULE_API UGeoReferencingSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	// Initializations
	UGeoReferencingSubsystem();

	/**
	 * Subsystem Init - Init PROJ and it data path
	 * @param Collection 
	*/
	void Initialize(FSubsystemCollectionBase& Collection) override;
	void Deinitialize() override;

	void RegisterGeoReferencingActor(AGeoreferencingActor* GeoActor);
	void UnregisterGeoReferencingActor();


// Settings

	/**
	 * Set the Projected CRS definition. Can be a EPSG:CODE, a WKT or a named CRS 
	*/
	UFUNCTION(BlueprintCallable, Category = "Simulation|Coordinates")
		bool SetProjectedCRS(FString InProjectedCRS);

	/**
	 * Set the Geographic CRS definition. Can be a EPSG:CODE, a WKT or a named CRS as "WGS84"
	*/
	UFUNCTION(BlueprintCallable, Category = "Simulation|Coordinates")
		bool SetGeographicCRS(FString InGeographicCRS);

	/**
	 * Set the Origin - Enter here the Coordinates of the point corresponding to UE Origin in Projected CRS - AKA Translation vector. 
	*/
	UFUNCTION(BlueprintCallable, Category = "Simulation|Coordinates")
		bool SetOriginProjectedCoordinates(int32 InX, int32 InY, int32 InZ);

// Engine <--> Projected (Translation offset)

	/**
	 * Convert a Vector expressed in ENGINE space to the PROJECTED CRS  
	*/
	UFUNCTION(BlueprintCallable, Category = "Simulation|Coordinates")
		void EngineToProjected(FVector EngineCoordinates, FLargeCoordinates& ProjectedCoordinates);

	/**
	 * Convert a Vector expressed in PROJECTED CRS to ENGINE space
	*/
	UFUNCTION(BlueprintCallable, Category = "Simulation|Coordinates")
		void ProjectedToEngine(FLargeCoordinates ProjectedCoordinates, FVector& EngineCoordinates);


// Projected <--> Geographic <--> Geocentric (Projection)

	/**
	 * Convert a Coordinate expressed in PROJECTED CRS to GEOGRAPHIC CRS
	*/
	UFUNCTION(BlueprintCallable, Category = "Simulation|Coordinates")
		void ProjectedToGeographic(FLargeCoordinates ProjectedCoordinates, FGeographicCoordinates& GeographicCoordinates);

	/**
	 * Convert a Coordinate expressed in PROJECTED CRS to GEOCENTRIC CRS
	*/
	UFUNCTION(BlueprintCallable, Category = "Simulation|Coordinates")
		void ProjectedToGeocentric(FLargeCoordinates ProjectedCoordinates, FLargeCoordinates& GeocentricCoordinates);

	/**
	 * Convert a Coordinate expressed in GEOGRAPHIC CRS to PROJECTED CRS
	*/
	UFUNCTION(BlueprintCallable, Category = "Simulation|Coordinates")
		void GeographicToProjected(FGeographicCoordinates GeographicCoordinates, FLargeCoordinates& ProjectedCoordinates);

	/**
	 * Convert a Coordinate expressed in GEOGRAPHIC CRS to GEOCENTRIC CRS
	*/
	UFUNCTION(BlueprintCallable, Category = "Simulation|Coordinates")
		void GeographicToGeocentric(FGeographicCoordinates GeographicCoordinates, FLargeCoordinates& GeocentricCoordinates);

	/**
	 * Convert a Coordinate expressed in GEOCENTRIC CRS to PROJECTED CRS
	*/
	UFUNCTION(BlueprintCallable, Category = "Simulation|Coordinates")
		void GeocentricToProjected(FLargeCoordinates GeocentricCoordinates, FLargeCoordinates& ProjectedCoordinates);

	/**
	 * Convert a Coordinate expressed in GEOCENTRIC CRS to GEOGRAPHIC CRS
	*/
	UFUNCTION(BlueprintCallable, Category = "Simulation|Coordinates")
		void GeocentricToGeographic(FLargeCoordinates GeocentricCoordinates, FGeographicCoordinates& GeographicCoordinates);

	/**
	 * Check if the string corresponds to a valid CRS descriptor
	*/
	UFUNCTION(BlueprintCallable, Category = "Simulation|Coordinates")
		bool CheckCRSString(FString CRSString, FString& Error);

private:
	void InitProj();
	bool RebuildProjections();
	PJ* GetProjection(FString SourceCRS, FString DestinationCRS);

	PJ_CONTEXT* ProjContext;
	PJ* ProjProjectedToGeographic;
	PJ* ProjProjectedToGeocentric;
	PJ* ProjGeographicToGeocentric;

	FLargeCoordinates OriginCoordinates;
	FString ProjectedCRS;
	FString GeographicCRS;
};
