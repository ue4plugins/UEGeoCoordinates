// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

using System;
using System.IO;
using System.Collections.Generic;

public class SimulationModule : ModuleRules
{
    public SimulationModule(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        bEnableExceptions = true;

        PublicIncludePaths.AddRange(
            new string[] {
				// ... add public include paths required here ...
			}
            );


        PrivateIncludePaths.AddRange(
            new string[] {
				// ... add other private include paths required here ...
			}
            );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", "CoreUObject", "Engine", "InputCore",
                "Proj",
                "Projects"
				// ... add other public dependencies that you statically link with here ...
			}
            );

            PrivateDependencyModuleNames.AddRange(
            new string[]
            {
				// ... add private dependencies that you statically link with here ...	
			}
            );


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
				// ... add any modules that your module loads dynamically here ...
			}
            );

        // Add dependencies to PROJ
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            List<string> RuntimeModuleNames = new List<string>();
            RuntimeModuleNames.Add("jpeg62.dll");
            RuntimeModuleNames.Add("lzma.dll");
            RuntimeModuleNames.Add("sqlite3.dll");
            RuntimeModuleNames.Add("tiff.dll");
            RuntimeModuleNames.Add("zlib1.dll");
            string ProjRedistFolder = Path.Combine(ModuleDirectory, @"..\ThirdParty\Proj\redist");


            foreach (string RuntimeModuleName in RuntimeModuleNames)
            {
                string ModulePath = Path.Combine(ProjRedistFolder, RuntimeModuleName);
                if (!File.Exists(ModulePath))
                {
                    string Err = string.Format("PROJ SDK module '{0}' not found.", ModulePath);
                    System.Console.WriteLine(Err);
                    throw new BuildException(Err);
                }
                //PublicDelayLoadDLLs.Add(RuntimeModuleName);
                RuntimeDependencies.Add("$(BinaryOutputDir)/" + RuntimeModuleName, ModulePath);
            }

            // Stage Proj data files
            RuntimeDependencies.Add("$(BinaryOutputDir)/proj-data/*", Path.Combine(ProjRedistFolder, "proj-data/*"), StagedFileType.SystemNonUFS);
        }
    }
}
