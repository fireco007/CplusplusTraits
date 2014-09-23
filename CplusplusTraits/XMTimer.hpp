#ifndef _XM_TIMER_
#define _XM_TIMER_


#ifdef _MSC_VER
#include <Windows.h>
#define timerType LARGE_INTEGER
#endif //_MSC_VER

#ifdef __GNUC__
#include <time.h>
#define timerType timeval
#endif //__GNUC__

namespace excalibur
{
	template <typename T>
	struct XMTimer
	{
		static T Now()
		{
			return static_cast<long>(0);
		}

		static long timeDelay(T before, T after)
		{
			return static_cast<long>(0);
		}

		static long timeShiftToNow(T before)
		{
			return static_cast<long>(0);
		}
	};

#ifdef _MSC_VER
	//we can use GetTickCount() to replace QueryPerformanceCounter()
	template <>
	struct XMTimer<LARGE_INTEGER>
	{
		static LARGE_INTEGER Now()
		{
			LARGE_INTEGER t;
			QueryPerformanceCounter(&t);

			return t;
		}

		static long timeDelay(LARGE_INTEGER before, LARGE_INTEGER after)
		{
			LARGE_INTEGER freq;
			QueryPerformanceFrequency(&freq);

			return static_cast<long>((after.QuadPart - before.QuadPart) * 1000 / freq.QuadPart);
		}

		static long timeShiftToNow(LARGE_INTEGER before)
		{
			LARGE_INTEGER t;
			QueryPerformanceCounter(&t);

			LARGE_INTEGER freq;
			QueryPerformanceFrequency(&freq);


			return static_cast<long>((t.QuadPart - before.QuadPart) * 1000 / freq.QuadPart);
		}
	};
#endif //_MSC_VER

#ifdef __GNUC__
	template <>
	struct XMTimer<timeval>
	{
		static timeval Now()
		{
			struct timeval t;
			gettimeofday(&t, NULL);
			return t;
		}

		static long timeDelay(timeval before, timeval after)
		{
			long afterTime = after.tv_sec * 1000 * 1000 + after.tv_usec;
			long beforeTime = before.tv_sec * 1000 * 1000 + before.tv_usec;
			return (afterTime - beforeTime) / 1000;
		}

		static long timeShiftToNow(timeval before)
		{
			struct timeval t;
			gettimeofday(&t, NULL);
			long afterTime = t.tv_sec * 1000 * 1000 + t.tv_usec;
			long beforeTime = before.tv_sec * 1000 * 1000 + before.tv_usec;
			return (afterTime - beforeTime) / 1000;
		}
	};
#endif //__GNUC__

}

#endif //_XM_TIMER_
