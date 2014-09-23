#include <iostream>

/*
int a = std::numeric_limits<int>::max();
namespace detail{

	template <bool b>
	struct copier
	{
		template<typename I1, typename I2>
		static I2 do_copy(I1 first, I1 last, I2 out);
	};

	template <bool b>
	template<typename I1, typename I2>
	I2 copier<b>::do_copy(I1 first, I1 last, I2 out)
	{
		while (first != last)
		{
			*out = *first;
			++out;
			++first;
		}
		return out;
	}

	template <>
	struct copier<true>
	{
		template<typename I1, typename I2>
		static I2* do_copy(I1* first, I1* last, I2* out)
		{
			memcpy(out, first, (last - first)*sizeof(I2));
			return out + (last - first);
		}
	};
}

template<typename I1, typename I2>
inline I2 copy(I1 first, I1 last, I2 out)
{
	typedef typename
		boost::remove_cv<
		typename std::iterator_traits<I1>
		::value_type>::type v1_t;
	typedef typename
		boost::remove_cv<
		typename std::iterator_traits<I2>
		::value_type>::type v2_t;
	enum{
		can_opt =
		boost::is_same<v1_t, v2_t>::value
		&& boost::is_pointer<I1>::value
		&& boost::is_pointer<I2>::value
		&& boost::
		has_trivial_assign<v1_t>::value
	};
	return detail::copier<can_opt>::
		do_copy(first, last, out);
}*/

#include "XMObjectPool.hpp"
#include "XMTimer.hpp"

/*
template <typename T>
struct is_void
{
	static const bool value = false;
};

template <>
struct is_void<void>
{
	static const bool value = true;
};*/

int main(void)
{
	//std::cout << is_void<int>::value << std::endl;
	//std::cout << is_void<void>::value << std::endl;


	excalibur::XMObjectPool<char, 1000, 100> charPool;
	excalibur::XMTimer<timerType> timer;

	//excalibur::XMObjectPool<char, 1000, 10> charPool2;

	timerType before = timer.Now();
	char *ch = NULL;
	for (int i = 0; i < 1000000; i++) {
		charPool.getObject();
	}

	std::cout << "size : " << charPool.totalSize() << "\ttime cose : " 
		<< timer.timeShiftToNow(before) << std::endl;

	int elemCount = charPool.totalSize();
	before = timer.Now();
	for (int i = 0; i < elemCount; i++) {
		new char();
	}

	std::cout << "size : " << charPool.totalSize() << "\ttime cose : "
		<< timer.timeShiftToNow(before) << std::endl;

	//charPool.freeObject(ch);

	ch = charPool.getObject();

	std::cout << "size : " << charPool.totalSize() << std::endl;

	getchar();

	return 0;
}
