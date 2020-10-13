// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
using System.IO;
using UnrealBuildTool;

public class Proj : ModuleRules
{
    public Proj(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;
		bEnableExceptions = true;
		
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            // add include path
            string IncPath = Path.Combine(ModuleDirectory, "include");
            PublicSystemIncludePaths.Add(IncPath);

            // add lib path
            string LibPath = Path.Combine(ModuleDirectory, "lib");
            
            // Explicitly name the used libraries
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "proj.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibPath, "libcurl.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibPath, "sqlite3.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibPath, "tiff.lib"));

            // add macros
            PublicDefinitions.Add("WITH_PROJ_API=1");
            PublicDefinitions.Add("__WINDOWS__");
        }
    }
}
