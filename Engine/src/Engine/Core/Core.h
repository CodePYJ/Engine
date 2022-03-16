#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS
#ifdef EE_DYNAMIC_LINK
	#ifdef ENGINE_BUILD_DLL
	#define EE_API __declspec(dllexport)
	#else
	#define EE_API __declspec(dllimport)
	#endif // ENGINE_BUILD_DLL
#else
	#define EE_API
#endif // EE_DYNAMIC_LINK

#endif // !ENGINE_PLATFORM_WINDOWS

#define ENGINE_ENABLE_ASSERTS

#ifdef ENGINE_ENABLE_ASSERTS
	#define EE_ASSERT(x, ...) { if(!(x)) { EE_ERROR( __VA_ARGS__); __debugbreak(); } }
	#define EE_CORE_ASSERT(x, ...) { if(!(x)) { EE_CORE_ERROR( __VA_ARGS__); __debugbreak(); } }
#else
	#define EE_ASSERT(x, ...)
	#define EE_CORE_ASSERT(x, ...)
#endif

