#pragma once
#include <iostream>
#include "list.h"
using namespace std;
class Set: public List
{

public:
    // конструкторы, деструктор не нуждается в модификации и наследуется от List
    Set();
    Set(int size);
    Set(int* a, int size);
    Set(Set& set);

    Set Assign(Set s); // присваивание, если множества другое создается новое

    void AddAfter(int val, Node* node); // добавить новое значение после указанной ноды // переопределяем из-за того, что множество не должно содержать одинаковые объекты

    void AddToBegin(int val); // добавить в начало и конец соответсвенно
    void AddToEnd(int val);

    /////// некоторые спецефичные методы для множества
    void AddRange(int* vals, int size); // добавление нескольких элементов в множетво
    void Remove(int val); // удаление элемента из множества
    void RemoveRange(int* vals, int size); // удаление нескольких элементов из множества

    int Count(); // колличество элементов в множестве
    bool Contains(int val); // проверка на вхождение подмножества(или одного элемента) в множество
    bool Contains(Set* subset);
    bool Contains(int* vals, int size);

    Set Union(Set& set2); // объеденение двух множеств
    Set Difference(Set& set2); // разность двух множеств
    Set Intersection(Set& set2); // пересечение двух множеств

    ///// перегрузка
    Set operator = (Set s){ return Assign(s); }
    Set operator + (Set& set2) { return Union(set2); }
    Set operator - (Set& set2) { return Difference(set2); }
    Set operator * (Set& set2) { return  Intersection(set2); }

    void Sort() { Sort(this, Count());}

private:
    void Sort(Set* data, int len);
    using List::AddToHead, List::AddToTail, List::ListSize; // инкапсулируем методы которые мы заменили
};

Set::Set():List(){}

Set::Set(int size)
{
    List::_init_base_();
    for (int i = 0; i < size; i++)
        AddToTail(i);
}
Set::Set(int* a, int size)
{
    List::_init_base_();
    for (int i = 0; i < size; i++) {
        AddToEnd(a[i]);
    }
}
Set::Set(Set& set)
{
    List::_init_base_();
    for (int i = 0; i < set.Count(); i++) {
        AddToEnd(set[i]);
    }
}
void Set::AddAfter(int val, Node *node)
{
    if (!Contains(val))
        List::AddAfter(val, node);
    else
        cout << "Duplicate found!\n";
}
void Set::AddToBegin(int val)
{
    AddAfter(val, List::_get_head_());
}
void Set::AddToEnd(int val)
{
    AddAfter(val, List::_get_tail_()->last);
}

void Set::AddRange(int *vals, int size)
{
    for (int i = 0; i < size; i++)
        AddToEnd(vals[i]);
}

void Set::Remove(int val)
{
    Node* DN = List::FindKey(val);
    if (DN)
        List::DelTo(DN);
    else
        cout << "Item " << val << " not found!\n";
}
void Set::RemoveRange(int* vals, int size)
{
    for (int i = 0; i < size; i++)
        Remove(vals[i]);
}
int Set::Count(){ return ListSize(); }

bool Set::Contains(int val)
{
    if (List::FindKey(val) != NULL)
        return 1;
    return 0;
}

bool Set::Contains(int *vals, int size)
{
    for(int i = 0; i < size; i++)
    {
        if (!Contains(vals[i]))
            return 0;
    }
    return 1;
}
bool Set::Contains(Set* subset)
{
    for(int i = 0; i < (*subset).Count(); i++)
    {
        if (!Contains((*subset)[i]))
            return 0;
    }
    return 1;
}
Set Set::Union(Set& set2)
{
    Set set = Set(*this);
    for (int i = 0; i < set2.Count(); i++)
        set.AddToEnd(set2[i]);
    return set;

}

Set Set::Intersection(Set& set2)
{
    Set set = Set();
    for(int i = 0; i < set2.Count(); i++)
    {
        if (Contains(set2[i]))
            set.AddToEnd(set2[i]);
    }
    return set;
}

Set Set::Difference(Set &set2)
{
    Node* nd;
    Set set = Set(*this);
    for (int i = 0; i < set2.Count(); i++)
    {
        nd = set.FindKey(set2[i]);
        if (nd != NULL) set.DelTo(nd);
    }
    return set;
}

Set Set::Assign(Set s)
{
    if (this != &s)
    {
        Clear();
        Node* nd = s._get_head_()->next;
        while (nd != s._get_tail_())
        {
            AddToTail(nd->val);
            nd = nd->next;
        }
    }
    return *this;
}

void Set::Sort(Set *data, int len)
{
    int key = 0;
    int i = 0;
    for(int j = 1; j < len; j++)
    {
        key = (*data)[j];
        i = j - 1;
        while (i >= 0 && (*data)[i] > key) {
            (*data).SetIndex(i + 1, (*data)[i]);
            i = i - 1;
            (*data).SetIndex(i + 1, key);
        }
    }
}
