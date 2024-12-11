#include "ProductCost.h"

ProductCost::PriceTrend ProductCost::getPriceTrend() const
{
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

ProductCost::ProductCost(const char* url, const unsigned int day, const unsigned int stock, double price)
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
	if ( url == nullptr) 
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

ProductCost::ProductCost(const char* url, const unsigned int productQuantity)
{
	if ( url == nullptr)
	{
		throw invalid_argument("Некорректная ссылка!!!");
	}
	strncpy_s(this->url, url, URL_LENGTH - NUMBER_ONE);
	this->url[URL_LENGTH - NUMBER_ONE] = '0';
}

 ProductCost::~ProductCost()
{
	priceHistory.clear();
	priceHistory.shrink_to_fit();
	monitoringDays.clear();
	monitoringDays.shrink_to_fit();
}

 
void ProductCost::updateCurrentData(double newPrice, int newProductQuantity) {
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
	for (double price : priceHistory) 
	{   
		averageCost += price;
	}
	averageCost /= priceHistory.size();
}

void ProductCost::printSummary() const 
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
		cout << monitoringDays[i] <<": "<< priceHistory[i] << endl;
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

void ProductCost::printSummary(int MonitoringDay)
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

double ProductCost::operator[](int MonitoringDay) const
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


ostream& operator << (ostream& out, const ProductCost& ourObject) 
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
