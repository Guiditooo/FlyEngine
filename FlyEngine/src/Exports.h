#pragma once

#ifdef FLY_EXPORTS
	#define FLY_API __declspec(dllexport)
#else
	#define FLY_API __declspec(dllimport)
#endif