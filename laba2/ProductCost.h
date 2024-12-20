#ifndef PRODUCTCOST_H
#define PRODUCTCOST_H
#include <iostream>
#include <string>
#include <vector>
#include <iomanip> 
#include "IProduct.h"

using namespace std;
template<typename T>
class ProductCost : public IProduct<T>
{
public:

	enum PriceTrend {
		STABLE,        // ���� ����������
		INCREASING,    // ���� ������
		DECREASING,    // ���� ������
		AT_MINIMUM,    // ���� �� ��������
		AT_MAXIMUM    // ���� �� ���������
	};
	PriceTrend getPriceTrend() const {
		double lastPrice = priceHistory[actualmonitoringDay - NUMBER_ONE];

		if (price == lastPrice)
		{
			return STABLE;
		}
		else if (price > lastPrice)
		{
			return INCREASING;
		}
		else if (price < lastPrice)
		{
			return DECREASING;
		}
		else if (price == minCost)
		{
			return AT_MINIMUM;
		}
		else if (price == maxCost)
		{
			return AT_MAXIMUM;
		}
		return STABLE;
	}

	ProductCost(const char* url, const unsigned int day, const unsigned int stock, T price);

	ProductCost(const char* url, const unsigned int productQuantity);

	~ProductCost();

	//����� �������
	bool isLowStock() const;

	void updateCurrentData(T newPrice, int newProductQuantity) override;
	void printSummary() const override;
	void printSummary(int MonitoringDay) const override;
	//���������
	unsigned int getProductQuantity() const;
	unsigned int getMonitoringDay() const;
	T getPrice() const;
	unsigned int getActualmonitoringDay() const;
	T getAverageCost() const;
	T getMaxCost() const;
	T getMinCost() const;

	virtual void CoutRating() const override { }

	double operator[](int MonitoringDay) const override;

	friend ostream& operator << (ostream& out, const ProductCost& ourObject);

protected:
	unsigned int actualmonitoringDay; // ������� ���� �����������;

private:
	// ����
	unsigned int productQuantity; // ������� ���������� ������;
	T price; //  ������� ���������;
	unsigned int monitoringDay; // ���������� ���� �����������;
	T averageCost = 0; // ������� ���������
	T maxCost; // ������������ ���������
	T minCost; // ����������� ���������
	static const int minProduct = 2;
	static const int URL_LENGTH = 256;
	char url[URL_LENGTH]; // URL
	static const int NUMBER_NULLIK = 0;
	static const int NUMBER_ONE = 1;
	vector<double> priceHistory;
	vector<int> monitoringDays; //��� �����������
	vector<int> productQuantityHistory;
};


//template<typename T>
//ProductCost<T>::PriceTrend ProductCost<T>::getPriceTrend() const
//{
//	double lastPrice = priceHistory[actualmonitoringDay - NUMBER_ONE];
//
//	if (price == lastPrice)
//	{
//		return STABLE;
//	}
//	else if (price > lastPrice)
//	{
//		return INCREASING;
//	}
//	else if (price < lastPrice)
//	{
//		return DECREASING;
//	}
//	else if (price == minCost)
//	{
//		return AT_MINIMUM;
//	}
//	else if (price == maxCost)
//	{
//		return AT_MAXIMUM;
//	}
//	return STABLE;
//}
template<typename T>
ProductCost<T>::ProductCost(const char* url, const unsigned int day, const unsigned int stock, T price)
	: productQuantity(stock), price(price), monitoringDay(day), actualmonitoringDay(0)
{
	if (monitoringDay <= NUMBER_NULLIK)
	{
		throw invalid_argument("��� ����������� �� ����� ���� ����� ���� ��� ���� ������ ����!!!");
	}
	if (price <= NUMBER_NULLIK)
	{
		throw invalid_argument("������� ��������� �� ����� ���� ����� ���� ��� ���� ������ ����!!!");
	}
	if (url == nullptr)
	{
		throw invalid_argument("������������ ������!!!");
	}
	strncpy_s(this->url, url, URL_LENGTH - NUMBER_ONE);
	this->url[URL_LENGTH - NUMBER_ONE] = '0';

	maxCost = price;
	minCost = price;
	priceHistory.push_back(price);
	monitoringDays.push_back(1);
	productQuantityHistory.push_back(stock);
}
template<typename T>
ProductCost<T>::ProductCost(const char* url, const unsigned int productQuantity)
{
	if (url == nullptr)
	{
		throw invalid_argument("������������ ������!!!");
	}
	strncpy_s(this->url, url, URL_LENGTH - NUMBER_ONE);
	this->url[URL_LENGTH - NUMBER_ONE] = '0';
}
template<typename T>
ProductCost<T>::~ProductCost()
{
	priceHistory.clear();
	priceHistory.shrink_to_fit();
	monitoringDays.clear();
	monitoringDays.shrink_to_fit();
}

