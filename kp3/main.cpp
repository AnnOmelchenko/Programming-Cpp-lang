#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
using namespace std;


 struct Node
{
   double data;
   Node *next;
 };

 Node* head = NULL, *current, *newptr, *last;
 int size = 0;

Node* head_2 = NULL, *current_2, *newptr_2, *last_2;
int size_2 = 0;

double myFunction(double x){
    return pow(cos(fabs(x)), 2);
}

void CreateFirstItem()
{
    head = newptr;
    head->next = NULL;
}

void Push(double data)
{
    newptr = new (Node);
    newptr->data = data;
    if (head == NULL)
    {
        CreateFirstItem();
        last = head;
    }
    else
    {
        last->next = newptr;
        last = newptr;
        last->next = NULL;
    }
    size++;
}

void Remove_2(int index){
    if(index == 1){
        Node* node = head_2;
        head_2 = head_2->next;
        delete node;
        return;
    }

    Node *currentHead = head_2;
    Node *prev = NULL;
    int i = 1;
    while(i++ < index){
        if(currentHead == NULL){
            std::cout << "Error: Such element does not exist" << std::endl;
            return;
        }
        prev = currentHead;
        currentHead = currentHead->next;
    }

    prev->next = currentHead->next;

    delete currentHead;
    size_2--;
}


void Remove(int index){

    if(index == 1){
        Node* node = head;
        head = head->next;
        delete node;
        return;
    }

    Node *currentHead = head;
    Node *prev = NULL;
    int i = 1;
    while(i++ < index){
        if(currentHead == NULL){
            std::cout << "Error: Such element does not exist" << std::endl;
            return;
        }
        prev = currentHead;
        currentHead = currentHead->next;
    }

    prev->next = currentHead->next;

    delete currentHead;
    size--;
}



void Show()
{
    int counter = 1;
    current = head;
    current_2 = head_2;
    if (current == NULL || current_2 == NULL)
    {
        cout << "List is empty" << endl;
    }
    else
    {
        cout << "X" << "\t\t\t\t\tY \t\t Number" << endl;
        do
        {
            printf("%.6lf\t\t\t", current->data);
            printf("%.6lf\t\t", current_2->data);
            cout << counter++ << endl;

            current = current->next;
            current_2 = current_2->next;
        } while (current != NULL || current_2 != NULL);
        cout << endl;
    }
}




void CreateFirstItem_2()
{
    head_2 = newptr_2;
    head_2->next = NULL;
}

void Push_2(double data)
{
    newptr_2 = new (Node);
    newptr_2->data = data;
    if (head_2 == NULL)
    {
        CreateFirstItem_2();
        last_2 = head_2;
    }
    else
    {
        last_2->next = newptr_2;
        last_2 = newptr_2;
        last_2->next = NULL;
    }
    size_2++;
}

double get_Value(int index){
    int counter = -1;
    Node *temp = head;

    while (temp->next != NULL){
        if (++counter == index) {
            return temp->data;
        }
        temp = temp->next;

    }
}

double get_Value2(int index){
    int counter = -1;
    Node *temp = head_2;

    while (temp->next != NULL){
        if (++counter == index) {
            return temp->data;
        }
        temp = temp->next;
    }
}



int main() {
    double  minValue = 0, maxValue = M_PI / 4, step = M_PI / 40;
    int counter = 0, number;

    ofstream out("kp3.txt");

    for (double i = minValue; i <= maxValue; i += step) {
        Push(i);
        out << myFunction(i) << "\n";
        counter++;
    }


    out.close();

    ifstream in("kp3.txt");

    for (int i = 0; i < counter; ++i) {
        float value;
        in >> value;
        Push_2(value);
    }

    in.close();

    Show();

    for (int i = 0; i < 11; i++) {
        double value_1 = get_Value(i);
        double value_2 = get_Value(i + 1);
        Push((value_1 + value_2) / 2);
    }

    for (int i = 0; i < 11; ++i) {
        double value_1 = get_Value2(i);
        double value_2 = get_Value2(i + 1);
        Push_2((value_1 + value_2) / 2);
    }

    cout << endl;

    Show();

    do {
        do{
            cout<< "Enter element which you want to delete or press Enter to exit: ";
            scanf("%i", &number);
            Remove(number);
            Remove_2(number);
            Show();
        } while (getchar() != '\n');
        cout<< "Enter any key to continue or press Enter to exit: ";
    } while (getchar() != '\n');


    return 0;
}
