#include <iostream>
// Лабораторная работа №1 по АиСД, тема "Списки", выполнила Марзаева Вера Игоревна, гр. 1302
using namespace std;

struct List { // a list item that stores an integer value
    int a;
    List* head; // pointer to the head element
    List* next; // pointer to the next element
    List* prev; // pointer to the previous element
    ~List() {
        a = -1000;
        head = nullptr;
        next = nullptr;
        prev = nullptr;
    }
    List() {
        a = -1000;
        head = nullptr;
        next = nullptr;
        prev = nullptr;
    }
    List(int a) {
        this->a = a;
        head = nullptr;
        next = nullptr;
        prev = nullptr;
    }
    List(int a, List* next) {
        this->a = a;
        head = nullptr;
        this->next = next;
        prev = nullptr;
    }
    List(int a, List* head, List* prev) {
        this->a = a;
        this->head = head;
        this->prev = prev;
        next = nullptr;
    }
    List(int a, List* head, List* next, List* prev) {
        this->a = a;
        this->head = head;
        this->prev = prev;
        this->next = next;
    }
    void PushBack(int a); //declaration of the function of adding to the end of the list
    void PushFront(int a); //declaring the function of adding to the top of the list
    void PopBack(); //declaring a function to delete the last element
    void PopFront(); //declaration of the function for deleting the first element
    int GetIndex(int a); // declaring a function for getting an element by index
    void PopIndex(int i); // declaring the function of deleting an element by index
    void AddIndex(int i, int a); // declaring the function of adding an element by index
    int GetSize(); // declaring a function for getting the list size
    void Clear(); // declaring a function to delete all list items
    void SetIndex(int i, int a); // declaration of the function of replacing an element by an index with a passed element
    bool Empty(); // declaration of a list emptiness check function
    int Search(List b); // declaring a search function for the first occurrence of another list in the list
};

int main()
{
    setlocale(0, "ru");
    List a;
    int h;
    cout << "Введите первый (целочисленный) список. Для завершения ввода введите -1000." << endl;
    while (1) // entering the first list
    {
        cin >> h;
        if(h!=-1000)
            a.PushBack(h);
        if (h == -1000)
            break;
    }
    cout << "Список: ";
    for (int i = 0; i < a.GetSize(); i++) { //output of the first list
        cout << a.GetIndex(i) << " ";
    }
    cout << endl << endl;
    List b;
    cout << "Введите второй (целочисленный) список. Для завершения ввода введите -1000." << endl;
    while (1) // entering the second list
    {
        cin >> h;
        if (h != -1000)
            b.PushBack(h);
        if (h == -1000)
            break;
    }
    while (1)
    {
        cout << "Введите номер функции, которую хотите проверить" << endl;
        cout << "1. удаление последнего элемента" << endl;
        cout << "2. удаление первого элемента" << endl;
        cout << "3. добавление элемента по индексу(вставка перед элементом, который был ранее доступен по этому индексу)" << endl;
        cout << "4. замена элемента по индексу на передаваемый элемент" << endl;
        cout << "5. удаление элемента по индексу" << endl;
        cout << "6. получение размера списка" << endl;
        cout << "7. удаление всех элементов списка" << endl;
        cout << "8. получение элемента по индексу" << endl;
        cout << "9. добавление в конец списка" << endl;
        cout << "10. добавление в начало списка" << endl;
        cout << "11. проверка на пустоту списка" << endl << endl;
        cout << "Введите 12, если хотите проверить релизацию метода поиска первого вхождения другого списка в список" << endl << endl;
        cout << "Для завершения работы программы введите 0" << endl;
        cin >> h;
        if (h >= 0 && h <= 12)
        {
            if (h == 1)
            {
                a.PopBack();
            }
            if (h == 2)
            {
                a.PopFront();
            }
            if (h == 3)
            {
                int i, a1;
                cout << "Введите новый элемент (целочисленный)" << endl;
                cin >> a1;
                cout << "Введите индекс элемента, не больше " << a.GetSize() - 1 << endl;
                cin >> i;
                a.AddIndex(i, a1);
            }
            if (h == 4)
            {
                int i, a1;
                cout << "Введите новый элемент (целочисленный)" << endl;
                cin >> a1;
                cout << "Введите индекс элемента, не больше " << a.GetSize() - 1 << endl;
                cin >> i;
                a.SetIndex(i, a1);
            }
            if (h == 5)
            {
                int i;
                cout << endl << "Введите индекс элемента, не больше " << a.GetSize() - 1 << endl;
                cin >> i;
                a.PopIndex(i);
            }
            if (h == 6)
            {
                cout << "Размер списка: " << a.GetSize() << endl;
            }
            if (h == 7)
            {
                a.Clear();
            }
            if (h == 8)
            {
                int i;
                cout << "Введите индекс элемента, не больше " << a.GetSize() - 1 << endl;
                cin >> i;
                cout << endl << a.GetIndex(i) << endl;
            }
            if (h == 9)
            {
                int a1;
                cout << "Введите новый элемент" << endl;
                cin >> a1;
                a.PushBack(a1);
            }
            if (h == 10)
            {
                int a1;
                cout << "Введите новый элемент" << endl;
                cin >> a1;
                a.PushFront(a1);
            }
            if (h == 11)
            {
                if (a.Empty())
                    cout << "ПУСТОЙ" << endl;
                else
                    cout << "НЕ ПУСТОЙ" << endl;
            }
            if (h == 0)
            {
                break;
            }
            if (h == 12)
            {
                cout << "Ответ: " << a.Search(b) << endl;
                cout << "Список 1: ";
                for (int i = 0; i < a.GetSize(); i++) {
                    cout << a.GetIndex(i) << " ";
                }
                cout << endl;
                cout << "Список 2: ";
                for (int i = 0; i < b.GetSize(); i++) {
                    cout << b.GetIndex(i) << " ";
                }
                cout << endl;
            }
            else {
                cout << "Список: ";
                for (int i = 0; i < a.GetSize(); i++) {
                    cout << a.GetIndex(i) << " ";
                }
                cout << endl;
            }
        }
        else
            cout << "Неверный ввод, попробуйте еще раз!" << endl;
    }
    a.Clear();
    cout << "Размер списка: " << a.GetSize() << endl;
}

