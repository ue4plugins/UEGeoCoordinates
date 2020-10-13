// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "SimulationSettings.h"

class FSimulationModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** Settings Management */
	bool HandleSettingsSaved();
	void RegisterSettings();
	void UnregisterSettings();

	static USimulationSettings* GetSettings() { return Settings; };
private:

	static USimulationSettings* Settings;
};
