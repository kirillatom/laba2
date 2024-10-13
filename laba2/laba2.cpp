#include "ProductCost.h"


int main() 
{
	setlocale(LC_ALL, "Russian");
    char link[] = "http://example.com/phone";
    ProductCost monitor(link, 30, 10, 299.99);  
    double price; int stock;
    bool check = true;
    string string;

    do {
        cout << "Введите цену товара" << endl;
        cin >> price;
        cout << "Введите количество товара" << endl;
        cin >> stock;
        monitor.updateCurrentData(price, stock);
        cout << "Хотели ли бы вы добавить еще 1 день мониторинга? (Да/Нет)" << endl;
        cin.ignore();
        getline(cin, string);
        if (string != "Да") 
        {
            check = false;
        }
    } while (check != false);
    
   
    monitor.updateCurrentData(289.99, 8);   
    monitor.updateCurrentData(299.99, 5);   
    monitor.updateCurrentData(279.99, 1);  
    
    monitor.printSummary();
	 
}