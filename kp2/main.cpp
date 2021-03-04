#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

void Show(vector<int> array, unsigned long long time, string name){
//    for (int i = 0; i < array.size(); ++i) {
//        cout << array[i] << " ";
//    }
    cout << endl << "Time of " << name << " sort is " << time << " ms" << endl;

}

void ChoiceSort(vector<int> arr){
    int min, t, num, counter = 0;
    unsigned long long start_time = clock();

    for (int i = 0; i < arr.size() - 1; ++i) {
        t = 0;
        num = i;
        min = arr[i];
        for (int j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < min){
                if (arr[j] == min){
                    counter++;
                }
                num = j;
                min = arr[j];
                t = 1;
            }
        }
        if (t == 1){
            arr[num] = arr[i];
            arr[i] = min;
        }
    }

    unsigned long long end_time = clock();
    Show(arr, end_time - start_time, "Choice");

}

void InsertSort(vector<int> arr){
    unsigned long long start_time = clock();

    for(int i = 1; i < arr.size(); i++){
        for(int j = i; j > 0 && arr[j - 1] > arr[j]; j--){
            int tmp = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = tmp;
        }
    }
    unsigned long long end_time = clock();
    Show(arr, end_time - start_time, "Insert");
}

void BubbleSort(vector<int> arr){
    unsigned long long start_time = clock();

    for (int i = 0; i < arr.size() - 1; ++i) {
        for (int j = 0; j < arr.size() - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }

    unsigned long long end_time = clock();
    Show(arr, end_time - start_time, "Bubble");
}

void ShakerSort(vector<int> arr){
    int k = arr.size() - 1, lb = 1, ub = arr.size() - 1, x;
    unsigned long long start_time = clock();

    do {
        for (int i = ub; i > 0; --i) {
            if (arr[i - 1] > arr[i]) {
                x = arr[i - 1];
                arr[i - 1] = arr[i];
                arr[i] = x;
                k = i;
            }
        }
        lb = k + 1;
        for (int i = 1; i <= ub; ++i) {
            if (arr[i - 1] > arr[i]){
                x = arr[i - 1];
                arr[i - 1] = arr[i];
                arr[i] = x;
                k = i;
            }
        }
        ub = k - 1;
    } while (lb < ub);

    unsigned long long end_time = clock();
    Show(arr, end_time - start_time, "Shaker");
}

vector<int> Random(int quantity){
    vector<int> arr;

    for (int i = 0; i < quantity; ++i) {
        arr.push_back(rand() % 8);
    }

    return arr;
}


int main() {
    int size, n;
    srand(time(NULL));
    printf("\nSelect array size:\n 1. 2200 \n 2. 22000 \n 3. 200000\n My choice: ");
    scanf("%d", &size);
    switch (size) {
        case 1:
            n = 2200;
            break;
        case 2:
            n = 22000;
            break;
        case 3:
            n = 200000;
            break;
        default:
            n = 2200;
    }

    vector <int> array = Random(n);
    ChoiceSort(array);
    InsertSort(array);
    BubbleSort(array);
    ShakerSort(array);
    return 0;
}
