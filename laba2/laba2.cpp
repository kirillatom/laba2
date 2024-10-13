#include "ProductCost.h"


int main() 
{
	setlocale(LC_ALL, "Russian");
    char link[] = "http://example.com/phone";
    ProductCost monitor(link, 30, 10, 299.99);  
    double price; int 
    
   
    monitor.updateCurrentData(289.99, 8);   
    monitor.updateCurrentData(299.99, 5);   
    monitor.updateCurrentData(279.99, 1);  

    monitor.printSummary();
	 
}