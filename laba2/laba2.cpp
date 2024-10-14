#include "ProductCost.h"


int main() 
{
	setlocale(LC_ALL, "Russian");
    char link[] = "http://example.com/phone";
    ProductCost monitor(link, 10, 10, 299.99);  
    double price; int stock;
    bool check = true;
    char string;

    do {
        cout << "Введите цену товара" << endl;
        cin >> price;
        cout << "Введите количество товара" << endl;
        cin >> stock;
        monitor.updateCurrentData(price, stock);
        cout << "Хотели ли бы вы добавить еще 1 день мониторинга? (Y/N)" << endl;
        cin >> string;
        if (string == 'N')
        {
            check = false;
        }
    } while (check != false);
    
    monitor.printSummary();
	 
}