#include "IProduct.h"
#include "ProductCost.h"
#include "ProductRating.h"


int main() 
{
	setlocale(LC_ALL, "Russian");
    char link[] = "http://example.com/phone";
    int startPrice;
    double price; int stock;
    bool check = true;
    char select;
    int count;
    unsigned int nr, pr;
    cout << "Введите начальную цену товара в 1 день" << endl;
    cin >> startPrice;
    cout << "Введите количество положительных отзывов о товарах" << endl;
    cin >> pr;
    cout << "Введите количество негативных отзывов о товарах" << endl;
    cin >> nr;
    IProduct* test[2];
    test[0] = new ProductRating(link, 10, 10, startPrice, pr, nr);

    do {
        cout << "Введите цену товара" << endl;
        cin >> price;
        cout << "Введите количество товара" << endl;
        cin >> stock;
        test[0]->updateCurrentData(price, stock);
        cout << "Введите количество положительных отзывов о товарах" << endl;
        cin >> pr;
        cout << "Введите количество негативных отзывов о товарах" << endl;
        cin >> nr;
        test[0]->CoutRating(pr, nr);
        cout << "Хотели ли бы вы добавить еще 1 день мониторинга? (Y/N)" << endl;
        cin >> select;
        if (select == 'N' || select == 'n')
        {
            check = false;
        }
    } while (check != false);
    check = true;
    cout << "Если хотите посмотреть цену и количество товара за определенный день, введите Y, либо введите N, если хотите посмотреть всю статистику.\n";
    cout << "Если хотите посмотреть только цену за определенный день, введите Z. Если хотите посмотреть только сводную информацию, введите S\n";
    cin >> select;
    if (select == 'N' || select == 'n')
    {
        check = false;
        test[0]->printSummary();
        test[0]->CoutRating();
    }
    else if(select == 'Y' || select == 'y')
    {
        cout << "Введите номер дня: ";
        cin >> count;
        test[0]->printSummary(count);
    }  
    else if (select == 'Z' || select == 'z')
    {
        cout << "Введите номер дня: ";
        cin >> count;
        //price = test[count];
        cout << "Цена за этот день составляла: " << price;
    }
    else if (select == 'S' || select == 's')
    {
        cout << test[0];
    }
}