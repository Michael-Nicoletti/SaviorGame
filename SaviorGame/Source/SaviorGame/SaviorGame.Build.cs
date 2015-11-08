// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SaviorGame : ModuleRules
{
	public SaviorGame(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", 
            "OnlineSubsystem", "OnlineSubsystemNull", "OnlineSubsystemUtils" });

        PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem" });
	}
}
