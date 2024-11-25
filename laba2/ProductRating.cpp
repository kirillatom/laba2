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
        throw invalid_argument("Количество положительных отзывов не может быть отрицательным!!!");
    }
    if (negativeReviewCount < 0)
    {
        throw invalid_argument("Количество негативных отзывов не может быть отрицательным!!!");
    }

    positiveReviews.push_back(positiveReviewCount);
    negativeReviews.push_back(negativeReviewCount);

    if (positiveReviewCount > maxRateProduct)
    {
        maxRateProduct = positiveReviewCount;
        maxRateDay = actualmonitoringDay;  
    } //TODO вывести последние элементы векторов и переименовать их
}

void ProductRating::CoutRating() const
{
    cout << "В " << maxRateDay + 1 << " день было больше всего положительных отзывов, а именно: " << maxRateProduct << endl;

    for (int i = 0; i < positiveReviews.size(); i++)
    {
        cout << "Количество положительных отзывов за " << i + 1 << " день = " << positiveReviews[i];
        cout << endl;
    }
    for (int i = 0; i < negativeReviews.size(); i++)
    {
        cout << "Количество негативных отзывов за " << i + 1 << " день = " << negativeReviews[i];
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
        throw invalid_argument("Количество положительных отзывов не может быть отрицательным!!!");
    }
    if (negativeReviewCount < 0)
    {
        throw invalid_argument("Количество негативных отзывов не может быть отрицательным!!!");
    }

    ProductCost::updateCurrentData(newPrice, newProductQuantity);

    positiveReviews.push_back(positiveReviewCount);
    negativeReviews.push_back(negativeReviewCount);
}


