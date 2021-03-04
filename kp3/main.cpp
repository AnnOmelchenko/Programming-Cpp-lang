#include <iostream>
#include <string>
#include <math.h>
using namespace std;


 struct List
{
   int Data;
   List *Next;
 };


double myFunction(double x){
    return pow(cos(x), 2);
}


int main() {
    double  Item, minValue = 0, maxValue = M_PI / 4, step = M_PI / 40;

    List *Current;
    List *first;
    first = NULL;

    Item = myFunction(minValue);

    List *NewItem = new List;
    NewItem -> Data = Item;
    NewItem -> Next = NULL;
    (*first) = *NewItem;

    minValue += step;

    for (int i = minValue; i <= maxValue; i += step) {
        List *NewItem = new List;
        Item = myFunction(minValue);
        NewItem -> Data = Item;
        NewItem -> Next = NULL;
        *Current = (*first);
        while (Current -> Next != NULL)
            Current = Current -> Next;
        Current->Next = NewItem;
    }


    do{
        cout << first -> Data << " ";
        first = first -> Next;
    }while(first != NULL);
     cout << endl;
    return 0;
}
