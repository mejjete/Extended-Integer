#include <iostream>
#include <fstream>
#include <climits>
#include <cstdlib>
#include <ctime>
#include "basic_int.h"
using namespace std;

void module_test();

int main()
{
	cout.setf(ios::boolalpha);
	int128_t val1 = 800;
	int128_t val2 = 333;

	module_test();

	return 0;
};


/*
//convert number to hexademical
#define CVT_HEX(T) char(((T) <= 9) ? (T) | 0x30 : (((T) | 0x40) - 9))

template <typename T>
const std::string toHex(const T& val)
{
	static_assert(std::is_integral_v<std::remove_all_extents_t<T>>,
		"only numbers can be converted into hexademical representation");

	string result;

	for (int i = sizeof(val); i > 0; i--)
	{
		unsigned char temp = *(((unsigned char*)&val) + i - 1);
		result += CVT_HEX(temp >> 4);
		result += CVT_HEX(temp & 0xF);
	};
	return result;
}
*/