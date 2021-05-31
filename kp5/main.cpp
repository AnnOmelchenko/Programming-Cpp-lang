#include <iostream>
#include <deque>
#include <iterator>
#include "postfix.h"

using namespace std;


int clear(char issue) {
    if (issue == '\n') {
        return 0;
    }
    else {
        while (issue != '\n') {
            issue = getchar();
        }
        return 1;
    }
}

class Deque
{
public:
    deque<int> newDeque;
    void AddElementToEnd(int value);
    void AddElementToBegin(int value);
    int RemoveElementFromBegin();
    int RemoveElementFromEnd();
    void DeleteElement(int value);
    void ShowDeque();
};

void Deque::AddElementToBegin(int value) {
    newDeque.push_front(value);
}

void Deque::AddElementToEnd(int value) {
    newDeque.push_back(value);
}

int Deque::RemoveElementFromBegin() {
    int element = newDeque.front();
    newDeque.pop_front();
    return element;
}

int Deque::RemoveElementFromEnd() {
    int element = newDeque.back();
    newDeque.pop_back();
    return element;
}

void Deque::DeleteElement(int position) {
    if (newDeque.empty()){
        cout << "Deque is empty";
        return;
    }
    newDeque.erase(newDeque.begin() + position - 1);
}

void Palindrome() {
    char c;
    Deque dec;
    bool b = true;

    cout << "Input your string:\n";

    while ((c = cin.get()) != '\n'){
        dec.AddElementToEnd(c);
    }
    while (b && dec.newDeque.size() > 2){
        b = (dec.RemoveElementFromEnd() == dec.RemoveElementFromBegin());
    }

    if (b)
        cout << "The string is a palindrome\n";
    else
        cout << "This is string is not a palindrome\n";
}

void Deque::ShowDeque() {
    if (!newDeque.empty()) { // если дек не пуст
        cout << "\n Your dequeue: ";
        // вывод на экран элементов дека
        copy(newDeque.begin(), newDeque.end(), ostream_iterator<int>(cout, " ")); // вывод на экран элементов дека
    } else {
        cout << "Your deque is empty";
    }

    cout << endl;
}

void PostfixNotation(const char *_infix, char *_postfix)
{
    char stack[MAX_LEN];	// стек для хранения операторов при преобразовании
    int st_ptr = 0;				// указатель вершины стека

    int out_index = 0;		// индекс в выходной строке
    int in_index = 0;		// индекс во входной строке

    // начинаем разбор входящей строки (она не должна быть пустой)
    do
    {
        char c = _infix[in_index];	// берем текущий символ входной строки

        switch (c)
        {
            case '+':
            case '-':
                // выталкиваем из стека в выходную строку все операторы с большим или равным приоритетом
                while (st_ptr != 0)
                {
                    char op = stack[st_ptr-1];	// оператор в вершине стека
                    if (op != '(')	// все операторы, кроме откр. скобки имеют больший или равный приоритет
                    {
                        _postfix[out_index++] = op;	// добавляем оператор в выходную строку
                        pop(stack, st_ptr);			// удаляем оператор из стека
                    }
                    else
                        break;
                }
                // помещаем оператор в стек
                push(stack, st_ptr, c);
                break;

            case '*':
            case '/':
                // выталкиваем из стека в выходную строку все операторы с большим или равным приоритетом
                while (st_ptr != 0)
                {
                    char op = stack[st_ptr-1];
                    if ((op == '^') || (op == '*') || (op == '/'))
                    {
                        _postfix[out_index++] = op;	// добавляем оператор в выходную строку
                        pop(stack, st_ptr);			// удаляем оператор из стека
                    }
                    else
                        break;
                }
                // помещаем оператор в стек
                push(stack, st_ptr, c);
                break;

            case '(':
                // просто помещаем в стек
                push(stack, st_ptr, c);
                break;

            case ')':
                // выталкиваем из стека в выходную строку все элементы до открывающей скобки (откр. скобку просто отбрасываем)
                while (st_ptr != 0)
                {
                    char op = pop(stack, st_ptr);	// забираем из стека оператор
                    if (op == '(')					// если достигли открывающей скобки
                        break;						// выталкивание закончили
                    else
                    {
                        _postfix[out_index++] = op;	// добавили оператор в выходную строку
                    }
                }
                break;

            case '^':
                // помещаем оператор в стек (выталкивать ничего не нужно, нет операторов с большим приоритетом)
                push(stack, st_ptr, c);
                break;

            default:		// символ цифры
                _postfix[out_index] = c;	// добавляем цифру в выходную строку
                out_index++;
                break;
        }

        in_index++;	// переходим к следующему символу входной строки
    }
    while (_infix[in_index] != 0);	// разбор закончен

    // выталкиваем все операторы в выходную строку
    while(st_ptr != 0)
        _postfix[out_index++] = pop(stack, st_ptr);

    // завершающий символ нуля
    _postfix[out_index] = 0;
}


void push(char *_stack, int &_ptr, char data)
{
    _stack[_ptr++] = data;
}

char pop(char *_stack, int &_ptr)
{
    return _stack[--_ptr];
}

void Postfix(){
    char str_infix[] = "(A-B-C)/D-E*F";
    char str_postfix[MAX_LEN];

    cout << str_infix << endl;
    PostfixNotation(str_infix, str_postfix);
    cout << str_postfix << endl;
}


int main (){
    bool isActive = true;
    Deque newDeque;

    while (isActive){
        int k;
        cout << "1. Add new element to deque \n2. Show deque \n3. Delete element\n4. Palindrome check \n5. Postfix form create \n";
        scanf("%i", &k);

        if(k == 1) {
            int key;
            cout << "1. Add new element to the beginning \n2. Add new element to the end \n";
            scanf("%i", &key);
            if (key == 1){
                cout << "Input your element: ";
                int value;
                cin >> value;
                if (value >= INT32_MAX){
                    cout << "Element is bigger than maximum" << endl;
                    continue;
                }
                newDeque.AddElementToBegin(value);
            }
            else if(key == 2){
                cout << "Input your element: ";
                int value;
                cin >> value;
                if (value >= INT32_MAX){
                    cout << "Element is bigger than maximum" << endl;
                    continue;
                }
                newDeque.AddElementToEnd(value);
            }
            else{
                cout << "Error. Input correct number";
                continue;
            }

            cout << "Your element has been added successfully";
            newDeque.ShowDeque();
            continue;
        }
        else if(k == 2){
            newDeque.ShowDeque();
            continue;
        }
        else if(k == 3){
            newDeque.ShowDeque();
            if (newDeque.newDeque.empty()) {
                continue;
            }
            cout << "Input position of element which you want to remove: ";
            int value;
            cin >> value;
            newDeque.DeleteElement(value);
            cout << "Element has been removed successfully. \n";
            newDeque.ShowDeque();
        }
        else if(k == 4){
            char issue = getchar();
            clear(issue);
            Palindrome();
            continue;
        }
        else if(k == 5){
            Postfix();
            continue;
        }
        else{
            cout << "Input correct value";
            continue;
        }

        cout << "Do you want to exit? (Enter 'y' to exit or any key to continue) \n";
        char key;
        cin >> key;
        if (key == 'y'){
            isActive = false;
        }
    }


    return 0;
}