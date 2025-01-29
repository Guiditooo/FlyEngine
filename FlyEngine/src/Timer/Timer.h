#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <set>

#include "Exports/Exports.h"

namespace FlyEngine
{
	class FLY_API Timer
	{
	private:
		static double deltaTime;
		static double totalTime;
		static double windowTime;
		static bool printMessages;

		static std::chrono::high_resolution_clock::time_point lastFrameTime;
		static std::chrono::high_resolution_clock::time_point startTime;
		static std::chrono::high_resolution_clock::time_point windowStartTime;

	public:
		enum TimerOption 
		{
			Delta,
			Total,
			Window
		};

		static void InitTimer(std::initializer_list<TimerOption> options = {});
		static void UpdateTimer();
		static void ResetTimer(std::initializer_list<TimerOption> options = {});
		static double DeltaTime();
		static double TotalTime();
		static double WindowTime();

		static void EnablePrintMessages(bool value);
	};
}

#endif // !TIMER_H