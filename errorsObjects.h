#pragma once

#include <stdexcept>
#include <string>
#include <iostream>

class InvalidIndexException : public std::logic_error
{
private:
	int index1, index2, index3, index4;

public:
	InvalidIndexException(int i1, int i2, int i3, int i4, std::string msg = "One of the indexes has invalid value, smaller than 0 or greater than 7\n")
		: index1(i1), index2(i2), index3(i3), index4(i4), std::logic_error(msg) {}
	void message()
	{
		using std::cout;
		using std::endl;
		cout << "Index values: " << endl;
		cout << "Index1 = " << index1 << "\t" << "Index2 = " << index2 << "\t" << "Index3 = " << index3 << "\t" << "Index4 = " << index4 << endl;
	}
};