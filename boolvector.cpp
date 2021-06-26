#include <iostream>
#include "boolvector.h"

using namespace std;
int main() {
    char arr1[] = {'1', '1', '0', '1', '1', '0', '1', '0', '1'};
    bool arr2[] = {1, 0, 0, 1, 1};

    // способы задания векторов
    BoolVector vec1(5);
    BoolVector vec2(arr1, size(arr1));
    BoolVector vec3 = vec2 >> 3; // побитовый сдвиг влево
    BoolVector vec4(arr2, size(arr2));

    cout << "vec1: " << vec1 << "real size: " << vec1.RealSize() << endl;
    cout << "vec2: " << vec2 << "real size: " << vec2.RealSize() << endl;
    cout << "vec3: " << vec3 << "real size: " << vec3.RealSize() << endl;
    cout << "vec4: " << vec4 << "real size: " << vec4.RealSize() << endl;
    cout << "---------------\n";

    // сравнение векторов
    if (vec2 > vec1)
        cout << "vec2 > vec1\n";
    else
        cout << "vec2 <= vec1\n";

    if (vec2 < vec3)
        cout << "vec2 < vec3\n";
    else
        cout << "vec2 >= vec3\n";

    BoolVector vec = vec2>>3;
    if (vec3 == vec)
        cout << "vec3 == (vec2 >> 3)\n";
    else
        cout << "vec3 != (vec2 >> 3)\n";

    // побитовые операции
    cout << "vec2 & vec3: ";
    (vec2 & vec3).Print();

    cout << "vec2 | vec3: ";
    (vec2 | vec3).Print();

    cout << "vec2 ^ vec3: ";
    (vec2 ^ vec3).Print();

    cout << "vec2 EQ vec3: ";
    (vec2.EQ(vec3)).Print();

    cout << "~vec3: ";
    (~vec3).Print();

    // побитовые сдвиги
    cout << "vec3 << 4: ";
    (vec3 << 4).Print();

    cout << "vec3 >> 2: ";
    (vec3 >> 2).Print();

    // доступ по индексу,
    // 0 - элемент младщий бит вектора. Чтобы получить старший бит(первый) нужно обратиться по индексу -1

    vec3.SetIndex(-1, 0);
    cout << "vec3: " << vec3 << "real size: " << vec3.RealSize() << endl;
    vec = vec3.SetUp(0, 1);
    cout << "vec: " << vec << "real size: " << vec.RealSize() << endl;

    cout << "vec2[2]: " << vec2[2] << endl;
    cout << "vec2[-2]: " << vec2[-2] << endl;

    vec = vec1.SetUp(0, 5, 1);
    cout << "vec: " << vec << "real size: " << vec.RealSize() << endl;

    // очистка
    vec1.Clear();
    vec1.Print();


    return 0;
}
