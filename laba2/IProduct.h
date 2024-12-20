#pragma once
#include <iostream>

using namespace std;

template<typename T>
class IProduct
{
public:
	virtual void printSummary() const = 0;
	virtual void updateCurrentData(T newPrice, int newProductQuantity)  = 0;
	virtual void CoutRating() const = 0;
	virtual double operator[](int MonitoringDay) const = 0;
	virtual void printSummary(int MonitoringDay) const = 0;

	virtual ~IProduct() {}
};
template<typename T>
ostream& operator << (ostream& out, const IProduct<T>& ourObject);


