#include <iostream>
#include <string>
#include <vector>
#include <iomanip> 

using namespace std;

class ProductCost
{
public:
	enum PriceTrend {
		STABLE,        // Цена стабильная
		INCREASING,    // Цена растет
		DECREASING,    // Цена падает
		AT_MINIMUM,    // Цена на минимуме
		AT_MAXIMUM    // Цена на максимуме
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

	ProductCost(const char* url, const unsigned int productQuantity);

	~ProductCost();

	//метод тригера
	bool isLowStock() const;

	void updateCurrentData(double newPrice, int newProductQuantity);
	void printSummary() const;
	void printSummary(int MonitoringDay);
	//Селекторы
	unsigned int getProductQuantity() const;
	unsigned int getMonitoringDay() const;
	double getPrice() const;
	unsigned int getActualmonitoringDay() const;
	double getAverageCost() const;
	double getMaxCost() const;
	double getMinCost() const;

	double operator[](int MonitoringDay) const
	{
		double test = 0;
		for (int i = 0; i < monitoringDays.size(); i++)
		{
			if (MonitoringDay == monitoringDays[i])
			{
				return test = priceHistory[i];

			}
		}
	};

	friend ostream& operator << (ostream& out, ProductCost& ourObject) 
	{
		out << ourObject.url << endl;
		out << "Дни мониторинга: " << ourObject.actualmonitoringDay << endl;
		out << "Текущая цена: $" << fixed << setprecision(2) << ourObject.price << endl;
		out << "Текущее количество товара:  " << ourObject.productQuantity << endl;
		out << "Средняя цена: $" << ourObject.averageCost << endl;
		out << "Максимальная цена: $" << ourObject.maxCost << endl;
		out << "Минимальная цена: $" << ourObject.minCost << endl;


		switch (ourObject.getPriceTrend())
		{
		case STABLE:
			out << "Тенденция товара: стабильно" << endl;
			break;
		case INCREASING:
			out << "Тенденция товара: растёт" << endl;
			break;
		case DECREASING:
			out << "Тенденция товара: падает" << endl;
			break;
		case AT_MINIMUM:
			out << "Тенденция товара: на минимуме" << endl;
			break;
		case AT_MAXIMUM:
			out << "Тенденция товара: на максимуме" << endl;
			break;
		}

		return out;
	}



private:
	// поля
	unsigned int productQuantity; // текущее количество товара;
    double price; //  текущая стоимость;
	unsigned int monitoringDay; // количество дней мониторинга;
	unsigned int actualmonitoringDay; // текущий день мониторинга;
	double averageCost = 0; // средняя стоимость
	double maxCost; // максимальная стоимость
	double minCost; // минимальная стоимость
	static const int minProduct = 2;
	static const int URL_LENGTH = 256;
	char url[URL_LENGTH]; // URL
	vector<double> priceHistory;
	vector<int> monitoringDays; //Дни мониторинга
	vector<int> productQuantityHistory; 

	
};

