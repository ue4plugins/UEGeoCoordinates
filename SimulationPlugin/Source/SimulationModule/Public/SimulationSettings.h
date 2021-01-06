// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SimulationSettings.generated.h"

/**
 *
 */
UCLASS(Config = Simulation, defaultconfig)
class SIMULATIONMODULE_API USimulationSettings : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Config, Category = Georeferencing)
		int32 OriginProjectedCoordinates_X = 705000; // Around Epic Games HQ

	UPROPERTY(EditAnywhere, Config, Category = Georeferencing)
		int32 OriginProjectedCoordinates_Y = 3960000; // Around Epic Games HQ

	UPROPERTY(EditAnywhere, Config, Category = Georeferencing)
		int32 OriginProjectedCoordinates_Z = 0; // For constituency, but should be 0

	UPROPERTY(EditAnywhere, Config, Category = Georeferencing)
		FString ProjectedCRS = FString("EPSG:32617"); // UTM Zone 17 North - (Cary)

	UPROPERTY(EditAnywhere, Config, Category = Georeferencing)
		FString GeographicCRS = FString("EPSG:4326"); // WGS84 https://epsg.io/4326

	// UPROPERTY() // TODO - I should not do that, but otherwise I get this message : 
	// Warning: Disregard for GC object SimulationSettings / Script / SimulationModule.Default__SimulationSettings referencing GeoReferencingSubsystem / Game / Levels / EarthLevelNoBing.EarthLevelNoBing : GeoReferencingSubsystem_2147482578 which is not part of root set
		class UGeoReferencingSubsystem* GeoReferencingSubsystem = NULL;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
