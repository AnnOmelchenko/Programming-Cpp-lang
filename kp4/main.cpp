#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>

using namespace std;

FILE* file;


class Marks{
public:
    int math, ukrainian, english;
    Marks(int math = 0, int ukrainian = 0, int english = 0){
        this->math = math;
        this->ukrainian = ukrainian;
        this->english = english;
    }
};



void clear() {
    while (std::cin.get() != '\n')
    {
        continue;
    }
}

class Student{
public:
    char *firstName, *lastName, *patronymic, *address;
    long phoneNumber;
    bool isNewcomer;
    Marks marks;
    Student *next = NULL, *prev = NULL;
};

class DoublyLinkedList
{
private:
    Student* head = NULL;
    Student* tail = NULL;
    int realSize = 0;
public:
    int getRealSize() { return realSize; }

    void printList(int mode) {
        if (realSize == 0)
            std::cout << "List is empty\n";
        else {
            Student* current;
            int i;
            mode == 49 ? current = head : current = tail;
            mode == 49 ? i = 1 : i = realSize;
            while (current != NULL) {
                cout << "Student " << i << endl;
                cout << "Firstname: " << current->firstName << "\nLastname: " << current->lastName << "\nPatronymic: " << current->patronymic << "\nAddress: " << current->address << "\nIs newcomer: " << current->isNewcomer << "\nPhone number: " << current->phoneNumber << "\nMaths mark: " << current->marks.math << "\nUkrainian mark: " << current->marks.ukrainian << "\nEnglish mark: " << current->marks.english<< "\n\n";
                mode == 49 ? i++ : i--;
                mode == 49 ? current = current->next : current = current->prev;
            }
        }
    }

    void Swap(Student *first, Student *second)
    {
        Student *pp = first->prev, // элемент перед первым из переставляемой пары
        *lp = second->next;  // элемент после пары

        // переставим элементы
        second->prev = first->prev;
        first->next = second->next;
        first->prev = second;
        second->next = first;

        // скорректируем указатель на начало переставленной пары
        if (pp)
            pp->next = second;
        else
            this->head = second; // пара была первой в списке, корректируем указатель на весь список

        if (lp) // корректируем элемент списка после пары
            lp->prev = first;
    }

    void Sort()
    {
        Student *temp = this->head;
        while (temp->next)
        {
            if (temp->phoneNumber > temp->next->phoneNumber)
            {
                Swap(temp, temp->next);

                Sort();
            }
            else
                temp = temp->next;
        }
    }

    void push_back(char firstName[], char lastName[], char patronymic[], char address[], long phoneNumber,  bool isNewComer, int maths, int english, int ukrainian) {
        Student* newStudent = new Student;
        newStudent->firstName = firstName;
        newStudent->lastName = lastName;
        newStudent->patronymic = patronymic;
        newStudent->address = address;
        newStudent->isNewcomer = isNewComer;
        newStudent->marks.math = maths;
        newStudent->marks.english = english;
        newStudent->marks.ukrainian = ukrainian;
        if (realSize == 0)
            head = newStudent;
        else {
            Student* last = tail;
            tail->next = newStudent;
            newStudent->prev = last;
        }
        tail = newStudent;
        realSize++;
    }

    void push_forward(char firstName[], char lastName[], char patronymic[], char address[], long phoneNumber, bool isNewComer, int math, int english, int ukrainian) {
        Student* newNode = new Student;
        newNode->firstName = firstName;
        newNode->lastName = lastName;
        newNode->patronymic = patronymic;
        newNode->address = address;
        newNode->phoneNumber = phoneNumber;
        newNode->isNewcomer = isNewComer;
        newNode->marks.math = math;
        newNode->marks.english = english;
        newNode->marks.ukrainian = ukrainian;
        if (realSize == 0) {
            head = newNode;
            tail = newNode;
        }
        else {
            newNode->next = head;
            newNode->prev = NULL;
            head->prev = newNode;
            head = newNode;
        }
        realSize++;
    }

    void insertAfter(int position, char firstName[], char lastName[], char patronymic[], char address[], long phoneNumber, bool isNewComer, int maths, int english, int ukrainian) {
        if (realSize == 0) {
            return;
        }
        else if (position == realSize) {
            push_back(firstName, lastName, patronymic, address, phoneNumber, isNewComer, maths, english, ukrainian);
        }
        else {
            Student* newNode = new Student;
            newNode->firstName = firstName;
            newNode->lastName = lastName;
            newNode->patronymic = patronymic;
            newNode->address = address;
            newNode->phoneNumber = phoneNumber;
            newNode->isNewcomer = isNewComer;
            newNode->marks.math = maths;
            newNode->marks.english = english;
            newNode->marks.ukrainian = ukrainian;
            Student* current = head;
            for (int i = 1; i < position; i++)
                current = current->next;
            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;
            realSize++;
        }
    }

