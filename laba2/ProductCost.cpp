#include "ProductCost.h"

ProductCost::ProductCost(const char* url, const unsigned int day, const unsigned int stock, double price)
	: productQuantity(stock), price(price), monitoringDay(day), actualmonitoringDay(0) 
{
	if (monitoringDay <= 0)
	{
		throw invalid_argument("��� ����������� �� ����� ���� ����� ���� ��� ���� ������ ����!!!");
	}
	if (price <= 0)
	{
		throw invalid_argument("������� ��������� �� ����� ���� ����� ���� ��� ���� ������ ����!!!");
	}
	if (url == 0 || url == nullptr) 
	{
		throw invalid_argument("������������ ������!!!");
	}
	strncpy_s(this->url, url, URL_LENGTH - 1); 
	this->url[URL_LENGTH - 1] = '0'; 

	maxCost = price;
	minCost = price;
	priceHistory.push_back(price);
	monitoringDays.push_back(1);
	productQuantityHistory.push_back(stock);
}

ProductCost::ProductCost(const char* url, const unsigned int productQuantity)
{
	if (url == 0 || url == nullptr)
	{
		throw invalid_argument("������������ ������!!!");
	}
	strncpy_s(this->url, url, URL_LENGTH - 1);
	this->url[URL_LENGTH - 1] = '0';
}

 ProductCost::~ProductCost()
{
	priceHistory.clear();
	priceHistory.shrink_to_fit();
	monitoringDays.clear();
	monitoringDays.shrink_to_fit();
}

 
void ProductCost::updateCurrentData(double newPrice, int newProductQuantity) {
	if (newProductQuantity < 0)
	{
		throw invalid_argument("����� ������ �� ����� ���� �������������!!!");
	}
	if (newPrice < 0)
	{
		throw invalid_argument("���� ������ �� ����� ���� �������������!!!");
	}

	productQuantity = newProductQuantity;

	price = newPrice;

	actualmonitoringDay++;

	priceHistory.push_back(newPrice);

	monitoringDays.push_back(actualmonitoringDay + 1);

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

void ProductCost::printSummary() const {
	cout << url << endl;
	cout << "��� �����������: " << actualmonitoringDay << endl;
	cout << "������� ����: $" << fixed << setprecision(2) << price << endl;
	cout << "������� ���������� ������:  " << productQuantity << endl;
	cout << "������� ���: \n";
	if (priceHistory.size() != monitoringDays.size())
	{
		throw out_of_range("������ ������ 404");
	}
	for (int i = 0; i < priceHistory.size(); ++i)
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
	for (int i = 0; i < monitoringDays.size(); i++)
	{
		if (MonitoringDay == monitoringDays[i])
		{
			cout << "����: $" << priceHistory[i] << endl;
			cout << "���������� ������:  " << productQuantityHistory[i] << endl;
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
