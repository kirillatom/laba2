#include <iostream>
#include <string>
#include <vector>
#include <iomanip> 

using namespace std;

class ProductCost
{
public:
	enum PriceTrend {
		STABLE = 0,        // ���� ����������
		INCREASING = 1,    // ���� ������
		DECREASING = 2,    // ���� ������
		AT_MINIMUM = 3,    // ���� �� ��������
		AT_MAXIMUM = 4     // ���� �� ���������
	};
	PriceTrend getPriceTrend() const {
		double lastPrice = priceHistory[monitoringDay - 1];
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
	ProductCost(const char* url, const unsigned int day, const unsigned int stock, const double prices) {}

	//����� �������
	bool isLowStock() const;

	void updateCurrentData(double newPrice, int newProductQuantity);
	void printSummary() const;
	//���������
	unsigned int getProductQuantity() const
	{
		return productQuantity;
    }
	unsigned int getMonitoringDay() const
	{
		return monitoringDay;
	}
	double getPrice() const
	{
		return price;
	}
	unsigned int getActualmonitoringDay() const
	{
		return actualmonitoringDay;
	}
	double getAverageCost() const
	{
		return averageCost;
	}
	double getMaxCost() const
	{
		return maxCost;
	}
	double getMinCost() const
	{
		return minCost;
	}


private:
	// ����
	unsigned int productQuantity; // ������� ���������� ������;
    double price; //  ������� ���������;
	unsigned int monitoringDay; // ���������� ���� �����������;
	unsigned int actualmonitoringDay; // ������� ���� �����������;
	double averageCost; // ������� ���������
	double maxCost; // ������������ ���������
	double minCost; // ����������� ���������
	static const int URL_LENGTH = 256;
	// ������ � ������
	static char url[URL_LENGTH];
	vector<double> priceHistory;
	
};

