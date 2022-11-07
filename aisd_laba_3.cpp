#include <iostream>
#include <algorithm>

using namespace std;

const int N = 10; // max array size
int b[2 * N];


void insertion_sort(int a[]) { // insertion sort
    for (int i = 1; i < N; i++) {
        for (int j = i; j > 0; j--) {
            if (a[j] < a[j - 1]) {
                int t = a[j];
                a[j] = a[j - 1];
                a[j - 1] = t;
            }
        }
    }
}

void selection_sort(int a[]) { // selection sort
    for (int i = 0; i < N; i++) {
        int nmin = i;
        for (int j = i + 1; j < N; j++) {
            if (a[j] < a[nmin]) nmin = j;
        }
        int t = a[i];
        a[i] = a[nmin];
        a[nmin] = t;
    }
}

void bubble_sort(int a[]) { // bubble sort
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (a[j] < a[i]) {
                int t = a[j];
                a[j] = a[i];
                a[i] = t;
            }
        }
    }
}


void merge_sort(int(&a)[N], int l, int r) { // merge sort
    if (r - l == 1) return;

    int m = (l + r) / 2;
    merge_sort(a, l, m);
    merge_sort(a, m, r);

    int left = l;
    int right = (l + r) / 2;

    for (int i = l; i < r; i++) {
        if (left == m) {
            b[i] = a[right++];
        }
        else if (right == r) {
            b[i] = a[left++];
        }
        else {
            if (a[right] < a[left]) b[i] = a[right++];
            else b[i] = a[left++];
        }
    }

    for (int i = l; i < r; i++) {
        a[i] = b[i];
    }
}

void shell_sort(int a[]) { // shell sort
    int h = 1;
    while (h < N / 3) {
        h = 3 * h + 1;
    }
    while (h > 0) {
        for (int i = 0; i < h; i++) {
            for (int j = i + h; j < N; j += h) {
                if (a[j] < a[j - h]) {
                    for (int k = j; k >= h; k -= h) {
                        if (a[k] > a[k - h]) break;
                        int t = a[k];
                        a[k] = a[k - h];
                        a[k - h] = t;
                    }
                }

            }
        }
        h /= 3;
    }
}

void quick_sort(int a[], int l, int r) { // quick sort
    if (l + 1 >= r) return;

    int pivot = a[r - 1];
    int left = l;

    for (int i = l; i < r; i++) {
        if (a[i] < pivot) {
            int t = a[i];
            a[i] = a[left];
            a[left++] = t;
        }
    }
    int t = a[r - 1];
    a[r - 1] = a[left];
    a[left] = t;
    quick_sort(a, l, left);
    quick_sort(a, left + 1, r);
}

int main()
{
    setlocale(0, "ru"); // russian text
    int tmp;
    while (1)
    {
        int a[N] = { 3, 5, 7, 8, 2, 1, 4, 6, 9, 0 }; // unsorted array
        cout << endl << "Исходный массив:" << endl; 
        for (int i = 0; i < N; i++)
            cout << a[i] << " ";
        cout << endl;
        cout << "1. Сортировка вставками (Insertion sort)" << endl;
        cout << "2. Сортировка выбором (Selection sort)" << endl;
        cout << "3. Пузырьковая сортировка (Bubble sort)" << endl;
        cout << "4. Сортировка слиянием (Merge sort)" << endl;
        cout << "5. Сортировка Шелла (Shell sort)" << endl;
        cout << "6. Быстрая сортировка (Quick sort)" << endl << endl;
        cout << "Выберите сортировку (введите ее номер). Если хотите завершить программу, нажмите 0" << endl;
        cin >> tmp; // choice of sort
        if (tmp > 6 || (tmp < 1 && tmp != 0))
            cout << "Неверное значение, попробуйте еще раз" << endl;
        if (tmp == 1) {
            insertion_sort(a);
            for (int i = 0; i < N; i++)
                cout << a[i] << " ";
            cout << endl;
        }
        if (tmp == 2) {
            selection_sort(a);
            for (int i = 0; i < N; i++)
                cout << a[i] << " ";
            cout << endl;
        }
        if (tmp == 3) {
            bubble_sort(a);
            for (int i = 0; i < N; i++)
                cout << a[i] << " ";
            cout << endl;
        }
        if (tmp == 4) {
            merge_sort(a, 0, N);
            for (int i = 0; i < N; i++)
                cout << a[i] << " ";
            cout << endl;
        }
        if (tmp == 5) {
            shell_sort(a);
            for (int i = 0; i < N; i++)
                cout << a[i] << " ";
            cout << endl;
        }
        if (tmp == 6) {
            quick_sort(a, 0, N);
            for (int i = 0; i < N; i++)
                cout << a[i] << " ";
            cout << endl;
        }
        if (tmp == 0)
            break; // program shutdown
    }
}