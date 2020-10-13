// Fill out your copyright notice in the Description page of Project Settings.

#include "SimulationEditorUtilitiesLibrary.h"
#include <SimulationEditorModule.h>

#include <EditorViewportClient.h>
#include <LevelEditorViewport.h>
#include <PhysicsEngine/PhysicsSettings.h>
#include <Engine/EngineTypes.h>

void USimulationEditorUtilitiesLibrary::GetViewportCursorLocation(bool& Focused, FVector2D& Location)
{
	Focused = false;
	Location = FVector2D(-1, -1);

	if (GCurrentLevelEditingViewportClient != nullptr && GCurrentLevelEditingViewportClient->Viewport->HasFocus()) {
		FViewportCursorLocation cursor = GCurrentLevelEditingViewportClient->GetCursorWorldLocationFromMousePos();
		FIntPoint pos = cursor.GetCursorPos();
		Location.X = pos.X;
		Location.Y = pos.Y;
		Focused = true;
	}
}

void USimulationEditorUtilitiesLibrary::GetViewportCursorInformation(bool& Focused, FVector2D& ScreenLocation, FVector& WorldLocation, FVector& WorldDirection)
{
	Focused = false;
	ScreenLocation = FVector2D(-1, -1);
	WorldLocation = FVector::ZeroVector;
	WorldDirection = FVector::ZeroVector;

	if (GCurrentLevelEditingViewportClient != nullptr && GCurrentLevelEditingViewportClient->Viewport->HasFocus()) {
		FViewportCursorLocation cursorWL = GCurrentLevelEditingViewportClient->GetCursorWorldLocationFromMousePos();

		FIntPoint pos = cursorWL.GetCursorPos();
		ScreenLocation.X = pos.X;
		ScreenLocation.Y = pos.Y;
		WorldLocation = cursorWL.GetOrigin();
		WorldDirection = cursorWL.GetDirection();
		Focused = true;
	}
}

void USimulationEditorUtilitiesLibrary::LineTraceViewport(const bool TraceComplex, const bool ShowTrace, bool& Success, FVector2D& ScreenLocation, FVector& WorldLocation, FVector& WorldDirection, FHitResult& HitResult)
{
	HitResult = FHitResult();
	Success = false;
	bool Focused;
	GetViewportCursorInformation(Focused, ScreenLocation, WorldLocation, WorldDirection);
	
	if (Focused)
	{
		LineTrace(WorldLocation, WorldDirection, TArray<AActor*>(), TraceComplex, ShowTrace, Success, HitResult);
	}

}

void USimulationEditorUtilitiesLibrary::LineTrace(const FVector WorldLocation, const FVector WorldDirection, const TArray<AActor*> ActorsToIgnore, const bool TraceComplex, const bool ShowTrace, bool& Success, FHitResult& HitResult)
{
	HitResult = FHitResult();
	Success = false;
	if (GWorld == nullptr) 
		return;

	FVector LineCheckStart = WorldLocation;
	FVector LineCheckEnd = WorldLocation + WorldDirection * WORLD_MAX;

	static const FName LineTraceSingleName(TEXT("LevelEditorLineTrace"));
	if (ShowTrace) {
		GWorld->DebugDrawTraceTag = LineTraceSingleName;
	}
	else
	{
		GWorld->DebugDrawTraceTag = NAME_None;
	}

	FCollisionQueryParams CollisionParams(LineTraceSingleName);
	CollisionParams.bTraceComplex = TraceComplex;
	CollisionParams.bReturnPhysicalMaterial = true;
	CollisionParams.bReturnFaceIndex = !UPhysicsSettings::Get()->bSuppressFaceRemapTable; // Ask for face index, as long as we didn't disable globally
	CollisionParams.AddIgnoredActors(ActorsToIgnore);

	FCollisionObjectQueryParams ObjectParams = FCollisionObjectQueryParams(ECC_WorldStatic);
	ObjectParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectParams.AddObjectTypesToQuery(ECC_Pawn);
	ObjectParams.AddObjectTypesToQuery(ECC_Visibility);

	if (GWorld->LineTraceSingleByObjectType(HitResult, LineCheckStart, LineCheckEnd, ObjectParams, CollisionParams))
	{
		Success = true;
	}
}

bool USimulationEditorUtilitiesLibrary::HasFocus()
{
	if (GCurrentLevelEditingViewportClient == nullptr) return false;

	return GCurrentLevelEditingViewportClient->Viewport->HasFocus();
}
