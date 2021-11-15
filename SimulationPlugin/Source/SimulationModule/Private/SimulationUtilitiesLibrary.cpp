// Fill out your copyright notice in the Description page of Project Settings.


#include "SimulationUtilitiesLibrary.h"

// FGeographicCoordinates Converters

FText USimulationUtilitiesLibrary::Conv_GeographicCoordinatesToFullText(FGeographicCoordinates InGeographicCoordinates, int32 IntegralDigitsLatLon /*= 8*/, int32 IntegralDigitsAlti /*= 2*/, bool AsDMS /*=false*/ )
{
	FNumberFormattingOptions NumberFormatOptions = FNumberFormattingOptions::DefaultNoGrouping();
	FFormatNamedArguments Args;
	
	// LatLon
	NumberFormatOptions.MinimumFractionalDigits = IntegralDigitsLatLon;
	NumberFormatOptions.MaximumFractionalDigits = IntegralDigitsLatLon;
	Args.Add(TEXT("Latitude"), USimulationUtilitiesLibrary::AsAngle(InGeographicCoordinates.Latitude, &NumberFormatOptions, AsDMS));
	Args.Add(TEXT("Longitude"), USimulationUtilitiesLibrary::AsAngle(InGeographicCoordinates.Longitude, &NumberFormatOptions, AsDMS));
	// Alti
	NumberFormatOptions.MinimumFractionalDigits = IntegralDigitsAlti;
	NumberFormatOptions.MaximumFractionalDigits = IntegralDigitsAlti;
	Args.Add(TEXT("Altitude"), FText::AsNumber(InGeographicCoordinates.Altitude, &NumberFormatOptions));

	return FText::Format(NSLOCTEXT("SimulationModule", "GeographicCoordinates", "Longitude={Longitude} Latitude={Latitude} Altitude={Altitude}m"), Args);
}

FText USimulationUtilitiesLibrary::Conv_GeographicCoordinatesToCompactText(FGeographicCoordinates InGeographicCoordinates, int32 IntegralDigitsLatLon /*= 8*/, int32 IntegralDigitsAlti /*= 2*/, bool AsDMS /*=false*/)
{
	FNumberFormattingOptions NumberFormatOptions = FNumberFormattingOptions::DefaultNoGrouping();
	FFormatNamedArguments Args;

	// LatLon
	NumberFormatOptions.MinimumFractionalDigits = IntegralDigitsLatLon;
	NumberFormatOptions.MaximumFractionalDigits = IntegralDigitsLatLon;
	Args.Add(TEXT("Latitude"), USimulationUtilitiesLibrary::AsAngle(InGeographicCoordinates.Latitude, &NumberFormatOptions, AsDMS));
	Args.Add(TEXT("Longitude"), USimulationUtilitiesLibrary::AsAngle(InGeographicCoordinates.Longitude, &NumberFormatOptions, AsDMS));
	// Alti
	NumberFormatOptions.MinimumFractionalDigits = IntegralDigitsAlti;
	NumberFormatOptions.MaximumFractionalDigits = IntegralDigitsAlti;
	Args.Add(TEXT("Altitude"), FText::AsNumber(InGeographicCoordinates.Altitude, &NumberFormatOptions));

	return FText::Format(NSLOCTEXT("SimulationModule", "GeographicCoordinates", "({Longitude}, {Latitude})  {Altitude}m"), Args);
}

void USimulationUtilitiesLibrary::Conv_GeographicCoordinatesToSeparateTexts(FGeographicCoordinates InGeographicCoordinates, FText& Latitude, FText& Longitude, FText& Altitude, int32 IntegralDigitsLatLon /*= 8*/, int32 IntegralDigitsAlti /*= 2*/, bool AsDMS /*=false*/)
{
	FNumberFormattingOptions NumberFormatOptions = FNumberFormattingOptions::DefaultNoGrouping();
	
	// LatLon
	NumberFormatOptions.MinimumFractionalDigits = IntegralDigitsLatLon;
	NumberFormatOptions.MaximumFractionalDigits = IntegralDigitsLatLon;
	Latitude = USimulationUtilitiesLibrary::AsAngle(InGeographicCoordinates.Latitude, &NumberFormatOptions, AsDMS);
	Longitude = USimulationUtilitiesLibrary::AsAngle(InGeographicCoordinates.Longitude, &NumberFormatOptions, AsDMS);
	// Alti
	NumberFormatOptions.MinimumFractionalDigits = IntegralDigitsAlti;
	NumberFormatOptions.MaximumFractionalDigits = IntegralDigitsAlti;
	Altitude = FText::AsNumber(InGeographicCoordinates.Altitude, &NumberFormatOptions);
}



// FLargeCoordinates Converters

