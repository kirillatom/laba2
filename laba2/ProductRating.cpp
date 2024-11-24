#include "ProductRating.h"

void ProductRating::Rating(unsigned int& positiveReviewCount, unsigned int& negativeReviewCount)
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

}

void ProductRating::CoutRating()
{
	for (int num : positiveReviews) {
		if (num > maxRateProduct) {
			maxRateProduct = num;
		}
	}
	cout << "В " << actualmonitoringDay << " день количество положительных отзывов о товарах больше всего, а именно: " << maxRateProduct << endl;
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