    void deleteNodeByNumber(int position, int mode) {
        if (realSize < position) {
            std::cout << "Такого порядкового номера не существует.\n";
            return;
        }
        else if (position == 1) {
            Student* temp = head;
            head = head->next;
            head->prev = NULL;
            delete temp;
        }
        else if (position == realSize) {
            Student* temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            delete temp;
        }
        else {
            Student* current = head;
            for (int i = 1; i < position - 1; i++)
                current = current->next;
            Student* temp = current->next;
            current->next->next->prev = current;
            current->next = current->next->next;
            delete temp;
        }
        realSize--;
        if (mode == 1)
            cout << "Successfully deleted!\n";
    }

    void deleteAllNodes() {
        Student* temp = new Student;
        while (head != NULL) {
            temp = head;
            head = head->next;
            delete temp;
            realSize--;
        }
        cout << "\nList successfully cleaned!\n";
    }



    void exportToFile() {
        if (realSize == 0) {
            cout << "List is empty.\n";
            return;
        }
        static char filename[100];
        printf("Enter filename: ");
        clear();
        scanf("%100[^\n]", filename);
        file = fopen(filename, "w");
        if (file != NULL)
            printf("File %s successfully created.\n", filename);
        else {
            printf("Error!\n", filename);
            return;
        }
        Student* current = head;
        char* char_arr;
        while (current != NULL) {
            char_arr = &current->firstName[0];
            fprintf(file, "%s\n%d\n%lf\n%lf\n", char_arr, current->lastName, current->patronymic, current->address);
            current = current->next;
        }
        fclose(file);
        cout << "\nList successfully exported!\n";
    }

    void seekElement(int mode) {
        Student* current;
        string str;

        bool isFound = false;
        bool checker = false;
        switch (mode)
        {
            case 1:
                cout << "Enter firstname to find student: ";
                clear();
                getline(cin, str);
                str += '\n';
                if (head->firstName == str) {
                    cout << "Found student: \n";
                    cout << "\nFirstname: " << head->firstName << "\nLastname: " << head->lastName << "\nPatronymic: " << head->patronymic << "\nAddress: " << head->address << "\n\n";
                    //getchar();
                    //return;
                    isFound = true;
                }
                current = head;
                while (current != tail) {
                    if(current->next->firstName == str) {
                        current = current->next;
                        cout << "Found student: \n";
                        cout << "\nFirstname: " << current->firstName << "\nLastname: " << current->lastName << "\nPatronymic: " << current->patronymic << "\nAddress: " << current->address << "\n\n";
                        //getchar();
                        //return;
                        checker = true;
                        isFound = true;
                    }
                    if (!checker)
                        current = current->next;
                    checker = false;
                }
                if(isFound == false)
                    cout << "Not found.\n";
                break;

            case 2:
                cout << "Enter lastname to find student: ";
                clear();
                getline(cin, str);
                str += '\n';

                if (head->lastName == str) {
                    cout << "Found student: \n";
                    cout << "\nFirstname: " << head->firstName << "\nLastname: " << head->lastName << "\nPatronymic: " << head->patronymic << "\nAddress: " << head->address << "\n\n";
                    //getchar();
                    //return;
                    isFound = true;
                }
                current = head;
                while (current != tail) {
                    if (current->next->lastName == str) {
                        current = current->next;
                        cout << "Found student: \n";
                        cout << "\nFirstname: " << current->firstName << "\nLastname: " << current->lastName << "\nPatronymic: " << current->patronymic << "\nAddress: " << current->address << "\n\n";
                        //getchar();
                        //return;
                        checker = true;
                        isFound = true;
                    }
                    if (!checker)
                        current = current->next;
                    checker = false;
                }
                if(isFound == false)
                    cout << "Not found.\n";
                break;

            case 3:
                cout << "Enter patronymic to find student: ";
                clear();
                getline(cin, str);
                str += '\n';

                if (head->patronymic == str) {
                    cout << "Found student: \n";
                    cout << "\nFirstname: " << head->firstName << "\nLastname: " << head->lastName << "\nPatronymic: " << head->patronymic << "\nAddress: " << head->address << "\n\n";
                    //getchar();
                    //return;
                    isFound = true;
                }
                current = head;
                while (current != tail) {
                    if (current->next->patronymic == str) {
                        current = current->next;
                        cout << "Found student: \n";
                        cout << "\nFirstname: " << current->firstName << "\nLastname: " << current->lastName << "\nPatronymic: " << current->patronymic << "\nAddress: " << current->address << "\n\n";
                        //getchar();
                        //return;
                        checker = true;
                        isFound = true;
                    }
                    if (!checker)
                        current = current->next;
                    checker = false;
                }
                if(isFound == false)
                    cout << "Not found.\n";
                break;

            case 4:
                cout << "Enter address to find student: ";
                clear();
                getline(cin, str);
                str += '\n';

                if (head->address == str) {
                    cout << "Found student: \n";
                    cout << "\nFirstname: " << head->firstName << "\nLastname: " << head->lastName << "\nPatronymic: " << head->patronymic << "\nAddress: " << head->address << "\n\n";
                    //getchar();
                    //return;
                    isFound = true;
                }
                current = head;
                while (current != tail) {
                    if (current->next->address == str) {
                        current = current->next;
                        cout << "Found student: \n";
                        cout << "\nFirstname: " << current->firstName << "\nLastname: " << current->lastName << "\nPatronymic: " << current->patronymic << "\nAddress: " << current->address << "\n\n";
                        //getchar();
                        //return;
                        checker = true;
                        isFound = true;
                    }
                    if (!checker)
                        current = current->next;
                    checker = false;
                }
                if(isFound == false)
                    cout << "Not found.\n";
                break;
        }
    }




