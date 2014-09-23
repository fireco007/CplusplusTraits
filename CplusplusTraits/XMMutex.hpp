#ifndef _XM_MUTEX_
#define _XM_MUTEX_

#ifdef _MSC_VER
#include <Windows.h>
#define mutexType CRITICAL_SECTION
#endif //_MSC_VER

#ifdef __GUNC__
#include <phtread.h>
#define mutexType pthread_mutex_t
#endif //__GUNC__

namespace excalibur
{
	template <typename T>
	struct XMMutex
	{
		T cs;
		XMMutex()
		{}

		~XMMutex()
		{}

		void lock()
		{}

		bool trylock()
		{}

		void unlock()
		{}
	};

#ifdef _MSC_VER
	template <>
	struct XMMutex<CRITICAL_SECTION>
	{
		CRITICAL_SECTION cs;
		XMMutex()
		{
			InitializeCriticalSection(&cs);
		}

		~XMMutex()
		{
			DeleteCriticalSection(&cs);
		}

		void lock()
		{
			EnterCriticalSection(&cs);
		}

		bool trylock()
		{
			return TryEnterCriticalSection(&cs);
		}

		void unlock()
		{
			LeaveCriticalSection(&cs);
		}
	};
#endif //_MSC_VER

#ifdef __GUNC__
	template <>
	struct XMMutex<pthread_mutex_t>
	{
		pthread_mutex_t cs;
		XMMutex()
		{
			pthread_mutex_init(&cs, NULL);
		}

		~XMMutex()
		{
			pthread_mutex_destroy(&cs);
		}

		void lock()
		{
			pthread_mutex_lock(&cs);
		}

		bool trylock()
		{
			if (pthread_mutex_trylock(&cs) == 0)
				return true;

			return false;
		}

		void unlock()
		{
			pthread_mutex_unlock(&cs);
		}
	};
#endif //__GUNC__

}

#endif //_XM_MUTEX_
