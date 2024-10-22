#include "ProductCost.h"

ProductCost::ProductCost(const char* url, const unsigned int day, const unsigned int stock, double price)
	: productQuantity(stock), price(price), monitoringDay(day), actualmonitoringDay(0) 
{
	if (monitoringDay <= 0)
	{
		throw invalid_argument("Дни мониторинга не могут быть равны нулю или быть меньше него!!!");
	}
	if (price <= 0)
	{
		throw invalid_argument("Текущая стоимость не может быть равна нулю или быть меньше него!!!");
	}
	if (url == 0 || url == nullptr) 
	{
		throw invalid_argument("Некорректная ссылка!!!");
	}
	strncpy_s(this->url, url, URL_LENGTH - 1); 
	this->url[URL_LENGTH - 1] = '0'; 

	maxCost = price;
	minCost = price;
	priceHistory.push_back(price);
}
 ProductCost::~ProductCost()
{
	priceHistory.clear();
	priceHistory.shrink_to_fit();
}

 
void ProductCost::updateCurrentData(double newPrice, int newProductQuantity) {
	if (newProductQuantity < 0)
	{
		throw invalid_argument("Запас товара не может быть отрицательным!!!");
	}
	if (newPrice < 0)
	{
		throw invalid_argument("Цена товара не может быть отрицательным!!!");
	}

	productQuantity = newProductQuantity;

	price = newPrice;

	actualmonitoringDay++;

	priceHistory.push_back(newPrice);

	if (newPrice > maxCost)
	{
		maxCost = newPrice;
	}
	if (newPrice < minCost)
	{
		minCost = newPrice;
    }
	for (double price : priceHistory) 
	{   
		averageCost += price;
	}
	averageCost /= priceHistory.size();
}

void ProductCost::printSummary() const {
	cout << url << endl;
	cout << "Дни мониторинга: " << actualmonitoringDay << endl;
	cout << "Текущая цена: $" << fixed << setprecision(2) << price << endl;
	cout << "Текущее количество товара:  " << productQuantity << endl;
	cout << "История цен: ";
	for (double price : priceHistory) {
		cout << "$" << price << " ";
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

//Селекторы

inline unsigned int ProductCost::getProductQuantity() const
{
	return productQuantity;
}
inline unsigned int ProductCost::getMonitoringDay() const
{
	return monitoringDay;
}
inline double ProductCost::getPrice() const
{
	return price;
}
inline unsigned int ProductCost::getActualmonitoringDay() const
{
	return actualmonitoringDay;
}
inline double ProductCost::getAverageCost() const
{
	return averageCost;
}
inline double ProductCost::getMaxCost() const
{
	return maxCost;
}
inline double ProductCost::getMinCost() const
{
	return minCost;
}
bool ProductCost::isLowStock() const
{
	if (productQuantity < minProduct)
	{
		return true;
	}
	else {
		return false;
	}
}