    void deleteNodeByKey() {
        bool isFound = false;
        bool deleted = false;
        Student* current;
        double var; string s;
        long value;
        cout << "Enter key 'Phone number' that will be deleted: ";
        while (scanf("%li", &value) != 1 || getchar() != '\n') {
            printf("Incorrect input. Try again: ");
            clear();
        }
        while (head->phoneNumber == value  && realSize != 1) {
            Student* temp = head;
            head = head->next;
            head->prev = NULL;
            delete temp;
            realSize--;
            isFound = true;
        }
        while (tail->phoneNumber == value && realSize != 1) {
            Student* temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            delete temp;
            realSize--;
            isFound = true;
        }
        current = head;
        while (current->next != tail && realSize != 1) {
            if (current->next->phoneNumber == value) {
                Student* temp = current->next;
                current->next->next->prev = current;
                current->next = current->next->next;
                delete temp;
                realSize--;
                deleted = true;
                isFound = true;
            }
            if (!deleted)
                current = current->next;
            deleted = false;
        }
        if (realSize == 1 && head->phoneNumber == value) {
            delete head;
            realSize--;
            isFound = true;
        }
        if (isFound == true)
            printList(49);
        else

            cout << "No elements with such value.\n";
    }


    void Add(char *firstName, char *lastName, char *patronymic, char *address, long phoneNumber, bool isNewcomer,
             Marks *marks);
};

void DoublyLinkedList::Add(char *firstName = NULL, char *lastName = NULL , char *patronymic = NULL,
                           char *address = NULL, long phoneNumber = 0, bool isNewcomer = 0, Marks *marks = new Marks())
{
    realSize++;
    Student *temp = new Student;
    temp->next = NULL;
    temp->firstName = firstName;
    temp->lastName = lastName;
    temp->patronymic = patronymic;
    temp->address = address;
    temp->phoneNumber = phoneNumber;
    temp->isNewcomer = isNewcomer;
    temp->marks = *marks;

    if (head != NULL)
    {
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
    }
    else
    {
        temp->prev = NULL;
        head = tail = temp;
    }
}

DoublyLinkedList list;


void addStudent(){
    char *firstName = new char[100], *lastName = new char[100], *patronymic = new char[100], *address = new char[100];
    char *condition = new char[100];
    bool isNewcomer;
    int k, math, ukrainian, english;
    long phoneNumber;
    cout << "Enter firstname of the Student: ";
    int i = 0;
    do {
        firstName[i] = getchar();
        ++i;
    }
    while (firstName[i-1]!='\n');

    cout << "Enter lastname of the Student: ";
    i = 0;
    do {
        lastName[i] = getchar();
        ++i;
    }
    while (lastName[i-1]!='\n');

    cout << "Enter patronymic of the Student: ";
    i = 0;
    do {
        patronymic[i] = getchar();
        ++i;
    }
    while (patronymic[i-1]!='\n');

    cout << "Enter address of the Student: ";
    i = 0;
    do {
        address[i] = getchar();
        ++i;
    }
    while (address[i-1]!='\n');



    cout << "Enter is the Student a newcomer [true/false]: ";
    i = 0;
    do {
        condition[i] = getchar();
        ++i;
    }
    while (condition[i-1]!='\n');

    if (strcmp(condition, "true\n") == 0){
        isNewcomer = true;
    }

    cout << "Enter math mark of the Student: ";
    scanf("%i", &math);

    cout << "Enter ukrainian language mark of the Student: ";
    scanf("%i", &ukrainian);

    cout << "Enter english language mark of the Student: ";
    scanf("%i", &english);

    cout << "Enter phone number of the Student: ";
    scanf("%li", &phoneNumber);

    list.Add(firstName, lastName, patronymic, address, phoneNumber, isNewcomer, new Marks(math, ukrainian, english));

}


