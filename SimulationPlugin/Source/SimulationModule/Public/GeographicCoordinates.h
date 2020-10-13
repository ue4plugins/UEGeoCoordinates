// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Internationalization/Text.h>
#include "GeographicCoordinates.generated.h"

/**
 * A Point in 3-D space located by Longitude, Latitude and Altitude with double point precision.
 */
USTRUCT(BlueprintType)
struct FGeographicCoordinates
{
	GENERATED_USTRUCT_BODY()

public:
		double Longitude;
		double Latitude;
		double Altitude;

public:

	/** A zero Coordinate (0,0,0) */
	static SIMULATIONMODULE_API const FGeographicCoordinates ZeroCoordinates;

	/** Default constructor (no initialization). */
	FORCEINLINE FGeographicCoordinates();

	/**
	 * Constructor using initial values for each component.
	 *
	 * @param InX X Coordinate.
	 * @param InY Y Coordinate.
	 * @param InZ Z Coordinate.
	 */
	FORCEINLINE FGeographicCoordinates(double InLatitude, double InLongitude, double InAltitude);

	/**
	 * Constructs a vector from an FVector2D and Z value.
	 *
	 * @param V Vector to copy from.
	 * @param InZ Z Coordinate.
	 */
	FORCEINLINE FGeographicCoordinates(const FGeographicCoordinates& InCoordinates);

#ifdef IMPLEMENT_ASSIGNMENT_OPERATOR_MANUALLY
	/**
	* Copy another FVector into this one
	*
	* @param Other The other vector.
	* @return Reference to vector after copy.
	*/
	FORCEINLINE FGeographicCoordinates& operator=(const FGeographicCoordinates& Other);
#endif

};
DECLARE_INTRINSIC_TYPE_LAYOUT(FGeographicCoordinates);

FORCEINLINE FGeographicCoordinates::FGeographicCoordinates()
{}

FORCEINLINE FGeographicCoordinates::FGeographicCoordinates(double InLatitude, double InLongitude, double InAltitude)
	: Longitude(InLongitude), Latitude(InLatitude), Altitude(InAltitude)
{
}

FORCEINLINE FGeographicCoordinates::FGeographicCoordinates(const FGeographicCoordinates& InCoordinates)
	: Longitude(InCoordinates.Longitude), Latitude(InCoordinates.Latitude), Altitude(InCoordinates.Altitude)
{
}

#ifdef IMPLEMENT_ASSIGNMENT_OPERATOR_MANUALLY
FORCEINLINE FGeographicCoordinates& FGeographicCoordinates::operator=(const FGeographicCoordinates& Other)
{
	this->Latitude = Other.Latitude;
	this->Longitude = Other.Longitude;
	this->Altitude = Other.Altitude;
	return *this;
}

#endif

SIMULATIONMODULE_API const FGeographicCoordinates FGeographicCoordinates::ZeroCoordinates(0.0, 0.0, 0.0);