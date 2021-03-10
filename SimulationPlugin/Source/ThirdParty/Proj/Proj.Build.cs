// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
using System.IO;
using UnrealBuildTool;

public class Proj : ModuleRules
{
    public Proj(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;
		bEnableExceptions = true;

        // add include path
        string IncPath = Path.Combine(ModuleDirectory, "include");
        PublicSystemIncludePaths.Add(IncPath);

        // add lib path
        string LibPath = Path.Combine(ModuleDirectory, "lib");
		
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            // Explicitly name the used libraries
            LibPath = Path.Combine(LibPath, "Win64");
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "proj.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibPath, "sqlite3.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibPath, "tiff.lib"));

            // add macros
            PublicDefinitions.Add("__WINDOWS__");
        }
        else if(Target.Platform == UnrealTargetPlatform.Linux)
        {
            // Explicitly name the used libraries
            LibPath = Path.Combine(LibPath, "Linux");
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "libproj.a"));
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "libsqlite3.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibPath, "libtiff.a"));
        }

        // add macros
        PublicDefinitions.Add("WITH_PROJ_API=1");
    }
}
