#include <iostream>
#include <string>
#include <vector>
#include <iomanip> 

using namespace std;

class ProductCost
{
public:
	enum PriceTrend {
		STABLE = 0,        // ÷ена стабильна€
		INCREASING = 1,    // ÷ена растет
		DECREASING = 2,    // ÷ена падает
		AT_MINIMUM = 3,    // ÷ена на минимуме
		AT_MAXIMUM = 4     // ÷ена на максимуме
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

	//метод тригера
	bool isLowStock() const;

	void updateCurrentData(double newPrice, int newProductQuantity);
	void printSummary() const;
	//—електоры
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
	// пол€
	unsigned int productQuantity; // текущее количество товара;
    double price; //  текуща€ стоимость;
	unsigned int monitoringDay; // количество дней мониторинга;
	unsigned int actualmonitoringDay; // текущий день мониторинга;
	double averageCost; // средн€€ стоимость
	double maxCost; // максимальна€ стоимость
	double minCost; // минимальна€ стоимость
	static const int URL_LENGTH = 256;
	// массив и вектор
	static char url[URL_LENGTH];
	vector<double> priceHistory;
	
};

