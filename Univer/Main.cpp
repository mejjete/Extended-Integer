#include <iostream>
#include <fstream>
#include "basic_int.h"
using namespace std;

void print_binary(void* fnum, size_t size)
{
	char *bbyte;
	for (size_t i = 0; i < size / 8; i++)
	{
		bbyte = ((char*)fnum) + i * 8;
	};
};

int main()
{
	int128_t cl;
	//int128_t gh;

	

	return 0;
};