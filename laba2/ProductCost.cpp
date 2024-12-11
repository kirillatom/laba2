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
		throw invalid_argument("��� ����������� �� ����� ���� ����� ���� ��� ���� ������ ����!!!");
	}
	if (price <= NUMBER_NULLIK)
	{
		throw invalid_argument("������� ��������� �� ����� ���� ����� ���� ��� ���� ������ ����!!!");
	}
	if ( url == nullptr) 
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

ProductCost::ProductCost(const char* url, const unsigned int productQuantity)
{
	if ( url == nullptr)
	{
		throw invalid_argument("������������ ������!!!");
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
	for (double price : priceHistory) 
	{   
		averageCost += price;
	}
	averageCost /= priceHistory.size();
}

void ProductCost::printSummary() const 
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
		cout << monitoringDays[i] <<": "<< priceHistory[i] << endl;
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

void ProductCost::printSummary(int MonitoringDay)
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
