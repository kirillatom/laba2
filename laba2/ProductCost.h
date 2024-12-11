#ifndef PRODUCTCOST_H
#define PRODUCTCOST_H
#include <iostream>
#include <string>
#include <vector>
#include <iomanip> 
#include "IProduct.h"

using namespace std;

class ProductCost : public IProduct
{
public:

	enum PriceTrend {
		STABLE,        // ���� ����������
		INCREASING,    // ���� ������
		DECREASING,    // ���� ������
		AT_MINIMUM,    // ���� �� ��������
		AT_MAXIMUM    // ���� �� ���������
	};
	PriceTrend getPriceTrend() const;

	ProductCost(const char* url, const unsigned int day, const unsigned int stock, double price);

	ProductCost(const char* url, const unsigned int productQuantity);

	~ProductCost();

	//����� �������
	bool isLowStock() const;

	void updateCurrentData(double newPrice, int newProductQuantity);
	void printSummary() const override;
	void printSummary(int MonitoringDay);
	//���������
	unsigned int getProductQuantity() const;
	unsigned int getMonitoringDay() const;
	double getPrice() const;
	unsigned int getActualmonitoringDay() const;
	double getAverageCost() const;
	double getMaxCost() const;
	double getMinCost() const;

	double operator[](int MonitoringDay) const;

	friend ostream& operator << (ostream& out, const ProductCost& ourObject);

protected:
	unsigned int actualmonitoringDay; // ������� ���� �����������;

private:
	// ����
	unsigned int productQuantity; // ������� ���������� ������;
    double price; //  ������� ���������;
	unsigned int monitoringDay; // ���������� ���� �����������;
	double averageCost = 0; // ������� ���������
	double maxCost; // ������������ ���������
	double minCost; // ����������� ���������
	static const int minProduct = 2;
	static const int URL_LENGTH = 256;
	char url[URL_LENGTH]; // URL
	static const int NUMBER_NULLIK = 0;
	static const int NUMBER_ONE = 1;
	vector<double> priceHistory;
	vector<int> monitoringDays; //��� �����������
	vector<int> productQuantityHistory; 
};
#endif  PRODUCTCOST_H

