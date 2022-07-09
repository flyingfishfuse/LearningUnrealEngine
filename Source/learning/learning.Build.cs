// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class learning : ModuleRules
{
	public learning(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG" , "NavigationSystem","MinimapPlugin"});
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	}
}
