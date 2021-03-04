#include <iostream>
#include <string>
#include <math.h>
using namespace std;


 struct Node
{
   int Data;
   Node *Next;
 };

 struct List
 {
     int *Node;
 };

double myFunction(double x){
    return pow(cos(x), 2);
}

double append(List* list, Node* node){
    double  Item, minValue = 0, maxValue = M_PI / 4, step = M_PI / 40;
    Node *Current;
    Node *first = new Node;
    first = NULL;

    Item = myFunction(minValue);

    Node *NewItem = new Node;
    NewItem -> Data = Item;
    NewItem -> Next = NULL;
    (*first) = *NewItem;

    minValue += step;

    for (int i = minValue; i <= maxValue; i += step) {
        Node *NewItem = new Node;
        Item = myFunction(minValue);
        NewItem -> Data = Item;
        NewItem -> Next = NULL;
        *Current = (*first);
        while (Current -> Next != NULL)
            Current = Current -> Next;
        Current->Next = NewItem;
    }
}


int main() {

    return 0;
}
