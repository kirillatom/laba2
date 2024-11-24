#include "ProductCost.h"
class ProductRating : public ProductCost
{
public:
    void Rating(unsigned int& positiveReviewCount, unsigned int& negativeReviewCount);
    void CoutRating();
    ~ProductRating();

private:
    vector <unsigned int> positiveReviews;
    vector <unsigned int> negativeReviews;
    unsigned int maxRateProduct;
    unsigned int maxRateDay;  // Новый член для хранения дня с максимальными отзывами
};