FText USimulationUtilitiesLibrary::Conv_LargeCoordinatesToFullText(FLargeCoordinates InLargeCoordinates, int32 IntegralDigits /*= 3*/)
{
	FNumberFormattingOptions NumberFormatOptions = FNumberFormattingOptions::DefaultNoGrouping();
	NumberFormatOptions.MinimumFractionalDigits = IntegralDigits;
	NumberFormatOptions.MaximumFractionalDigits = IntegralDigits;

	FFormatNamedArguments Args;
	Args.Add(TEXT("X"), FText::AsNumber(InLargeCoordinates.X, &NumberFormatOptions));
	Args.Add(TEXT("Y"), FText::AsNumber(InLargeCoordinates.Y, &NumberFormatOptions));
	Args.Add(TEXT("Z"), FText::AsNumber(InLargeCoordinates.Z, &NumberFormatOptions));

	return FText::Format(NSLOCTEXT("SimulationModule", "GeographicCoordinates", "X={X} Y={Y} Z={Z}"), Args);
}

FText USimulationUtilitiesLibrary::Conv_LargeCoordinatesToCompactText(FLargeCoordinates InLargeCoordinates, int32 IntegralDigits /*= 3*/)
{
	FNumberFormattingOptions NumberFormatOptions = FNumberFormattingOptions::DefaultNoGrouping();
	NumberFormatOptions.MinimumFractionalDigits = IntegralDigits;
	NumberFormatOptions.MaximumFractionalDigits = IntegralDigits;

	FFormatNamedArguments Args;
	Args.Add(TEXT("X"), FText::AsNumber(InLargeCoordinates.X, &NumberFormatOptions));
	Args.Add(TEXT("Y"), FText::AsNumber(InLargeCoordinates.Y, &NumberFormatOptions));
	Args.Add(TEXT("Z"), FText::AsNumber(InLargeCoordinates.Z, &NumberFormatOptions));

	return FText::Format(NSLOCTEXT("SimulationModule", "GeographicCoordinates", "({X}, {Y}, {Z}m )"), Args);
}

void USimulationUtilitiesLibrary::Conv_LargeCoordinatesToSeparateTexts(FLargeCoordinates InLargeCoordinates, FText& X, FText& Y, FText& Z, int32 IntegralDigits /*= 3*/)
{
	FNumberFormattingOptions NumberFormatOptions = FNumberFormattingOptions::DefaultNoGrouping();
	NumberFormatOptions.MinimumFractionalDigits = IntegralDigits;
	NumberFormatOptions.MaximumFractionalDigits = IntegralDigits;

	X = FText::AsNumber(InLargeCoordinates.X, &NumberFormatOptions);
	Y = FText::AsNumber(InLargeCoordinates.Y, &NumberFormatOptions);
	Z = FText::AsNumber(InLargeCoordinates.Z, &NumberFormatOptions);
}

void USimulationUtilitiesLibrary::CreateGeographicCoordinatesApproximation(float Latitude, float Longitude, float Altitude, FGeographicCoordinates& GeographicCoordinates)
{
	GeographicCoordinates.Latitude = static_cast<double>(Latitude);
	GeographicCoordinates.Longitude = static_cast<double>(Longitude);
	GeographicCoordinates.Altitude = static_cast<double>(Altitude);
}


void USimulationUtilitiesLibrary::CreateLargeCoordinatesApproximation(float X, float Y, float Z, FLargeCoordinates& LargeCoordinates)
{
	LargeCoordinates.X = static_cast<double>(X);
	LargeCoordinates.Y = static_cast<double>(Y);
	LargeCoordinates.Z = static_cast<double>(Z);
}

void USimulationUtilitiesLibrary::GetGeographicCoordinatesApproximation(FGeographicCoordinates GeographicCoordinates, float& Latitude, float& Longitude, float& Altitude)
{
	Latitude = static_cast<float>(GeographicCoordinates.Latitude);
	Longitude = static_cast<float>(GeographicCoordinates.Longitude);
	Altitude = static_cast<float>(GeographicCoordinates.Altitude);
}

void USimulationUtilitiesLibrary::GetLargeCoordinatesApproximation(FLargeCoordinates LargeCoordinates, float& X, float& Y, float& Z)
{
	X = static_cast<float>(LargeCoordinates.X);
	Y = static_cast<float>(LargeCoordinates.Y);
	Z = static_cast<float>(LargeCoordinates.Z);
}

FText USimulationUtilitiesLibrary::AsAngle(double Val, const FNumberFormattingOptions* const Options /*= NULL*/, bool AsDMS /*= false*/)
{
	if (AsDMS)
	{
		int32 degrees = FMath::TruncToInt(Val);
		int32 minutes = FMath::TruncToInt(60.0 * FMath::Abs<double>(Val - degrees));
		double seconds = 3600.0 * FMath::Abs<double>(Val - degrees) - 60.0 * minutes;
		return FText::Format(NSLOCTEXT("SimulationModule", "AngleDMSFmt", "{0}° {1}' {2}\""), FText::AsNumber(degrees), FText::AsNumber(minutes), FText::AsNumber(seconds, Options));
	}
	else
	{
		return FText::Format(NSLOCTEXT("SimulationModule", "AngleDegFmt", "{0}°"), FText::AsNumber(Val, Options));
	}
}


