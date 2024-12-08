#pragma once
#include <iostream>

using namespace std;
class Product
{
public:
	virtual void printSummary() = 0;
	virtual ostream& operator << (ostream& out) = 0;
};

