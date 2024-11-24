#include "ProductRating.h"

void ProductRating::Rating(unsigned int& positiveReviewCount, unsigned int& negativeReviewCount)
{
    if (positiveReviewCount < 0)
    {
        throw invalid_argument("���������� ������������� ������� �� ����� ���� �������������!!!");
    }
    if (negativeReviewCount < 0)
    {
        throw invalid_argument("���������� ���������� ������� �� ����� ���� �������������!!!");
    }

    positiveReviews.push_back(positiveReviewCount);
    negativeReviews.push_back(negativeReviewCount);

    if (positiveReviewCount > maxRateProduct)
    {
        maxRateProduct = positiveReviewCount;
        maxRateDay = actualmonitoringDay;  
    }
}

void ProductRating::CoutRating()
{
    cout << "� " << maxRateDay + 1 << " ���� ���� ������ ����� ������������� �������, � ������: " << maxRateProduct << endl;

    for (int i = 0; i < positiveReviews.size(); i++)
    {
        cout << "���������� ������������� ������� �� " << i + 1 << " ���� = " << positiveReviews[i];
        cout << endl;
    }
    for (int i = 0; i < negativeReviews.size(); i++)
    {
        cout << "���������� ���������� ������� �� " << i + 1 << " ���� = " << negativeReviews[i];
        cout << endl;
    }
}

ProductRating::~ProductRating()
{
	positiveReviews.clear();
	positiveReviews.shrink_to_fit();
	negativeReviews.clear();
	negativeReviews.shrink_to_fit();
}

