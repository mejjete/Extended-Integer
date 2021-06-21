/*
*	Provides basic interface for extended 
*	integer arithmetics 
*/

#pragma once 
#include <iostream>
#include <type_traits>
#include <cstring>
#include <cstdint>

#if defined _M_IX86 || defined _M_X64 ||	\
	defined __i386__ 

#ifndef __X86_64__
#define __X86_64__
#endif 

#endif 

#if defined __X86_64__

#define INT128_MAX		0
#define INT128_MIN		0
#define INT512_MAX		0
#define INT512_MIN		0
#define INT1024_MAX		0
#define INT1024_MIN		0

#define UINT128_MAX		0
#define UINT128_MIN		0
#define UINT512_MAX		0

#define UINT512_MIN		0
#define UINT1024_MAX	0
#define UINT1024_MIN	0

/*  
	ISIGNED - used as template argument with signed number
	IUNSIGNED - used as template argument with unsigned number
*/
#define ISIGNED			int8_t
#define IUNSIGNED		uint8_t

//convert number to hexademical
#define CVT_HEX(T) char(((T) <= 9) ? (T) | 0x30 : (((T) | 0x40) - 9))
#define CVT_ASCII(T) char((T) | 0x30)

//ASM function declaration
extern "C" void addInteger(void* fnum, void* snum, void* result, size_t size);
extern "C" void subInteger(void* fnum, void* snum, void* result, size_t size);

//forward declaration
template <typename T, size_t size>
class __basic_int;

/* 
 *	Friends forward declaration 
*/


/*		Arithmetic operations		*/
template <typename T, size_t size>
__basic_int<T, size> operator+(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2);

template <typename T, size_t size>
__basic_int<T, size> operator-(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2);

template <typename T, size_t size>
__basic_int<T, size> operator*(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2);

template <typename T, size_t size>
__basic_int<T, size> operator/(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2);

template <typename T, size_t size>
__basic_int<T, size> operator%(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2);


/*		Boolean operations		*/
template <typename T, size_t size>
bool operator==(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2);

template <typename T, size_t size>
bool operator!=(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2);

template <typename T, size_t size>
bool operator<(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2);

template <typename T, size_t size>
bool operator>(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2);

template <typename T, size_t size>
bool operator<=(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2);

template <typename T, size_t size>
bool operator>=(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2);



/*		Standard output operations		*/	
template <typename T, size_t size>
std::ostream& operator<<(std::ostream& os, const __basic_int<T, size>& op1);

template <typename T, size_t size>
std::istream& operator>>(std::istream& os, const __basic_int<T, size>& op1);



/* 
 *		Base class for integer arbitrary size
*/
template <typename T, size_t size>
class __basic_int
{
	static_assert(std::is_integral<T>::value,
		"__basic_int: T must be an integral type");

	public:
		using self_type = __basic_int<T, size>;

		__basic_int() = default;

		template <typename V>
		__basic_int(const V& rhs);

		__basic_int(const self_type& op) = default;
		__basic_int(self_type&& op) = default;

		__basic_int& operator=(const self_type& op) = default;
		__basic_int& operator=(self_type&& op) = default;

		template <typename V>
		__basic_int& operator=(const V& lhs);

		__basic_int& operator++()		{ return *this = operator+(*this, self_type(1)); };
		__basic_int& operator++(int)	{ return operator++(); };

		__basic_int& operator--()		{ return *this = operator-(*this, self_type(1)); };
		__basic_int& operator--(int)	{ return operator--(); };

		__basic_int& operator+=(const self_type& op) { return *this = operator+(*this, op); };
		__basic_int& operator-=(const self_type& op) { return *this = operator-(*this, op); };
		__basic_int& operator*=(const self_type& op) { return *this = operator*(*this, op); };
		__basic_int& operator/=(const self_type& op) { return *this = operator/(*this, op); };

		template <typename V>
		operator V() const;

		operator int() const;

		friend bool operator==	<T, size>(const self_type& op1, const self_type& op2);
		friend bool operator!=	<T, size>(const self_type& op1, const self_type& op2);

		friend bool operator< <T, size>(const self_type& op1, const self_type& op2);
		friend bool operator> <T, size>(const self_type& op1, const self_type& op2);
		friend bool operator<= <T, size>(const self_type& op1, const self_type& op2);
		friend bool operator<= <T, size>(const self_type& op1, const self_type& op2);

