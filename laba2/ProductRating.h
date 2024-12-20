#include "ProductCost.h"
template<typename T>
class ProductRating : public ProductCost<T>
{
public:
    ProductRating(const char* url, const unsigned int day, const unsigned int stock, T price, unsigned int& positiveReviewCount, unsigned int& negativeReviewCount);
    void CoutRating() const override;
    ~ProductRating();

    int GetPositiveReviews() const;
    int GetNegativeReviews() const;
    void updateCurrentData(double newPrice, int newProductQuantity, int positiveReviewCount, int negativeReviewCount);


private:
    vector <unsigned int> positiveReviews;
    vector <unsigned int> negativeReviews;
    unsigned int maxRateProduct;
    unsigned int maxRateDay;  // Новый член для хранения дня с максимальными отзывами
};
template<typename T>
ProductRating<T>::ProductRating(const char* url,
    const unsigned int day,
    const unsigned int stock,
    T price,
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
        maxRateDay = ProductCost<T>::actualmonitoringDay;
    }
}
template<typename T>
void ProductRating<T>::CoutRating() const
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
template<typename T>
ProductRating<T>::~ProductRating()
{
    positiveReviews.clear();
    positiveReviews.shrink_to_fit();
    negativeReviews.clear();
    negativeReviews.shrink_to_fit();
}
template<typename T>
int ProductRating<T>::GetPositiveReviews() const {

    return positiveReviews.back();
}
template<typename T>
int ProductRating<T>::GetNegativeReviews() const {
    return negativeReviews.back();
}
template<typename T>
void ProductRating<T>::updateCurrentData(double newPrice, int newProductQuantity, int positiveReviewCount, int negativeReviewCount)
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