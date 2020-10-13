// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimulationModule.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "Developer/Settings/Public/ISettingsContainer.h"
#include "Developer/Settings/Public/ISettingsSection.h" 
#include "Developer/Settings/Public/ISettingsModule.h"
//#include "SimulationPluginLibrary/ExampleLibrary.h"

#define LOCTEXT_NAMESPACE "FSimulationModule"

USimulationSettings* FSimulationModule::Settings;

void FSimulationModule::StartupModule()
{
	RegisterSettings();
}

void FSimulationModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	if (UObjectInitialized())
	{
		UnregisterSettings();
	}
}

bool FSimulationModule::HandleSettingsSaved()
{
#if WITH_EDITORONLY_DATA
	Settings = GetMutableDefault<USimulationSettings>();
	Settings->SaveConfig(); 
	return true;
#endif
	return false;
}

void FSimulationModule::RegisterSettings()
{
#if WITH_EDITORONLY_DATA
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings")) 
	{
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "Simulation",
			LOCTEXT("RuntimeGeneralName", "Simulation Plugin"),
			LOCTEXT("RuntimeGeneralDescription", "General settings for the Simulation Plugin"),
			GetMutableDefault<USimulationSettings>());
		
		if (SettingsSection.IsValid()) { 
			SettingsSection->OnModified().BindRaw(this, &FSimulationModule::HandleSettingsSaved); 
		}
	}
#endif
}

void FSimulationModule::UnregisterSettings()
{
#if WITH_EDITORONLY_DATA
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings")) {
		SettingsModule->UnregisterSettings("Project", "Plugins", "Simulation");
	}
#endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSimulationModule, SimulationModule)
