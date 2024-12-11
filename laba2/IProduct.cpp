#include "IProduct.h"

ostream& operator << (ostream& out, const IProduct& ourObject)
{
	out << ourObject.url << endl;
	out << "��� �����������: " << ourObject.actualmonitoringDay + 1 << endl;
	out << "������� ����: $" << fixed << setprecision(2) << ourObject.price << endl;
	out << "������� ���������� ������:  " << ourObject.productQuantity << endl;
	out << "������� ����: $" << ourObject.averageCost << endl;
	out << "������������ ����: $" << ourObject.maxCost << endl;
	out << "����������� ����: $" << ourObject.minCost << endl;


	switch (ourObject.getPriceTrend())
	{
	case ourObject.STABLE:
		out << "��������� ������: ���������" << endl;
		break;
	case ourObject.INCREASING:
		out << "��������� ������: �����" << endl;
		break;
	case ourObject.DECREASING:
		out << "��������� ������: ������" << endl;
		break;
	case ourObject.AT_MINIMUM:
		out << "��������� ������: �� ��������" << endl;
		break;
	case ourObject.AT_MAXIMUM:
		out << "��������� ������: �� ���������" << endl;
		break;
	}

	return out;
}
