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

#define __X86_64__
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
#define ISIGNED			char 
#define IUNSIGNED		unsigned char

//ASM function declaration
extern "C" void addInteger(void* fnum, void* snum, void* result, size_t size);
extern "C" void subInteger(void* fnum, void* snum, void* result, size_t size);
extern "C" void mulInteger(void* fnum, void* snum, void* result, size_t size);
extern "C" void divInteger(void* fnum, void* snum, void* result, size_t size);

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
bool operator==(const __basic_int<T, size>& op1, const __basic_int<T, size>& op);

template <typename T, size_t size>
bool operator!=(const __basic_int<T, size>& op1, const __basic_int<T, size>& op);

template <typename T, size_t size>
inline bool operator<(const __basic_int<T, size>& op1, const __basic_int<T, size>& op);

template <typename T, size_t size>
inline bool operator>(const __basic_int<T, size>& op1, const __basic_int<T, size>& op);

template <typename T, size_t size>
inline bool operator<=(const __basic_int<T, size>& op1, const __basic_int<T, size>& op);

template <typename T, size_t size>
inline bool operator>=(const __basic_int<T, size>& op1, const __basic_int<T, size>& op);



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
		"T must be an integral type");
	static_assert(!std::is_floating_point<T>::value,
		"T must be non-floating point type");

	public:
		using self_type = __basic_int<T, size>;

		__basic_int() = default;
		__basic_int(const self_type& op) = default;
		__basic_int(self_type&& op) = default;

		__basic_int& operator=(const self_type& op);
		__basic_int& operator=(self_type&& op);

		template <typename T>
		__basic_int& operator=(const T& item);

		__basic_int& operator++();
		__basic_int& operator++(int);

		friend bool operator==	<T, size>(const self_type& op1, const self_type& op);
		friend bool operator!=	<T, size>(const self_type& op1, const self_type& op);

		friend inline bool operator<(const self_type& op1, const self_type& op);
		friend inline bool operator>(const self_type& op1, const self_type& op);
		friend inline bool operator<=(const self_type& op1, const self_type& op);
		friend inline bool operator<=(const self_type& op1, const self_type& op);

		friend self_type operator+	<T, size>(const self_type& op1, const self_type& op2);
		friend self_type operator-	<T, size>(const self_type& op1, const self_type& op2);
		friend self_type operator*	<T, size>(const self_type& op1, const self_type& op2);
		friend self_type operator/	<T, size>(const self_type& op1, const self_type& op2);

		friend std::ostream& operator<<	<T, size>(std::ostream& os, const self_type& op1);
		friend std::istream& operator>>	<T, size>(std::istream& os, const self_type& op1);

		void print_binary();
	private:
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
std::ostream& operator<< <T, size>(std::ostream& os, const __basic_int<T, size>& op1)
{
	for (int i = 0; i < size; i++)
	{
		os << (int)op1.m_data[i];
		os << " ";
	}
	return os;
}

template <typename T, size_t size>
__basic_int<T, size> operator+<T, size>(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2)
{
	std::cout << "+" << std::endl;
	return __basic_int<T, size>();
};

template <typename T, size_t size>
__basic_int<T, size> operator-<T, size>(const __basic_int<T, size>& op1, const __basic_int<T, size>& op2)
{
	std::cout << "-" << std::endl;
	return __basic_int<T, size>();
};

template <typename T, size_t size>
void __basic_int<T, size>::print_binary()
{
	for (size_t i = 0; i < size; i++)
	{
		if ((i + 1) % 32 == 0)
		{
			std::cout << std::endl;
			continue;
		}
	};
};

/*Experimental feature*/	
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