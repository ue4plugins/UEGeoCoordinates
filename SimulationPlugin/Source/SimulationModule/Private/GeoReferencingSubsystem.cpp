// Fill out your copyright notice in the Description page of Project Settings.


#include "GeoReferencingSubsystem.h"
#include "Interfaces\IPluginManager.h"
#include <SimulationSettings.h>
#include "..\Public\GeoReferencingSubsystem.h"
#include "GeoReferencingActor.h"


UGeoReferencingSubsystem::UGeoReferencingSubsystem() : 
	ProjContext(NULL),
	ProjProjectedToGeographic(NULL),
	ProjProjectedToGeocentric(NULL),
	ProjGeographicToGeocentric(NULL),
	OriginCoordinates(0.0,0.0,0.0),
	ProjectedCRS(""),
	GeographicCRS("")
{
}

void UGeoReferencingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	InitProj();

	// By default, use global settings. If a georeferencing actor is there it will register itself afterwards.
	USimulationSettings* SimSettings = GetMutableDefault<USimulationSettings>();
	SimSettings->GeoReferencingSubsystem = this;

	SetOriginProjectedCoordinates(SimSettings->OriginProjectedCoordinates_X, SimSettings->OriginProjectedCoordinates_Y, SimSettings->OriginProjectedCoordinates_Z);
	this->GeographicCRS = SimSettings->GeographicCRS;
	this->ProjectedCRS = SimSettings->ProjectedCRS;
	RebuildProjections();
}

void UGeoReferencingSubsystem::Deinitialize()
{
	Super::Deinitialize();

	// Remove shared ref
	USimulationSettings* SimSettings = GetMutableDefault<USimulationSettings>();
	SimSettings->GeoReferencingSubsystem = NULL;

	// Destroy projections
	if (ProjProjectedToGeographic != NULL)
	{
		proj_destroy(ProjProjectedToGeographic);
	}
	if (ProjProjectedToGeocentric != NULL)
	{
		proj_destroy(ProjProjectedToGeocentric);
	}
	if (ProjGeographicToGeocentric != NULL)
	{
		proj_destroy(ProjGeographicToGeocentric);
	}

	// Destroy proj context
	if (ProjContext != NULL)
	{
		proj_context_destroy(ProjContext); /* may be omitted in the single threaded case */
	}
}

void UGeoReferencingSubsystem::RegisterGeoReferencingActor(AGeoreferencingActor* GeoActor)
{
	// Disconnect global setting to avoid unwanted updates
	USimulationSettings* SimSettings = GetMutableDefault<USimulationSettings>();
	SimSettings->GeoReferencingSubsystem = NULL;

	SetOriginProjectedCoordinates(GeoActor->OriginProjectedCoordinates_X, GeoActor->OriginProjectedCoordinates_Y, GeoActor->OriginProjectedCoordinates_Z);
	this->GeographicCRS = GeoActor->GeographicCRS;
	this->ProjectedCRS = GeoActor->ProjectedCRS;
	RebuildProjections();
}

void UGeoReferencingSubsystem::UnregisterGeoReferencingActor()
{
	// Reconnect global settings
	USimulationSettings* SimSettings = GetMutableDefault<USimulationSettings>();
	SimSettings->GeoReferencingSubsystem = this;

	// Apply settings 
	SetOriginProjectedCoordinates(SimSettings->OriginProjectedCoordinates_X, SimSettings->OriginProjectedCoordinates_Y, SimSettings->OriginProjectedCoordinates_Z);
	this->GeographicCRS = SimSettings->GeographicCRS;
	this->ProjectedCRS = SimSettings->ProjectedCRS;
	RebuildProjections();
}

void UGeoReferencingSubsystem::InitProj()
{
	// Initialize proj context
	
	// Get the base directory of this plugin
	FString BaseDir;
#if WITH_EDITOR
	BaseDir = IPluginManager::Get().FindPlugin("SimulationPlugin")->GetBaseDir();
#else
	BaseDir = FPaths::ProjectDir();
#endif
	BaseDir = FPaths::ConvertRelativePathToFull(BaseDir);

	// Add on the relative location of the third party dll and load it
	FString ProjDataPathPath;
#if PLATFORM_WINDOWS
	ProjDataPathPath = FPaths::Combine(*BaseDir, TEXT("Binaries/Win64/proj-data"));
#endif // PLATFORM_WINDOWS


	UE_LOG(LogTemp, Display, TEXT("Initializing Proj context using Data in '%s'"), *ProjDataPathPath);
	ProjContext = proj_context_create();
	if (ProjContext == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("proj_context_create() failed - Check DLL dependencies"));
	}
	FTCHARToUTF8 Convert(*ProjDataPathPath);
	const ANSICHAR* Temp = Convert.Get();
	proj_context_set_search_paths(ProjContext, 1, &Temp);
}

