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
		out << "��� �����������: " << ourObject.actualmonitoringDay << endl;
		out << "������� ����: $" << fixed << setprecision(2) << ourObject.price << endl;
		out << "������� ���������� ������:  " << ourObject.productQuantity << endl;
		out << "������� ����: $" << ourObject.averageCost << endl;
		out << "������������ ����: $" << ourObject.maxCost << endl;
		out << "����������� ����: $" << ourObject.minCost << endl;


		switch (ourObject.getPriceTrend())
		{
		case STABLE:
			out << "��������� ������: ���������" << endl;
			break;
		case INCREASING:
			out << "��������� ������: �����" << endl;
			break;
		case DECREASING:
			out << "��������� ������: ������" << endl;
			break;
		case AT_MINIMUM:
			out << "��������� ������: �� ��������" << endl;
			break;
		case AT_MAXIMUM:
			out << "��������� ������: �� ���������" << endl;
			break;
		}

		return out;
	}



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
	vector<int> monitoringDays; //��� �����������
	vector<int> productQuantityHistory; 

	
};

