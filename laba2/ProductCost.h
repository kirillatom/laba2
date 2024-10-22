#include <iostream>
#include <string>
#include <vector>
#include <iomanip> 

using namespace std;

class ProductCost
{
public:
	enum PriceTrend {
		STABLE,        // ÷ена стабильна€
		INCREASING,    // ÷ена растет
		DECREASING,    // ÷ена падает
		AT_MINIMUM,    // ÷ена на минимуме
		AT_MAXIMUM    // ÷ена на максимуме
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

	//метод тригера
	bool isLowStock() const;

	void updateCurrentData(double newPrice, int newProductQuantity);
	void printSummary() const;
	//—електоры
	unsigned int getProductQuantity() const;
	unsigned int getMonitoringDay() const;
	double getPrice() const;
	unsigned int getActualmonitoringDay() const;
	double getAverageCost() const;
	double getMaxCost() const;
	double getMinCost() const;


private:
	// пол€
	unsigned int productQuantity; // текущее количество товара;
    double price; //  текуща€ стоимость;
	unsigned int monitoringDay; // количество дней мониторинга;
	unsigned int actualmonitoringDay; // текущий день мониторинга;
	double averageCost = 0; // средн€€ стоимость
	double maxCost; // максимальна€ стоимость
	double minCost; // минимальна€ стоимость
	static const int minProduct = 2;
	static const int URL_LENGTH = 256;
	char url[URL_LENGTH]; // URL
	vector<double> priceHistory;
	
};