		friend self_type operator+	<T, size>(const self_type& op1, const self_type& op2);
		friend self_type operator-	<T, size>(const self_type& op1, const self_type& op2);
		friend self_type operator*	<T, size>(const self_type& op1, const self_type& op2);
		friend self_type operator/	<T, size>(const self_type& op1, const self_type& op2);
		friend self_type operator% <T, size>(const self_type& op1, const self_type& op2);

		friend std::ostream& operator<<	<T, size>(std::ostream& os, const self_type& op1);
		friend std::istream& operator>>	<T, size>(std::istream& os, const self_type& op1);

	private:
		template <typename V>
		inline void copy_from(const V& rhs);

		T m_data[size];
};


//signed integer templates
using int128_t = __basic_int<ISIGNED, 16>;
using int512_t = __basic_int<ISIGNED, 32>;
using int1024_t = __basic_int<ISIGNED, 64>;

//unsigned integer templates
using uint128_t = __basic_int<IUNSIGNED, 16>;
using uint512_t = __basic_int<IUNSIGNED, 32>;
using uint1024_t = __basic_int<IUNSIGNED, 64>;


template <typename T, size_t size>
template <typename V>
__basic_int<T, size>::__basic_int(const V& lhs)
{
	static_assert(std::is_integral_v<std::remove_all_extents_t<V>>,
		"__basic_int: constructor template parameter must be an integral type");

	int sign = lhs < 0 ? -1 : 0;
	std::memset(static_cast<void*>(&m_data), sign, size);
	copy_from(lhs);
};


template <typename T, size_t size>
template <typename V>
__basic_int<T, size>& __basic_int<T, size>::operator=(const V& lhs)
{
	static_assert(std::is_integral_v<std::remove_all_extents_t<V>>,
		"__basic_int: constructor template parameter must be an integral type");

	copy_from(lhs);
	return *this;
};


template <typename T, size_t size>
std::ostream& operator<< <T, size>(std::ostream& os, const __basic_int<T, size>& op1)
{
	std::string number;
	__basic_int<T, size> result = op1;
	while (result > 0)
	{
		number += CVT_ASCII(unsigned(result % 10));
		result /= 10;
	}
	std::reverse(number.begin(), number.end());
	os << number;
	return os;
}


template <typename T, size_t size>
__basic_int<T, size> operator+<T, size>(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2)
{
	void *fnum = (void*)op1.m_data;
	void* snum = (void*)op2.m_data;
	T result[size];
	std::memset(result, 0, sizeof(size));
	addInteger(fnum, snum, (void*)result, size);
	return __basic_int<T, size>(result);
};


template <typename T, size_t size>
__basic_int<T, size> operator-<T, size>(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2)
{
	void* fnum = (void*)op1.m_data;
	void* snum = (void*)op2.m_data;
	T result[size];
	std::memset(result, 0, sizeof(size));
	subInteger(fnum, snum, (void*)result, size);
	return __basic_int<T, size>(result);
};


template <typename T, size_t size>
__basic_int<T, size> operator*<T, size>(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2)
{
	__basic_int<T, size> result = 0;
	for (__basic_int<T, size> i = 0; i < op2; i++)
		result += op1;
	return result;
};


template <typename T, size_t size>
__basic_int<T, size> operator/<T, size>(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2)
{
	__basic_int<T, size> temp = op1;
	__basic_int<T, size> result = 0;

	while (temp != 0 && temp >= op2)
	{
		temp -= op2;
		result++;
	}
	return result;
};


template <typename T, size_t size>
__basic_int<T, size> operator%<T, size>(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2)
{
	__basic_int<T, size> result = op1;
	while (result >= op2)
		result -= op2;
	return result;
};