template<typename T>
void ProductCost<T>::updateCurrentData(T newPrice, int newProductQuantity) {
	if (newProductQuantity < NUMBER_NULLIK)
	{
		throw invalid_argument("����� ������ �� ����� ���� �������������!!!");
	}
	if (newPrice < NUMBER_NULLIK)
	{
		throw invalid_argument("���� ������ �� ����� ���� �������������!!!");
	}

	productQuantity = newProductQuantity;

	price = newPrice;

	actualmonitoringDay++;

	priceHistory.push_back(newPrice);

	monitoringDays.push_back(actualmonitoringDay + NUMBER_ONE);

	productQuantityHistory.push_back(newProductQuantity);

	if (newPrice > maxCost)
	{
		maxCost = newPrice;
	}
	if (newPrice < minCost)
	{
		minCost = newPrice;
	}
	for (T price : priceHistory)
	{
		averageCost += price;
	}
	averageCost /= priceHistory.size();
}
template<typename T>
void ProductCost<T>::printSummary() const
{
	cout << url << endl;
	cout << "��� �����������: " << actualmonitoringDay + 1 << endl;
	cout << "������� ����: $" << fixed << setprecision(2) << price << endl;
	cout << "������� ���������� ������:  " << productQuantity << endl;
	cout << "������� ���: \n";
	if (priceHistory.size() != monitoringDays.size())
	{
		throw out_of_range("������ ������ 404");
	}
	for (int i = NUMBER_NULLIK; i < priceHistory.size(); ++i)
	{
		cout << monitoringDays[i] << ": " << priceHistory[i] << endl;
	}
	cout << endl;

	cout << "������� ����: $" << averageCost << endl;
	cout << "������������ ����: $" << maxCost << endl;
	cout << "����������� ����: $" << minCost << endl;


	switch (getPriceTrend())
	{
	case STABLE:
		cout << "��������� ������: ���������" << endl;
		break;
	case INCREASING:
		cout << "��������� ������: �����" << endl;
		break;
	case DECREASING:
		cout << "��������� ������: ������" << endl;
		break;
	case AT_MINIMUM:
		cout << "��������� ������: �� ��������" << endl;
		break;
	case AT_MAXIMUM:
		cout << "��������� ������: �� ���������" << endl;
		break;
	}
}
template<typename T>
void ProductCost<T>::printSummary(int MonitoringDay) const
{
	cout << url << endl;
	cout << "���� �����������: " << MonitoringDay << endl;
	for (int i = NUMBER_NULLIK; i < monitoringDays.size(); i++)
	{
		if (MonitoringDay == monitoringDays[i])
		{
			cout << "����: $" << priceHistory[i] << endl;
			cout << "���������� ������:  " << productQuantityHistory[i] << endl;
			break;
		}
	}
}

//���������
template<typename T>
inline unsigned int ProductCost<T>::getProductQuantity() const
{
	return productQuantity;
}
template<typename T>
inline unsigned int ProductCost<T>::getMonitoringDay() const
{
	return monitoringDay;
}
template<typename T>
T ProductCost<T>::getPrice() const
{
	return price;
}
template<typename T>
inline unsigned int ProductCost<T>::getActualmonitoringDay() const
{
	return actualmonitoringDay;
}
template<typename T>
T ProductCost<T>::getAverageCost() const
{
	return averageCost;
}
template<typename T>
T ProductCost<T>::getMaxCost() const
{
	return maxCost;
}
template<typename T>
T ProductCost<T>::getMinCost() const
{
	return minCost;
}
template<typename T>
bool ProductCost<T>::isLowStock() const
{
	if (productQuantity < minProduct)
	{
		return true;
	}
	else {
		return false;
	}
}
template<typename T>
double ProductCost<T>::operator[](int MonitoringDay) const
{
	double test = NUMBER_NULLIK;
	for (int i = NUMBER_NULLIK; i < monitoringDays.size(); i++)
	{
		if (MonitoringDay == monitoringDays[i])
		{
			return test = priceHistory[i];

		}
	}
};

template<typename T>
ostream& operator << (ostream& out, const ProductCost<T>& ourObject)
{
	out << ourObject.url << endl;
	out << "��� �����������: " << ourObject.actualmonitoringDay + 1 << endl;
	out << "������� ����: $" << fixed << setprecision(2) << ourObject.price << endl;
	out << "������� ���������� ������:  " << ourObject.productQuantity << endl;
	out << "������� ����: $" << ourObject.averageCost << endl;
	out << "������������ ����: $" << ourObject.maxCost << endl;
	out << "����������� ����: $" << ourObject.minCost << endl;


	switch (ourObject.getPriceTrend())
	{
	case ourObject.STABLE:
		out << "��������� ������: ���������" << endl;
		break;
	case ourObject.INCREASING:
		out << "��������� ������: �����" << endl;
		break;
	case ourObject.DECREASING:
		out << "��������� ������: ������" << endl;
		break;
	case ourObject.AT_MINIMUM:
		out << "��������� ������: �� ��������" << endl;
		break;
	case ourObject.AT_MAXIMUM:
		out << "��������� ������: �� ���������" << endl;
		break;
	}

	return out;
}
template<typename T>
ostream& operator << (ostream& out, const IProduct<T>& ourObject) {
	ourObject.printSummary();
	return out;
}

#endif  PRODUCTCOST_H