bool UGeoReferencingSubsystem::SetProjectedCRS(FString InProjectedCRS)
{
	this->ProjectedCRS = InProjectedCRS;
	return RebuildProjections();
}

bool UGeoReferencingSubsystem::SetGeographicCRS(FString InGeographicCRS)
{
	this->GeographicCRS = InGeographicCRS;
	return RebuildProjections();
}

bool UGeoReferencingSubsystem::SetOriginProjectedCoordinates(int32 InX, int32 InY, int32 InZ)
{
	this->OriginCoordinates = FLargeCoordinates(InX, InY, InZ);
	return true;
}


void UGeoReferencingSubsystem::EngineToProjected(FVector EngineCoordinates, FLargeCoordinates& ProjectedCoordinates)
{
	ProjectedCoordinates = FLargeCoordinates(
		EngineCoordinates.X * 0.01 + OriginCoordinates.X,
		-EngineCoordinates.Y * 0.01 + OriginCoordinates.Y,
		EngineCoordinates.Z * 0.01 + OriginCoordinates.Z);
}

void UGeoReferencingSubsystem::ProjectedToEngine(FLargeCoordinates ProjectedCoordinates, FVector& EngineCoordinates)
{
	EngineCoordinates = FVector(
		ProjectedCoordinates.X - OriginCoordinates.X,
		-(ProjectedCoordinates.Y - OriginCoordinates.Y),
		ProjectedCoordinates.Z - OriginCoordinates.Z) * 100;
}


void UGeoReferencingSubsystem::ProjectedToGeographic(FLargeCoordinates ProjectedCoordinates, FGeographicCoordinates& GeographicCoordinates)
{
	PJ_COORD input, output;
	input = proj_coord(ProjectedCoordinates.X, ProjectedCoordinates.Y, ProjectedCoordinates.Z, 0);
	
	output = proj_trans(ProjProjectedToGeographic, PJ_FWD, input);
	GeographicCoordinates.Latitude = output.lpz.phi;
	GeographicCoordinates.Longitude = output.lpz.lam;
	GeographicCoordinates.Altitude = output.lpz.z;
}

void UGeoReferencingSubsystem::ProjectedToGeocentric(FLargeCoordinates ProjectedCoordinates, FLargeCoordinates& GeocentricCoordinates)
{
	PJ_COORD input, output;
	input = proj_coord(ProjectedCoordinates.X, ProjectedCoordinates.Y, ProjectedCoordinates.Z, 0);

	output = proj_trans(ProjProjectedToGeocentric, PJ_FWD, input);
	GeocentricCoordinates.X = output.xyz.x;
	GeocentricCoordinates.Y = output.xyz.y;
	GeocentricCoordinates.Z = output.xyz.z;
}

void UGeoReferencingSubsystem::GeographicToProjected(FGeographicCoordinates GeographicCoordinates, FLargeCoordinates& ProjectedCoordinates)
{
	PJ_COORD input, output;
	input = proj_coord(GeographicCoordinates.Longitude, GeographicCoordinates.Latitude, GeographicCoordinates.Altitude, 0);

	output = proj_trans(ProjProjectedToGeographic, PJ_INV, input);
	ProjectedCoordinates.X = output.xyz.x;
	ProjectedCoordinates.Y = output.xyz.y;
	ProjectedCoordinates.Z = output.xyz.z;
}

void UGeoReferencingSubsystem::GeographicToGeocentric(FGeographicCoordinates GeographicCoordinates, FLargeCoordinates& GeocentricCoordinates)
{
	PJ_COORD input, output;
	input = proj_coord(GeographicCoordinates.Longitude, GeographicCoordinates.Latitude, GeographicCoordinates.Altitude, 0);

	output = proj_trans(ProjGeographicToGeocentric, PJ_FWD, input);
	GeocentricCoordinates.X = output.xyz.x;
	GeocentricCoordinates.Y = output.xyz.y;
	GeocentricCoordinates.Z = output.xyz.z;
}

