#include "Timer.h"

#include "FlyFunctions/Debugger/Debugger.h"

namespace FlyEngine
{
	double Timer::deltaTime = 0.0;
	double Timer::totalTime = 0.0;
	double Timer::windowTime = 0.0;

	std::chrono::high_resolution_clock::time_point Timer::lastFrameTime;
	std::chrono::high_resolution_clock::time_point Timer::startTime;
	std::chrono::high_resolution_clock::time_point Timer::windowStartTime;

	bool Timer::printMessages = true;

	void Timer::InitTimer(std::initializer_list<TimerOption> options)
	{
		auto now = std::chrono::high_resolution_clock::now();

		startTime = now;
		lastFrameTime = now;
		windowStartTime = now;

		std::set<TimerOption> specifiedOptions(options);

		if (specifiedOptions.count(Delta) || specifiedOptions.empty())
		{
			deltaTime = 0.0;
			if (printMessages)
				Utils::Debugger::ConsoleMessage("Delta time Initialized");
		}

		if (specifiedOptions.count(Total) || specifiedOptions.empty())
		{
			totalTime = 0.0;
			if (printMessages)
				Utils::Debugger::ConsoleMessage("Total time Initialized");
		}

		if (specifiedOptions.count(Window) || specifiedOptions.empty())
		{
			windowTime = 0.0;
			if (printMessages)
				Utils::Debugger::ConsoleMessage("Window time Initialized");
		}
	}

	void FlyEngine::Timer::UpdateTimer()
	{
		auto now = std::chrono::high_resolution_clock::now();

		deltaTime = std::chrono::duration<double>(now - lastFrameTime).count();
		totalTime = std::chrono::duration<double>(now - startTime).count();
		windowTime = std::chrono::duration<double>(now - windowStartTime).count();

		lastFrameTime = now;

		/*
		if (printMessages)
		{
			Utils::Debugger::ConsoleMessage("Delta time Updated", deltaTime);
			Utils::Debugger::ConsoleMessage("Total time Updated", totalTime);
			Utils::Debugger::ConsoleMessage("Window time Updated", windowTime);
		}
		*/
	}

	void Timer::ResetTimer(std::initializer_list<TimerOption> options)
	{
		std::set<TimerOption> specifiedOptions(options);

		if (specifiedOptions.count(Delta))
		{
			deltaTime = 0.0;
			if (printMessages)
				Utils::Debugger::ConsoleMessage("Delta timer Reseted");
		}

		if (specifiedOptions.count(Total))
		{
			totalTime = 0.0;
			if (printMessages)
				Utils::Debugger::ConsoleMessage("Total timer Reseted");
		}

		if (specifiedOptions.count(Window))
		{
			windowTime = 0.0;
			if (printMessages)
				Utils::Debugger::ConsoleMessage("Window timer Reseted");
		}

		if (specifiedOptions.empty())
		{
			deltaTime = 0.0;
			totalTime = 0.0;
			windowTime = 0.0;
			if (printMessages)
				Utils::Debugger::ConsoleMessage("All timers Reseted");
		}
	}

	double Timer::DeltaTime()
	{
		return deltaTime;
	}

	double Timer::TotalTime()
	{
		return totalTime;
	}

	double Timer::WindowTime()
	{
		return windowTime;
	}

	void Timer::EnablePrintMessages(bool value)
	{
		printMessages = value;
	}
}