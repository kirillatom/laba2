#include "ProductRating.h"

ProductRating::ProductRating(const char* url,
    const unsigned int day,
    const unsigned int stock, 
    double price, 
    unsigned int& positiveReviewCount, 
    unsigned int& negativeReviewCount) : ProductCost(url, day, stock, price)
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
    } //TODO ������� ��������� �������� �������� � ������������� ��
}

void ProductRating::CoutRating() const
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

int ProductRating::GetPositiveReviews() const {

    return positiveReviews.back();
}

int ProductRating::GetNegativeReviews() const {
    return negativeReviews.back();
}

void ProductRating::updateCurrentData(double newPrice, int newProductQuantity, int positiveReviewCount, int negativeReviewCount)
{
    if (positiveReviewCount < 0)
    {
        throw invalid_argument("���������� ������������� ������� �� ����� ���� �������������!!!");
    }
    if (negativeReviewCount < 0)
    {
        throw invalid_argument("���������� ���������� ������� �� ����� ���� �������������!!!");
    }

    ProductCost::updateCurrentData(newPrice, newProductQuantity);

    positiveReviews.push_back(positiveReviewCount);
    negativeReviews.push_back(negativeReviewCount);
}


