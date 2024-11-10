﻿#include "ProductCost.h"
#include "string"

int main() 
{
	setlocale(LC_ALL, "Russian");
    char link[] = "http://example.com/phone";
    ProductCost monitor(link, 10, 10, 299.99);  
    double price; int stock;
    bool check = true;
    char select;
    int count;

    do {
        cout << "Введите цену товара" << endl;
        cin >> price;
        cout << "Введите количество товара" << endl;
        cin >> stock;
        monitor.updateCurrentData(price, stock);
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
        monitor.printSummary();
    }
    else if(select == 'Y' || select == 'y')
    {
        cout << "Введите номер дня: ";
        cin >> count;
        monitor.printSummary(count);
    }  
    else if (select == 'Z' || select == 'z')
    {
        price = monitor[count];
        cout << "Цена за этот день составляла: " << price;
    }
    else if (select == 'S' || select == 's')
    {
        cout << monitor;
    }
}