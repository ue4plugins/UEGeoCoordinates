// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeographicCoordinates.h"
#include "LargeCoordinates.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SimulationUtilitiesLibrary.generated.h"

/**
 *
 */
UCLASS()
class SIMULATIONMODULE_API USimulationUtilitiesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

// FGeographicCoordinates Converters

	/** Converts a GeographicCoordinates value to localized formatted text, in the form 'Longitude= Latitude= Altitude=' */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToFullText", AdvancedDisplay = "1", BlueprintAutocast), Category = "Simulation|Coordinates")
		static FText Conv_GeographicCoordinatesToFullText(FGeographicCoordinates InGeographicCoordinates, int32 IntegralDigitsLatLon = 8, int32 IntegralDigitsAlti = 2, bool AsDMS = false);

	/** Converts a GeographicCoordinates value to formatted text, in the form '(Latitude,Longitude) Altitude' */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToCompactText", AdvancedDisplay = "1", BlueprintAutocast), Category = "Simulation|Coordinates")
		static FText Conv_GeographicCoordinatesToCompactText(FGeographicCoordinates InGeographicCoordinates, int32 IntegralDigitsLatLon = 8, int32 IntegralDigitsAlti = 2, bool AsDMS = false);

	/** Converts a GeographicCoordinates value to 3 separate text values */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToSeparateTexts", AdvancedDisplay = "4", BlueprintAutocast), Category = "Simulation|Coordinates")
		static void Conv_GeographicCoordinatesToSeparateTexts(FGeographicCoordinates InGeographicCoordinates, FText& Latitude, FText& Longitude, FText& Altitude, int32 IntegralDigitsLatLon = 8, int32 IntegralDigitsAlti = 2, bool AsDMS = false);

	// TODO : Converters for HMS, Decimal... 

// FLargeCoordinates Converters

	/** Converts a LargeCoordinates value to localized formatted text, in the form 'X= Y= Z=' */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToFullText", AdvancedDisplay = "1", BlueprintAutocast), Category = "Simulation|Coordinates")
		static FText Conv_LargeCoordinatesToFullText(FLargeCoordinates InLargeCoordinates, int32 IntegralDigits = 3);

	/** Converts a LargeCoordinates value to formatted text, in the form '(X, Y, Z)' */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToCompactText", AdvancedDisplay = "1", BlueprintAutocast), Category = "Simulation|Coordinates")
		static FText Conv_LargeCoordinatesToCompactText(FLargeCoordinates InLargeCoordinates, int32 IntegralDigits = 3);

	/** Converts a LargeCoordinates value to 3 separate text values */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToSeparateTexts", AdvancedDisplay = "4", BlueprintAutocast), Category = "Simulation|Coordinates")
		static void Conv_LargeCoordinatesToSeparateTexts(FLargeCoordinates InLargeCoordinates, FText& X, FText& Y, FText& Z, int32 IntegralDigits = 3);

private:
	static FText AsAngle(double Val, const FNumberFormattingOptions* const Options = NULL, bool AsDMS = false);
};
