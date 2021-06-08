/*
*	Provides basic interface for extended 
*	integer arithmetics 
*/

#pragma once 
#include <iostream>
#include <type_traits>
#include <cstring>

#if defined _M_IX86 || defined _M_X64 ||	\
	defined __i386__ 

#ifndef __X86_64__
#define __X86_64__
#endif 

#endif 

#if defined __X86_64__

#define INT128_MAX		
#define INT128_MIN		0
#define INT512_MAX		0
#define INT512_MIN		0
#define INT1024_MAX		0
#define INT1024_MIN		0

#define UINT128_MAX		0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
#define UINT128_MIN		0
#define UINT512_MAX		0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF \
						  FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
#define UINT512_MIN		0
#define UINT1024_MAX	0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF \
						  FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF \
						  FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF \
						  FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
#define UINT1024_MIN	0

/*  
	ISIGNED - used as template argument with signed number
	IUNSIGNED - used as template argument with unsigned number
*/
#define ISIGNED			char 
#define IUNSIGNED		unsigned char

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

		__basic_int& operator++();
		__basic_int& operator++(int);

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

		friend std::ostream& operator<<	<T, size>(std::ostream& os, const self_type& op1);
		friend std::istream& operator>>	<T, size>(std::istream& os, const self_type& op1);

	private:
		template <typename V>
		inline void copy_from(const V& rhs);

		void print_binary() const;

		T m_data[size];
};

//signed integer templates
using int128_t = __basic_int<ISIGNED, 128>;
using int512_t = __basic_int<ISIGNED, 512>;
using int1024_t = __basic_int<ISIGNED, 1024>;

//unsigned integer templates
using uint128_t = __basic_int<IUNSIGNED, 128>;
using uint512_t = __basic_int<IUNSIGNED, 512>;
using uint1024_t = __basic_int<IUNSIGNED, 1024>;


template <typename T, size_t size>
template <typename V>
__basic_int<T, size>::__basic_int(const V& lhs)
{
	static_assert(std::is_integral_v<std::remove_all_extents_t<V>>,
		"__basic_int: constructor template parameter must be an integral type");

	std::memset(static_cast<void*>(&m_data), 0, size / 8);
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
	op1.print_binary();
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
bool operator< <T, size>(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2)
{	
	bool is_equal = true;
	for (size_t i = 0; i < size; i++)
	{
		if (op1.m_data[i] > op2.m_data[i])
			return false;
		if (op1.m_data[i] != op2.m_data[i])
			is_equal = false;
	}

	/* 
		The main purpose of the following statement is to 
		eliminate number equality. If the precedence loop
		not returned from the function, two scenarios are possible.
		The first one is when the number op1 is not great that op2, 
		and the second when op1 == op2. In order to exclude such 
		drawback what we need is just track the number equality
		throughout the loop. If each pair of the loop were 
		equal, than return false, otherwise true.
	*/

	return !is_equal;
}


template <typename T, size_t size>
bool operator> <T, size>(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2)
{
	return !operator<(op1, op2) && !operator==(op1, op2);
}


template <typename T, size_t size>
bool operator<= <T, size>(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2)
{
	return (operator<(op1, op2) && !operator>(op1, op2));
}


template <typename T, size_t size>
bool operator>= <T, size>(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2)
{
	return (operator>(op1, op2) && !operator<(op1, op2));
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
inline void __basic_int<T, size>::copy_from(const V& lhs)
{
	size_t sz = sizeof(lhs) > size ? size : sizeof(lhs);
	std::memcpy(static_cast<void*>(&m_data), &lhs, sz);
}


template <typename T, size_t size>
void __basic_int<T, size>::print_binary() const
{
	char* bbyte;
	for (size_t i = size / 8; i > 0; i--)
	{
		bbyte = ((char*)m_data) + i - 1;
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


/*		Experimental feature		*/	
namespace ext_int
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
};

#endif