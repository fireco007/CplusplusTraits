#ifndef _XM_OBJECT_POOL_
#define _XM_OBJECT_POOL_

#include <list>

using namespace std;

//this class is not thread safe now
namespace excalibur {

	template<typename T, size_t initsize = 100, size_t expandsize = 50>
	class XMObjectPool
	{
	public:

		//without this keyword [typename] this cann't work in g++ 4.1.2
		//but OK in vs2013
		typedef typename list<T*>::iterator listite;

		XMObjectPool() : size(initsize)
		{
			T *ptr = new T[initsize];
			blockList.push_back(ptr);
			for (size_t i = 0; i < initsize; i++)
			{
				freeObjectList.push_back(ptr + i);
			}
			
		}

		~XMObjectPool()
		{
			listite ite = blockList.begin();
			for (ite; ite != blockList.end(); ++ite)
			{
				delete[] (*ite);
			}
		}

		T *getObject()
		{
			if (freeObjectList.empty())
			{
				expandPool();
			}

			T* tmptr = static_cast<T*>(*freeObjectList.begin());
			freeObjectList.pop_front();
			return tmptr;
		}

		void freeObject(T* ptr)
		{
			if (ptr == NULL)
				return;

			freeObjectList.push_back(ptr);
		}

		size_t totalSize()
		{
			return size;
		}

		size_t freeSize()
		{
			return freeObjectList.size();
		}

	private:
		void expandPool()
		{
			T *ptr = new T[expandsize];
			blockList.push_back(ptr);
			for (size_t i = 0; i < expandsize; i++)
			{
				freeObjectList.push_back(ptr + i);
			}
			size += expandsize;
		}

	private:
		list<T*> freeObjectList;
		list<T*> blockList;
		size_t size;
	};

}

#endif //_XM_OBJECT_POOL_
