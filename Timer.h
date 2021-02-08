#pragma once

namespace Bear
{
	typedef double TimerDouble;

	#ifdef _WIN64
		typedef unsigned long long int TimerUInt;
	#elif _WIN32
		typedef unsigned int TimerUInt;
	#endif

	class Timer
	{
	private:
		TimerDouble start;

		void* thread;
		bool* stop;
	public:
		enum class Duration
		{
			Nanoseconds,
			Microseconds,
			Milliseconds,
			Seconds,
			Minutes,
			Hours
		};
	public:
		Timer();
		Timer(const TimerUInt& Time, void(*Callback)(), const Duration& duration = Duration::Milliseconds);
		~Timer();
	public:
		void Stop() const;

		const TimerDouble GetTime() const;
	};
}