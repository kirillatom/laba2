#include "ProductCost.h"

ProductCost::ProductCost(const char* url, const unsigned int day, const unsigned int stock, double prices)
	: monitoringDay(day), productQuantity(stock), price(prices), actualmonitoringDay(0) 
{
	if (monitoringDay <= 0)
	{
		throw invalid_argument("��� ����������� �� ����� ���� ����� ���� ��� ���� ������ ����!!!");
	}
	if (price <= 0)
	{
		throw invalid_argument("������� ��������� �� ����� ���� ����� ���� ��� ���� ������ ����!!!");
	}

	strncpy_s(this->url, url, URL_LENGTH - 1); 
	this->url[URL_LENGTH - 1] = '0'; 

	maxCost = price;
	minCost = price - 200;
	priceHistory.push_back(price);
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

	priceHistory.push_back(newPrice);

	actualmonitoringDay++;

	if (newPrice > maxCost)
	{
		maxCost = newPrice;
	}
	if (newPrice < minCost)
	{
		minCost = newPrice;
    }
	averageCost = 0.0;
	for (double price : priceHistory) 
	{   
		averageCost += price;
	}
	averageCost /= priceHistory.size();
}

void ProductCost::printSummary() const {
	cout << url << endl;
	cout << "��� �����������: " << actualmonitoringDay << "/" << monitoringDay << endl;
	cout << "������� ����: $" << fixed << setprecision(2) << price << endl;
	cout << "������� ���������� ������:  " << productQuantity << endl;
	cout << "������� ���: ";
	for (double price : priceHistory) {
		cout << "$" << price << " ";
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
bool ProductCost::isLowStock() const
{
	if (productQuantity < 2)
	{
		return true && "����� ������ ������!";
	}
	else {
		return false;
	}
}
