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
    unsigned int maxRateDay;  // ����� ���� ��� �������� ��� � ������������� ��������
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
        maxRateDay = ProductCost<T>::actualmonitoringDay;
    }
}
template<typename T>
void ProductRating<T>::CoutRating() const
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