template <typename T, size_t size>
bool operator< <T, size>(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2)
{	
	bool is_second_great = false;
	
	using stype = IUNSIGNED;

	/*
		Sign bit check allows us to skip
		unnecessary loop iterations
		If they are equal - do the bitwise comparison
	*/
	stype first = (op1.m_data[size - 1] & 0x80);
	stype second = (op2.m_data[size - 1] & 0x80);

	if (first != second)
	{
		if (first > second)
			return true;
		return false;
	}

	//Bitwise comparison
	for (size_t i = size; i > 0; i--)
	{
		//to avoid sign bit extension
		first = op1.m_data[i - 1];
		second = op2.m_data[i - 1];

		if (first > second)
			return is_second_great;
		if (second > first)
			is_second_great = true;
	}

	/* 
		The main purpose of the following statement is to 
		eliminate number equality. If the precedence loop
		not returned from the function, two scenarios are possible.
		The first one is when the number op1 is not great that op2, 
		and the second when op1 == op2. In order to exclude such 
		drawback we need nothing but track the number equality
		throughout the loop. If each pair of number throughout 
		the loop were equal, return false, otherwise true.
	*/

	return is_second_great;
}


template <typename T, size_t size>
bool operator> <T, size>(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2)
{
	return !operator<(op1, op2) && !operator==(op1, op2);
}


template <typename T, size_t size>
bool operator<= <T, size>(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2)
{
	return (operator<(op1, op2) || operator==(op1, op2));
}


template <typename T, size_t size>
bool operator>= <T, size>(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2)
{
	return (operator>(op1, op2) || operator==(op1, op2));
}


template <typename T, size_t size>
bool operator== <T, size>(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2)
{
	for (size_t i = 0; i < size; i++)
	{
		if (op1.m_data[i] != op2.m_data[i])
			return false;
	}
	return true;
};


template <typename T, size_t size>
bool operator!= <T, size>(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2)
{
	return !operator==(op1, op2);
}


template <typename T, size_t size>
template <typename V>
__basic_int<T, size>::operator V() const
{
	static_assert(std::is_integral_v<std::remove_all_extents_t<V>>,
		"__basic_int: operator overloading template parameter must be an integral type");
	
	V result;
	std::memcpy(&result, static_cast<const void*>(&m_data), sizeof(V));
	return result;
}


template <typename T, size_t size>
template <typename V, size_t sz>
__basic_int<T, size>::operator __basic_int<V, sz>() const
{
	/*static_assert(false, "NOT YET IMPLEMENTED");*/
	std::cerr << "not implemented\n";
	return __basic_int<V, sz>(0);
}


template <typename T, size_t size>
inline __basic_int<T, size>::operator int() const
{
	int result;
	std::memcpy(&result, static_cast<const void*>(&m_data), sizeof(int));
	return result;
}


template <typename T, size_t size>
template <typename V>
inline void __basic_int<T, size>::copy_from(const V& lhs)
{
	size_t sz = sizeof(lhs) > size ? size : sizeof(lhs);
	std::memcpy(static_cast<void*>(&m_data), &lhs, sz);
}


/*		Experimental feature		*/	
namespace eint
{
	/*		Extended integer type traits		*/
	template <typename>
	struct is_signed : public std::false_type {};

	template <size_t size>
	struct is_signed<__basic_int<ISIGNED, size>> : public std::true_type {};

	template <typename>
	struct is_unsigned : public std::false_type {};

	template <size_t size>
	struct is_unsigned<__basic_int<IUNSIGNED, size>> : public std::true_type {};

	template <typename T>
	void toBin(const T& num)
	{
		static_assert(std::is_integral_v<std::remove_all_extents_t<T>>,
			"only numbers can be converted into hexademical representation");

		char* bbyte;
		for (size_t i = sizeof(T); i > 0; i--)
		{
			bbyte = ((char*)&num) + i - 1;
			for (int j = 8; j > 0; j--)
			{
				std::cout << ((*bbyte >> j - 1) & 1);
				if ((j - 1) % 4 == 0)
					std::cout << " ";
			}

			if ((i - 1) % 4 == 0)
				std::cout << std::endl;
		};
	};

	template <typename T>
	void toHex(const T& num)
	{
		static_assert(std::is_integral_v<std::remove_all_extents_t<T>>,
			"only numbers can be converted into hexademical representation");

		string result;

		for (int i = sizeof(num); i > 0; i--)
		{
			unsigned char temp = *(((unsigned char*)&num) + i - 1);
			result += CVT_HEX(temp >> 4);
			result += CVT_HEX(temp & 0xF);
		};
		std::cout << result << endl;
	};
};

#endif