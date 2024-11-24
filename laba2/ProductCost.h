#ifndef PRODUCTCOST_H
#define PRODUCTCOST_H
#include <iostream>
#include <string>
#include <vector>
#include <iomanip> 

using namespace std;

class ProductCost
{
public:
	unsigned int actualmonitoringDay; // ������� ���� �����������;

	enum PriceTrend {
		STABLE,        // ���� ����������
		INCREASING,    // ���� ������
		DECREASING,    // ���� ������
		AT_MINIMUM,    // ���� �� ��������
		AT_MAXIMUM    // ���� �� ���������
	};
	PriceTrend getPriceTrend() const;

	ProductCost() {};

	ProductCost(const char* url, const unsigned int day, const unsigned int stock, double price);

	ProductCost(const char* url, const unsigned int productQuantity);

	~ProductCost();

	//����� �������
	bool isLowStock() const;

	void updateCurrentData(double newPrice, int newProductQuantity);
	void printSummary() const;
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
	vector<double> priceHistory;
	vector<int> monitoringDays; //��� �����������
	vector<int> productQuantityHistory; 
};
#endif  PRODUCTCOST_H

