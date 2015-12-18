// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.


namespace UnrealBuildTool.Rules
{
	public class CafeSDKPlugin : ModuleRules
	{
		
		public CafeSDKPlugin (TargetInfo Target)
		{
			
			PublicIncludePaths.AddRange(
				new string[] {
				"CafeSDKPlugin/Public"
					// ... add public include paths required here ...
			}
			);
			
			
			PrivateIncludePaths.AddRange(
				new string[] {
				"CafeSDKPlugin/Private"
					// ... add other private include paths required here ...
			}
			);
			PublicDependencyModuleNames.AddRange(
				new string[]
				{
				"Engine",
				"Core",
				"CoreUObject",
				"Slate",
				"SlateCore",
				"UMG"
			}
			);
		}
	}
}
//// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
//
//using UnrealBuildTool;
//
//public class CafeSDKPlugin : ModuleRules
//{
//	public CafeSDKPlugin(TargetInfo Target)
//	{
//		
//		PublicIncludePaths.AddRange(
//			new string[] {
//				"CafeSDKPlugin/Public"
//				// ... add public include paths required here ...
//			}
//			);
//				
//		
//		PrivateIncludePaths.AddRange(
//			new string[] {
//				"CafeSDKPlugin/Private",
//				// ... add other private include paths required here ...
//			}
//			);
//			
//		
//		PublicDependencyModuleNames.AddRange(
//			new string[]
//			{
//				"Core",
//				// ... add other public dependencies that you statically link with here ...
//			}
//			);
//			
//		
//		PrivateDependencyModuleNames.AddRange(
//			new string[]
//			{
//				"CoreUObject",
//				"Engine",
//				"Slate",
//				"SlateCore",
//				// ... add private dependencies that you statically link with here ...	
//			}
//			);
//		
//		
//		DynamicallyLoadedModuleNames.AddRange(
//			new string[]
//			{
//				// ... add any modules that your module loads dynamically here ...
//			}
//			);
//	}
//}