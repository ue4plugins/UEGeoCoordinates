// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GameFramework/Pawn.h>
#include "GeoreferencingActor.generated.h"

UCLASS()
class SIMULATIONMODULE_API AGeoreferencingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeoreferencingActor();

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Destroyed() override;

public:
	UPROPERTY(EditAnywhere, Config, Category = Georeferencing)
		int32 OriginProjectedCoordinates_X = 705000; // Around Epic Games HQ

	UPROPERTY(EditAnywhere, Config, Category = Georeferencing)
		int32 OriginProjectedCoordinates_Y = 3960000; // Around Epic Games HQ

	UPROPERTY(EditAnywhere, Config, Category = Georeferencing)
		int32 OriginProjectedCoordinates_Z = 0; // For constituency, but should be 0

	UPROPERTY(EditAnywhere, Config, Category = Georeferencing)
		FString ProjectedCRS = FString("EPSG:32617"); // UTM Zone 17 North - (Cary) https://epsg.io/32617

	UPROPERTY(EditAnywhere, Config, Category = Georeferencing)
		FString GeographicCRS = FString("EPSG:4326"); // WGS84 https://epsg.io/4326

	UPROPERTY()
		class UGeoReferencingSubsystem* GeoReferencingSubsystem = NULL;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