void UGeoReferencingSubsystem::GeocentricToProjected(FLargeCoordinates GeocentricCoordinates, FLargeCoordinates& ProjectedCoordinates)
{
	PJ_COORD input, output;
	input = proj_coord(GeocentricCoordinates.X, GeocentricCoordinates.Y, GeocentricCoordinates.Z, 0);

	output = proj_trans(ProjProjectedToGeocentric, PJ_INV, input);
	ProjectedCoordinates.X = output.xyz.x;
	ProjectedCoordinates.Y = output.xyz.y;
	ProjectedCoordinates.Z = output.xyz.z;
}

void UGeoReferencingSubsystem::GeocentricToGeographic(FLargeCoordinates GeocentricCoordinates, FGeographicCoordinates& GeographicCoordinates)
{
	PJ_COORD input, output;
	input = proj_coord(GeocentricCoordinates.X, GeocentricCoordinates.Y, GeocentricCoordinates.Z, 0);

	output = proj_trans(ProjGeographicToGeocentric, PJ_INV, input);
	GeographicCoordinates.Latitude = output.lpz.phi;
	GeographicCoordinates.Longitude = output.lpz.lam;
	GeographicCoordinates.Altitude = output.lpz.z;
}

bool UGeoReferencingSubsystem::CheckCRSString(FString CRSString, FString& Error)
{
	if (ProjContext == NULL)
	{
		Error = FString("Proj Context has not been initialized");
		return false;
	}

	// Try to create a CRS from this string
	FTCHARToUTF8 Convert(*CRSString);
	const ANSICHAR* UtfString = Convert.Get();
	PJ* CRS = proj_create(ProjContext, UtfString);

	if (CRS == NULL)
	{
		int ErrorNumber = proj_context_errno(ProjContext);
		Error = FString(proj_errno_string(ErrorNumber));
		return false;
	}
	
	proj_destroy(CRS);
	return true;
}

bool UGeoReferencingSubsystem::RebuildProjections()
{
	// Projected -> Geographic
	if (ProjProjectedToGeographic != NULL)
	{
		proj_destroy(ProjProjectedToGeographic);
	}
	ProjProjectedToGeographic = GetProjection(ProjectedCRS, GeographicCRS);
	
	// Projected -> Geocentric
	if (ProjProjectedToGeocentric != NULL)
	{
		proj_destroy(ProjProjectedToGeocentric);
	}
	ProjProjectedToGeocentric = GetProjection(ProjectedCRS, FString("EPSG:4978"));

	// Geographic -> Geocentric
	if (ProjGeographicToGeocentric != NULL)
	{
		proj_destroy(ProjGeographicToGeocentric);
	}
	ProjGeographicToGeocentric = GetProjection(GeographicCRS, FString("EPSG:4978"));

	return (ProjProjectedToGeographic != NULL && ProjProjectedToGeocentric != NULL && ProjGeographicToGeocentric != NULL);
}


PJ*  UGeoReferencingSubsystem::GetProjection(FString SourceCRS, FString DestinationCRS)
{
	FTCHARToUTF8 ConvertSource(*SourceCRS);
	FTCHARToUTF8 ConvertDestination(*DestinationCRS);
	const ANSICHAR* Source = ConvertSource.Get();
	const ANSICHAR* Destination = ConvertDestination.Get();
	
	PJ* TempPJ = proj_create_crs_to_crs(ProjContext, Source, Destination, NULL);
	if (TempPJ == NULL) {
		int ErrorNumber = proj_context_errno(ProjContext);
		FString ProjError = FString(proj_errno_string(ErrorNumber));
		UE_LOG(LogTemp, Error, TEXT("UGeoReferencingSubsystem::BuildProjection failed in proj_create_crs_to_crs : %s "), *ProjError);

		UE_LOG(LogTemp, Display, TEXT("SourceCRS was : %s "), *SourceCRS);
		UE_LOG(LogTemp, Display, TEXT("DestinationCRS was : %s "), *DestinationCRS);
		return NULL;
	}

	/* This will ensure that the order of coordinates for the input CRS */
	/* will be longitude, latitude, whereas EPSG:4326 mandates latitude, longitude */
	PJ* P_for_GIS = proj_normalize_for_visualization(ProjContext, TempPJ);
	if (P_for_GIS == NULL) {
		int ErrorNumber = proj_context_errno(ProjContext);
		FString ProjError = FString(proj_errno_string(ErrorNumber));
		UE_LOG(LogTemp, Error, TEXT("UGeoReferencingSubsystem::BuildProjection failed in proj_normalize_for_visualization : %s "), *ProjError);
		return NULL;
	}
	proj_destroy(TempPJ);
	return P_for_GIS;
}
