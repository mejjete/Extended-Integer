#include <iostream>
#include <fstream>
#include <climits>
#include "basic_int.h"
using namespace std;

int main()
{
	cout.setf(ios::boolalpha);
	int128_t val1 = 5;
	int128_t val2 = 5;

	cout << int(val1 * val2) << endl;

#if defined _DEBUG
	{
		for (int i = 0; i < 10; i++)
		{
			int128_t temp = 5;
			int128_t ii = i;
			cout << "I = " << i << endl;

			cout << "operator<: ";
			cout << (ii < temp) << endl;
			
			cout << "operator>: ";
			cout << (ii > temp) << endl;

			cout << "operator<=: ";
			cout << (ii <= temp) << endl;

			cout << "operator>=: ";
			cout << (ii >= temp) << endl;
			system("pause");
		}
	}
#endif 

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