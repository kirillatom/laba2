#include "IProduct.h"

ostream& operator << (ostream& out, const IProduct& ourObject)
{
	out << ourObject.url << endl;
	out << "Дни мониторинга: " << ourObject.actualmonitoringDay + 1 << endl;
	out << "Текущая цена: $" << fixed << setprecision(2) << ourObject.price << endl;
	out << "Текущее количество товара:  " << ourObject.productQuantity << endl;
	out << "Средняя цена: $" << ourObject.averageCost << endl;
	out << "Максимальная цена: $" << ourObject.maxCost << endl;
	out << "Минимальная цена: $" << ourObject.minCost << endl;


	switch (ourObject.getPriceTrend())
	{
	case ourObject.STABLE:
		out << "Тенденция товара: стабильно" << endl;
		break;
	case ourObject.INCREASING:
		out << "Тенденция товара: растёт" << endl;
		break;
	case ourObject.DECREASING:
		out << "Тенденция товара: падает" << endl;
		break;
	case ourObject.AT_MINIMUM:
		out << "Тенденция товара: на минимуме" << endl;
		break;
	case ourObject.AT_MAXIMUM:
		out << "Тенденция товара: на максимуме" << endl;
		break;
	}

	return out;
}
