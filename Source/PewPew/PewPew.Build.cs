// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PewPew : ModuleRules
{
	public PewPew(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