int List::Search(List b) { //search for the first occurrence of another list in the list
    if (b.GetSize() > GetSize()) return -1;
    int n = GetSize();
    for (int i = 0; i < n; i++) {
        int x = 1;
        for (int j = 0; j < b.GetSize(); j++) {
            if (i + j >= n) return -1;

            if (GetIndex(i + j) != b.GetIndex(j)) { 

                x = 0;
                break;
            }
        }
        if (x) return i;
    }
    return -1;
}

void List::PushBack(int a) { // adding to the end of the list
    if (Empty()) {
        head = new List(a);
        return;
    }
    List* cur = head;
    while (cur->next != nullptr) cur = cur->next;
    cur->next = new List(a, head, cur);
}

void List::PushFront(int a) { // adding to the top of the list
    if (Empty()) {
        head = new List(a);
        return;
    }
    List* tmp = new List(a, head);
    head->prev = tmp;
    head = tmp;
}

void List::PopBack() { // deleting the last element
    List* cur = head;
    while (cur->next != nullptr) cur = cur->next;
    List* p = cur;
    p = p->prev;
    p->next = nullptr;
    delete cur;
}

void List::PopFront() { // deleting the first element
    List* tmp = head;
    head = head->next;
    head->prev = nullptr;
    delete tmp;
}

void List::AddIndex(int i, int a) { // adding an element by index
    if (i == 0) {
        PushFront(a);
        return;
    }
    List* cur = head;
    List* p = head;
    while (i--) {
        p = cur;
        cur = cur->next;
    }
    p->next = new List(a, head, p->next, cur->prev);
    cur->prev = p->next;
}

void List::SetIndex(int i, int a) { // replacing an element by index with the transmitted element
    List* cur = head;
    while (i--) {
        cur = cur->next;
    }
    cur->a = a;
}

void List::PopIndex(int i) { // deleting an item by index
    if (i == 0) {
        PopFront();
        return;
    }
    if (i + 1 == GetSize()) {
        PopBack();
        return;
    }
    List* cur = head;
    while (i--) cur = cur->next;
    List* p = cur->prev;
    List* p2 = cur->next;
    delete cur;
    p->next = p2;
    p2->prev = p;
}

int List::GetSize() { // getting the list size
    List* cur = head;
    int ans = 0;
    while (cur != nullptr) {
        ans++;
        cur = cur->next;
    }
    return ans;
}

void List::Clear() { //deleting all list items
    List* cur;
    while (head != nullptr) {
        cur = head;
        head = next;
        delete cur;
    }
}

int List::GetIndex(int a) { // getting an item by index
    List* cur = head;
    while (a--) {
        cur = cur->next;
    }
    return cur->a;
}

bool List::Empty() { // checking for the emptiness of the list
    return head == nullptr;
}