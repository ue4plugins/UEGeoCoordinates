// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LargeCoordinates.generated.h"

/**
 * A vector in 3-D space composed of components (X, Y, Z) with double precision.
 * Unfortunately, can't be exposed to Blueprints yet
 */
USTRUCT(BlueprintType)
struct FLargeCoordinates
{
	GENERATED_USTRUCT_BODY()

public:
	double X;
	double Y;
	double Z;

	/** A zero Coordinate (0,0,0) */
	static SIMULATIONMODULE_API const FLargeCoordinates ZeroCoordinates;

	/** Default constructor (no initialization). */
	FORCEINLINE FLargeCoordinates();

	/**
	 * Constructor using initial values for each component.
	 *
	 * @param InX X Coordinate.
	 * @param InY Y Coordinate.
	 * @param InZ Z Coordinate.
	 */
	FORCEINLINE FLargeCoordinates(double InX, double InY, double InZ);

	/**
	 * Constructs a FLargeCoordinates from an existing FLargeCoordinates
	 * @param InLargeCoordinates 
	*/
	FORCEINLINE FLargeCoordinates(const FLargeCoordinates& InLargeCoordinates);

#ifdef IMPLEMENT_ASSIGNMENT_OPERATOR_MANUALLY
	/**
	* Copy another FLargeCoordinates into this one
	*
	* @param Other The other FLargeCoordinates.
	* @return Reference to FLargeCoordinates after copy.
	*/
	FORCEINLINE FLargeCoordinates& operator=(const FLargeCoordinates& Other);
#endif
};
DECLARE_INTRINSIC_TYPE_LAYOUT(FLargeCoordinates);

FORCEINLINE FLargeCoordinates::FLargeCoordinates()
{}

FORCEINLINE FLargeCoordinates::FLargeCoordinates(double InX, double InY, double InZ) :
	X(InX),
	Y(InY),
	Z(InZ)
{
}

FORCEINLINE FLargeCoordinates::FLargeCoordinates(const FLargeCoordinates& InCoordinates) :
	X(InCoordinates.X),
	Y(InCoordinates.Y),
	Z(InCoordinates.Z)
{
}

#ifdef IMPLEMENT_ASSIGNMENT_OPERATOR_MANUALLY
FORCEINLINE FLargeCoordinates& FLargeCoordinates::operator=(const FLargeCoordinates& Other)
{
	this->X = Other.X;
	this->Y = Other.Y;
	this->Z = Other.Z;
	return *this;
}

#endif

SIMULATIONMODULE_API const FLargeCoordinates FLargeCoordinates::ZeroCoordinates(0.0, 0.0, 0.0);