int getCriterion() {
    cout << "Criteria:\n1 - Firstname\n2 - Lastname \n3 - Patronymic\n4 - Address\n";
    int ch;
    printf("My choice: ");
    while (scanf("%d", &ch) != 1 || ch < 1 || ch > 4) {
        printf("\nIncorrect input! Try again. ");
        clear();
    }
    return ch;
}



int main()
{
    char *firstName = new char[100], *lastName = new char[100], *patronymic = new char[100], *address = new char[100];
    double phoneNumber;
    bool isNewComer;
    int maths, english, ukrainian;
    int choice, shutdown = 0;
    do {
        //system("cls");
        printf("* STUDENT\" *\n\n");
        printf("1. Add student\n"); // 1 DONE
        printf("2. Export to file\n"); // 2 DONE
        printf("3. Show list\n"); // 3 DONE
        printf("4. Find element by criteria\n"); // 4 DONE
        printf("5. Add to head\n"); // 5 DONE
        printf("6. Add to tail\n"); // 6 DONE
        printf("7. Insert after any\n"); // 7 DONE
        printf("8. Sort\n"); // 8 DONE
        printf("9. Delete element\n"); // 9 DONE
        printf("10. Delete element by value\n"); // 9 DONE
        printf("11. Clear list\n"); // 10 DONE
        printf("12. Leave program\n"); // 12 DONE
        printf("\nMy choice: ");
        while (scanf("%d", &choice) != 1 || choice < 1 || choice > 12) {
            printf("\nIncorrect input. Try again: ");
            clear();
        }

        switch (choice)
        {
            case 1:
                clear();
                addStudent();
                break;

            case 2:
                //system("cls");
                list.exportToFile();
                printf("Enter any key to continue.\n");
                getchar();
                break;

            case 3:
                //system("cls");
                cout << "\n1 - Вывод от головы до хвоста \n2 - Вывод от хвоста до головы\nMy choice: ";
                int mode;
                do {
                    mode = getchar();
                } while (mode != 49 && mode != 50);
                cout << endl;
                list.printList(mode);
                printf("Enter any key to continue.\n");
                getchar();
                break;

            case 4:
                //system("cls");
                int a;
                a = getCriterion();
                list.seekElement(a);
                printf("Enter any key to continue.\n");
                getchar();
                break;

            case 5:
                //system("cls");
                cout << "Enter new student:\n1. Firstname: ";
                clear(); scanf("%100[^\n]", firstName);
                cout << "2. Lastname: ";
                clear(); scanf("%100[^\n]", lastName);
                cout << "3. Patronymic: ";
                clear(); scanf("%100[^\n]", patronymic);
                cout << "4. Address: ";
                clear(); scanf("%100[^\n]", address);
                cout << "5. Phone number: ";
                while (scanf("%d", &phoneNumber) != 1 || getchar() != '\n') {
                    printf("Incorrect input! Try again: ");
                    clear();
                }
                cout << "6. Is newcomer: ";
                {
                    char *str = new char[100];
                    fgets(str, 100, stdin);
                    if (strcmp(str, "true\n") == 0) {
                        isNewComer = true;
                    } else {
                        isNewComer = false;
                    }
                }
                cout << "7. Maths mark: ";
                while (scanf("%i", &maths) != 1 || getchar() != '\n') {
                    printf("Incorrect input! Try again: ");
                    clear();
                }
                cout << "8. English mark: ";
                while (scanf("%i", &english) != 1 || getchar() != '\n') {
                    printf("Incorrect input! Try again: ");
                    clear();
                }
                cout << "9. Ukrainian mark: ";
                while (scanf("%i", &ukrainian) != 1 || getchar() != '\n') {
                    printf("Incorrect input! Try again: ");
                    clear();
                }
                list.push_forward(firstName, lastName, patronymic, address, phoneNumber, isNewComer, maths, english, ukrainian);
                printf("Enter any key to continue.\n");
                getchar();
                break;

            case 6:
                cout << "Enter new student:\n1. Firstname: ";
                clear(); scanf("%100[^\n]", firstName);
                cout << "2. Lastname: ";
                clear(); scanf("%100[^\n]", lastName);
                cout << "3. Patronymic: ";
                clear(); scanf("%100[^\n]", patronymic);
                cout << "4. Address: ";
                clear(); scanf("%100[^\n]", address);
                cout << "5. Phone number: ";
                while (scanf("%d", &phoneNumber) != 1 || getchar() != '\n') {
                    printf("Incorrect input! Try again: ");
                    clear();
                }
                cout << "6. Is newcomer: ";
                {
                    char *str = new char[100];
                    fgets(str, 100, stdin);
                    if (strcmp(str, "true\n") == 0) {
                        isNewComer = true;
                    } else {
                        isNewComer = false;
                    }
                }
                cout << "7. Maths mark: ";
                while (scanf("%d",&maths) != 1 || getchar() != '\n') {
                    printf("Incorrect input! Try again: ");
                    clear();
                }
                cout << "8. English mark: ";
                while (scanf("%d", &english) != 1 || getchar() != '\n') {
                    printf("Incorrect input! Try again: ");
                    clear();
                }
                cout << "9. Ukrainian mark: ";
                while (scanf("%d", &ukrainian) != 1 || getchar() != '\n') {
                    printf("Incorrect input! Try again: ");
                    clear();
                }
                list.push_back(firstName, lastName, patronymic, address, phoneNumber, isNewComer, maths, english, ukrainian);
                printf("Enter any key to continue.\n");
                getchar();
                break;


            case 7:
                //system("cls");
                list.printList(49);
                if (list.getRealSize() <= 0) {
                    getchar();
                    break;
                }
                int position;
                cout << "Введите номер элемента, после которого будет добавлен новый: ";
                while (scanf("%d", &position) != 1 || position <= 0 || position > list.getRealSize() || getchar() != '\n') {
                    printf("Incorrect input! Try again: ");
                    clear();
                }
                cout << "Enter new student:\n1. Firstname: ";
                clear(); scanf("%100[^\n]", firstName);
                cout << "2. Lastname: ";
                clear(); scanf("%100[^\n]", lastName);
                cout << "3. Patronymic: ";
                clear(); scanf("%100[^\n]", patronymic);
                cout << "4. Address: ";
                clear(); scanf("%100[^\n]", address);
                cout << "5. Phone number: ";
                while (scanf("%d", &phoneNumber) != 1 || getchar() != '\n') {
                    printf("Ошибка ввода! Попробуйте снова: ");
                    clear();
                }
                cout << "6. Is newcomer: ";
                {
                    char *str = new char[100];
                    fgets(str, 100, stdin);
                    if (strcmp(str, "true\n") == 0) {
                        isNewComer = true;
                    } else {
                        isNewComer = false;
                    }
                }
                cout << "7. Maths mark: ";
                while (scanf("%d",&maths) != 1 || getchar() != '\n') {
                    printf("Incorrect input! Try again: ");
                    clear();
                }
                cout << "8. English mark: ";
                while (scanf("%d", &english) != 1 || getchar() != '\n') {
                    printf("Incorrect input! Try again: ");
                    clear();
                }
                cout << "9. Ukrainian mark: ";
                while (scanf("%d", &ukrainian) != 1 || getchar() != '\n') {
                    printf("Incorrect input! Try again: ");
                    clear();
                }
                list.insertAfter(position, firstName, lastName, patronymic, address, phoneNumber, isNewComer, maths, english, ukrainian);
                cout << "Элемент был успешно вставлен!\n";
                printf("Enter any key to continue.\n");
                getchar();
                break;




            case 8:
                //system("cls");
                list.Sort();
                cout << "List sorted successfully \n";
                printf("Enter any key to continue.\n");
                getchar();
                break;

            case 9:
                //system("cls");
                list.printList(49);
                int x;
                cout << "\nВведите порядковый номер элемента: ";
                while (scanf("%d", &x) != 1 || x < 1 || getchar() != '\n') {
                    printf("Incorrect input! Try again: ");
                    clear();
                }
                list.deleteNodeByNumber(x, 1);
                printf("Enter any key to continue.\n");
                getchar();
                break;

            case 10:
                //system("cls");
                if (list.getRealSize() == 0) {
                    cout << "List is empty.\n";
                    getchar();
                    break;
                }
                list.printList(49);
                list.deleteNodeByKey();
                printf("Enter any key to continue.\n");
                getchar();
                break;



            case 11:
                list.deleteAllNodes();
                printf("Enter any key to continue.\n");
                getchar();
                break;


            case 12:
                fclose(file);
                shutdown = 1;
                break;

            default: break;
        }

    } while (shutdown != 1);
    return 0;
}