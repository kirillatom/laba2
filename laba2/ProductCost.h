#include <iostream>
#include <string>
#include <vector>
#include <iomanip> 

using namespace std;

class ProductCost
{
public:
	enum PriceTrend {
		STABLE,        // ���� ����������
		INCREASING,    // ���� ������
		DECREASING,    // ���� ������
		AT_MINIMUM,    // ���� �� ��������
		AT_MAXIMUM    // ���� �� ���������
	};
	PriceTrend getPriceTrend() const 
	{
		double lastPrice = priceHistory[actualmonitoringDay - 1];

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

	ProductCost(const char* url, const unsigned int day, const unsigned int stock, double price);

	~ProductCost();

	//����� �������
	bool isLowStock() const;

	void updateCurrentData(double newPrice, int newProductQuantity);
	void printSummary() const;
	//���������
	unsigned int getProductQuantity() const;
	unsigned int getMonitoringDay() const;
	double getPrice() const;
	unsigned int getActualmonitoringDay() const;
	double getAverageCost() const;
	double getMaxCost() const;
	double getMinCost() const;


private:
	// ����
	unsigned int productQuantity; // ������� ���������� ������;
    double price; //  ������� ���������;
	unsigned int monitoringDay; // ���������� ���� �����������;
	unsigned int actualmonitoringDay; // ������� ���� �����������;
	double averageCost = 0; // ������� ���������
	double maxCost; // ������������ ���������
	double minCost; // ����������� ���������
	static const int minProduct = 2;
	static const int URL_LENGTH = 256;
	char url[URL_LENGTH]; // URL
	vector<double> priceHistory;
	
};

