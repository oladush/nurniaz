#include <iostream>
#include "list.h"

using namespace std;

int main() {
    int arr1[] = {1, 2, 3, 4, 5};

    List list1;
    List list2(5);
    List list3(arr1, size(arr1));

    cout << "list1: " << list1 << " size: " << list1.ListSize() << endl;
    cout << "list2: " << list2 << " size: " << list2.ListSize() << endl;
    cout << "list3: " << list3 << " size: " << list3.ListSize() << endl;
    cout << "-----------------\n";

    // добавление элементов в список
    list1.AddToTail(42);
    list2.AddToHead(34);
    list3.AddAfterPos(3, 24);

    cout << "list1: " << list1 << "size: " << list1.ListSize() << endl;
    cout << "list2: " << list2 << "size: " << list2.ListSize() << endl;
    cout << "list3: " << list3 << "size: " << list3.ListSize() << endl;
    cout << "-----------------\n";

    // доступ к элементам списка
    cout << list3[4] << endl; // получить элемент по индексу
    list3.SetIndex(2, 2021); // установить элемент по индексу
    cout << list3[2] << endl;

    // сложение списков
    List sum;
    sum = list2 + list3;
    sum += list1;

    sum.Sort(); // сортировка
    cout << "Sum: " << sum << "size: " << sum.ListSize() << endl;

    // удаление элементов списка
    list1.DelToHead();
    list2.DelToTail();
    list3.DelTo(sum.FindPos(3));

    cout << "list1: " << list1 << "size: " << list1.ListSize() << endl;
    cout << "list2: " << list2 << "size: " << list2.ListSize() << endl;
    cout << "list3: " << list3 << "size: " << list3.ListSize() << endl;
    cout << "-----------------\n";

    // проверка на равенство

    if (list3 == list2)
        cout << "list3 equals list2\n";
    else
        cout << "list3 not equals list2\n";

    List* list4 = new List(list3);

    if (list3 == *list4)
        cout << "list3 equals list4\n";
    else
        cout << "list3 not equals list4\n";

    // очистка списка
    list1.Clear();
    cout << "list1: " << list1 << "size: " << list1.ListSize() << endl;

    // удаление списка
    delete list4;

    return 0;
}
