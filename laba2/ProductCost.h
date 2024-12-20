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
		STABLE,        // Цена стабильная
		INCREASING,    // Цена растет
		DECREASING,    // Цена падает
		AT_MINIMUM,    // Цена на минимуме
		AT_MAXIMUM    // Цена на максимуме
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

	//метод тригера
	bool isLowStock() const;

	void updateCurrentData(T newPrice, int newProductQuantity) override;
	void printSummary() const override;
	void printSummary(int MonitoringDay) const override;
	//Селекторы
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
	unsigned int actualmonitoringDay; // текущий день мониторинга;

private:
	// поля
	unsigned int productQuantity; // текущее количество товара;
	T price; //  текущая стоимость;
	unsigned int monitoringDay; // количество дней мониторинга;
	T averageCost = 0; // средняя стоимость
	T maxCost; // максимальная стоимость
	T minCost; // минимальная стоимость
	static const int minProduct = 2;
	static const int URL_LENGTH = 256;
	char url[URL_LENGTH]; // URL
	static const int NUMBER_NULLIK = 0;
	static const int NUMBER_ONE = 1;
	vector<double> priceHistory;
	vector<int> monitoringDays; //Дни мониторинга
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
		throw invalid_argument("Дни мониторинга не могут быть равны нулю или быть меньше него!!!");
	}
	if (price <= NUMBER_NULLIK)
	{
		throw invalid_argument("Текущая стоимость не может быть равна нулю или быть меньше него!!!");
	}
	if (url == nullptr)
	{
		throw invalid_argument("Некорректная ссылка!!!");
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
		throw invalid_argument("Некорректная ссылка!!!");
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
		throw invalid_argument("Запас товара не может быть отрицательным!!!");
	}
	if (newPrice < NUMBER_NULLIK)
	{
		throw invalid_argument("Цена товара не может быть отрицательным!!!");
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
	cout << "Дни мониторинга: " << actualmonitoringDay + 1 << endl;
	cout << "Текущая цена: $" << fixed << setprecision(2) << price << endl;
	cout << "Текущее количество товара:  " << productQuantity << endl;
	cout << "История цен: \n";
	if (priceHistory.size() != monitoringDays.size())
	{
		throw out_of_range("Ошибка данных 404");
	}
	for (int i = NUMBER_NULLIK; i < priceHistory.size(); ++i)
	{
		cout << monitoringDays[i] << ": " << priceHistory[i] << endl;
	}
	cout << endl;

	cout << "Средняя цена: $" << averageCost << endl;
	cout << "Максимальная цена: $" << maxCost << endl;
	cout << "Минимальная цена: $" << minCost << endl;


	switch (getPriceTrend())
	{
	case STABLE:
		cout << "Тенденция товара: стабильно" << endl;
		break;
	case INCREASING:
		cout << "Тенденция товара: растёт" << endl;
		break;
	case DECREASING:
		cout << "Тенденция товара: падает" << endl;
		break;
	case AT_MINIMUM:
		cout << "Тенденция товара: на минимуме" << endl;
		break;
	case AT_MAXIMUM:
		cout << "Тенденция товара: на максимуме" << endl;
		break;
	}
}
template<typename T>
void ProductCost<T>::printSummary(int MonitoringDay) const
{
	cout << url << endl;
	cout << "День мониторинга: " << MonitoringDay << endl;
	for (int i = NUMBER_NULLIK; i < monitoringDays.size(); i++)
	{
		if (MonitoringDay == monitoringDays[i])
		{
			cout << "Цена: $" << priceHistory[i] << endl;
			cout << "Количество товара:  " << productQuantityHistory[i] << endl;
			break;
		}
	}
}

//Селекторы
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
	out << "Дни мониторинга: " << ourObject.actualmonitoringDay + 1 << endl;
	out << "Текущая цена: $" << fixed << setprecision(2) << ourObject.price << endl;
	out << "Текущее количество товара:  " << ourObject.productQuantity << endl;
	out << "Средняя цена: $" << ourObject.averageCost << endl;
	out << "Максимальная цена: $" << ourObject.maxCost << endl;
	out << "Минимальная цена: $" << ourObject.minCost << endl;


	switch (ourObject.getPriceTrend())
	{
	case ourObject.STABLE:
		out << "Тенденция товара: стабильно" << endl;
		break;
	case ourObject.INCREASING:
		out << "Тенденция товара: растёт" << endl;
		break;
	case ourObject.DECREASING:
		out << "Тенденция товара: падает" << endl;
		break;
	case ourObject.AT_MINIMUM:
		out << "Тенденция товара: на минимуме" << endl;
		break;
	case ourObject.AT_MAXIMUM:
		out << "Тенденция товара: на максимуме" << endl;
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
