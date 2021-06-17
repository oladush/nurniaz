#include <iostream>
#include "set.h"

using namespace std;
int main() {
    int arr1[] = {10, 20, 40, 30, 20};

    // способы задания множества
    Set set1 = Set(5);
    Set set2 = Set(arr1, size(arr1));
    Set set3 = Set(set1);

    cout << "set1: " << set1 << "Count: " << set1.Count() << endl;
    cout << "set2: " << set2 << "Count: " << set2.Count() << endl;
    cout << "set3: " << set3 << "Count: " << set3.Count() << endl;

    cout << "-----------------\n";

    // добавление элементов в множество
    int arr2[] = {23, 40, 45, 60};

    set1.AddToEnd(42);
    set1.AddToBegin(44);

    set2.AddRange(arr2, size(arr2));

    cout << "set1: " << set1 << "Count: " << set1.Count() << endl;
    cout << "set2: " << set2 << "Count: " << set2.Count() << endl;
    cout << "set3: " << set3 << "Count: " << set3.Count() << endl;

    cout << "-----------------\n";

    // удаление элементов из множества
    set1.Remove(44);
    set2.RemoveRange(arr1, size(arr2));

    cout << "set1: " << set1 << "Count: " << set1.Count() << endl;
    cout << "set2: " << set2 << "Count: " << set2.Count() << endl;
    cout << "set3: " << set3 << "Count: " << set3.Count() << endl;

    cout << "-----------------\n";

    // проверка на вхождение элементов в множество
    if (set1.Contains(&set3))
        cout << "set3 in set1\n";
    else
        cout << "set3 not in set1\n";

    int cnst = 3;
    if (set1.Contains(cnst))
        cout << cnst <<" in set1\n";
    else
        cout << cnst <<" not in set1\n";

    int arr3[] = {45, 60};

    cout << "[";
    for (int i = 0; i < size(arr3); i++)
        cout << arr3[i] << ", ";

    if (set2.Contains(arr3, size(arr3)))
    {
        cout << "] in set1\n";
    }
    else
        cout <<"] not in set1\n";

    cout << "-----------------\n";
    // операции над множествами

    Set Uni = set2 + set3;
    Set Inter = Uni * set1;
    Set Diff = Uni - set1;

    cout << "Uni: " << Uni << "Count: " << Uni.Count() << endl;
    cout << "Inter: " << Inter << "Count: " << Inter.Count() << endl;
    cout << "Diff: " << Diff << "Count: " << Diff.Count() << endl;

    // сортировка множества
    Uni.Sort();
    Uni.Print();

    return 0;
}
