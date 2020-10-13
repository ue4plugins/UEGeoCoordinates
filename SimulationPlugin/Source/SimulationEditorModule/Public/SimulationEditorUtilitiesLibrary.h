// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SimulationEditorUtilitiesLibrary.generated.h"

/**
 *
 */
UCLASS()
class SIMULATIONEDITORMODULE_API USimulationEditorUtilitiesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/*
		Return the Viewport-Space position of the mouse in the Level Editor Viewport. If the Level editor not are in focus it will return false.
	*/
	UFUNCTION(BlueprintCallable, Category = "Simulation|Viewport Utilities")
		static void GetViewportCursorLocation(bool& Focused, FVector2D& ScreenLocation);

	/*
		Return several informations about the viewport under the mouse cursor.
		  Viewport-Space position of cursor
		  Location of viewport origin (camera) in world space
		  Direction of viewport (camera) in world space
		If the Level editor not are in focus it will return false.
	*/
	UFUNCTION(BlueprintCallable, Category = "Simulation|Viewport Utilities")
		static void GetViewportCursorInformation(bool& Focused, FVector2D& ScreenLocation, FVector& WorldLocation, FVector& WorldDirection);

	/*
		LineTrace under mouse cursor and return various information
		  Viewport-Space position of cursor
		  Location of viewport origin (camera) in world space
		  Direction of viewport (camera) in world space
		  Hit Result
		If the Level editor not are in focus it will return false, and same if nothing is hit.
	*/
	UFUNCTION(BlueprintCallable, Category = "Simulation|Viewport Utilities", meta = (AdvancedDisplay = "TraceComplex, ShowTrace"))
		static void LineTraceViewport(const bool TraceComplex, const bool ShowTrace, bool& Success, FVector2D& ScreenLocation, FVector& WorldLocation, FVector& WorldDirection, FHitResult& HitResult);

	/*
		LineTrace at specific location/direction
	*/
	UFUNCTION(BlueprintCallable, Category = "Simulation|Utilities", meta = (AdvancedDisplay = "TraceComplex, ShowTrace, ActorsToIgnore"))
		static void LineTrace(const FVector WorldLocation, const FVector WorldDirection, const TArray<AActor*> ActorsToIgnore, const bool TraceComplex, const bool ShowTrace, bool& Success, FHitResult& HitResult);

	static bool HasFocus();
};
