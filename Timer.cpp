#include "Timer.h"

#include <ctime>
#include <thread>

namespace Bear
{
	static TimerUInt&& maxThreads = std::thread::hardware_concurrency();
	static TimerUInt&& usingThreads = 1;

	static void TimerFunction(const TimerUInt& time, const bool* stop, void(*CallbackFunction)(), const Timer::Duration& duration)
	{
		while (!(*stop))
		{
			switch (duration)
			{
				case Timer::Duration::Nanoseconds:
				{
					std::this_thread::sleep_for((std::chrono::nanoseconds)time);
					break;
				}
				case Timer::Duration::Microseconds:
				{
					std::this_thread::sleep_for((std::chrono::microseconds)time);
					break;
				}
				case Timer::Duration::Milliseconds:
				{
					std::this_thread::sleep_for((std::chrono::milliseconds)time);
					break;
				}
				case Timer::Duration::Seconds:
				{
					std::this_thread::sleep_for((std::chrono::seconds)time);
					break;
				}
				case Timer::Duration::Minutes:
				{
					std::this_thread::sleep_for((std::chrono::minutes)time);
					break;
				}
				case Timer::Duration::Hours:
				{
					std::this_thread::sleep_for((std::chrono::hours)time);
					break;
				}
				default:
					break;
			}

			CallbackFunction();
		}
	}

	Timer::Timer()
	{
		start = std::clock();
	}

	Timer::Timer(const TimerUInt& time, void(*Callback)(), const Duration& duration)
	{
		if (usingThreads >= maxThreads)
			throw ("Can't create new timer in other thread");

		stop = new bool(false);

		start = std::clock();

		thread = new std::thread(TimerFunction, time, stop, Callback, duration);
	}

	Timer::~Timer()
	{
		if (thread)
		{
			if (((std::thread*)thread)->joinable())
			{
				((std::thread*)thread)->join();
				delete thread;
				delete stop;
			}
		}
	}

	void Timer::Stop() const
	{
		if(stop)
			*stop = true;
	}

	const TimerDouble Timer::GetTime() const
	{
		return ((std::clock() - start) / CLOCKS_PER_SEC);
	}
}