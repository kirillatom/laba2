#include "ProductCost.h"
class ProductRating : public ProductCost
{
public:
    ProductRating(const char* url, const unsigned int day, const unsigned int stock, double price, unsigned int& positiveReviewCount, unsigned int& negativeReviewCount);
    void CoutRating() const;
    ~ProductRating();

    int GetPositiveReviews() const;
    int GetNegativeReviews() const;
    void updateCurrentData(double newPrice, int newProductQuantity, int positiveReviewCount, int negativeReviewCount);

    //TODO �������� ����� ��������� � �������������� ������ ��������� �������� ������ currentdata

private:
    vector <unsigned int> positiveReviews;
    vector <unsigned int> negativeReviews;
    unsigned int maxRateProduct;
    unsigned int maxRateDay;  // ����� ���� ��� �������� ��� � ������������� ��������
};
