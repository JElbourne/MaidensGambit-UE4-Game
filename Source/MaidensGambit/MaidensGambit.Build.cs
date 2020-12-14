// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MaidensGambit : ModuleRules
{
	public MaidensGambit(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule" });
    }
}
