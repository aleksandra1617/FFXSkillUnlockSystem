// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FFXSkillTree : ModuleRules
{
	public FFXSkillTree(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "EditorScriptingUtilities", "EditorScriptingUtilities", "Blutility" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
		
		// Editor-only dependencies
		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(new string[] 
			{
				"EditorStyle"                // For editor UI styling
			});
		}
	}
}
