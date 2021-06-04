#pragma once
#include <iostream>
using namespace std;

struct Node
{
    int val;
    Node* last; Node* next;
};

class List
{
    Node* head, * tail;

public:
    List(); // объявляем конструкторы и дескруктор
    List(int* arr, int size);
    List(int size);

    ~List();

    void AddAfter(int val, Node* node); // добавить новое значение после указанной ноды
    void AddToHead(int val); // добавить значение в "голову"
    void AddToTail(int val); // добавить значение в "хвост"

    void DelTo(Node* node); // удаляем ноду
    void DelToHead();  // удаляем первую ноду(не "головную")
    void DelToTail();  // удаляем последнюю ноду(не "хвостовую")

    Node* FindKey(int key); // поиск ноды по ключу
    Node* FindPos(int pos);	// нода по индексу

    Node* MaxNode(); // нода с максимальным значением
    Node* MinNode(); // нода с минимальным значением

    int Max(){ return MaxNode()->val; }
    int Min(){ return MinNode()->val; }

    int ListSize(); // размер списка

    bool isEmpty(); // проверка списка на пустоту
    void Clear(); 	// удаление списка, освобождение памяти

    // некоторые операции и их перегрузка
    List& Assign(const List& l); // присваивание
    List& operator = (const List&l){ return Assign(l); }

    List& Sum(const List& l); // сложение списков
    List& operator + (const List& l){ return Sum(l);}
    List& operator += (const List& l){ return Sum(l);}

    bool Equals(List l); // проверка на равенство
    bool operator == (List l){ return Equals(l); }
    bool operator != (List l){ return !Equals(l); }

    int GetIndex(int index); // получение значения по индексу
    int operator [] (int index) {return GetIndex(index); }

    void SetIndex(int index, int val); // установить значение по индексу

    void Print(); // вывод значений списка в консоль
    friend ostream& operator << (ostream& st, List& l) {l.Print(); return st;};

    void Input(int size); // ввод значений списка из консоли
    friend istream& operator >> (istream& st, List& l);

private:
    void _init_base_();
    int listSize = 0;
};

void List::_init_base_()
{
    head = new Node;
    tail = new Node{-1, head, NULL};
    (*head).next = tail;
    listSize = 0;
}
List::List()
{
    _init_base_();
}
List::List(int size)
{
    _init_base_();
    for (int i = 0; i < size; i++)
        AddToTail(0);
}
List::List(int* arr, int size)
{
    _init_base_();
    for (int i = 0; i < size; i++) {
        AddToTail(arr[i]);
    }
}
List::~List()
{
    Clear();
    delete head;
    delete tail;

}
void List::AddAfter(int val, Node*node) {
    Node* newNode = new Node;
    (*newNode).val = val;
    (*newNode).next = (*node).next;
    (*newNode).last = node;

    (*node).next = newNode;
    (*(*newNode).next).last = newNode;

    this->listSize++;
}
void List::AddToHead(int val)
{
    AddAfter(val, head);
}
void List::AddToTail(int val)
{
    AddAfter(val, (*tail).last);
}
void List::DelTo(Node *node)
{
    Node* t1 = node->last;
    Node* t2 = node->next;

    t1->next = t2;
    t2->last = t1;

    listSize --;
    delete node;
}
bool List::isEmpty()
{
    return (head->next == tail);
}
void List::DelToHead()
{
    if (isEmpty())
        cout << "list is empty\n";
    else
        DelTo((*head).next);
}
void List::DelToTail()
{
    if (isEmpty())
        cout << "list is empty\n";
    else
        DelTo((*tail).last);
}
Node* List::FindKey(int key)
{
    Node* nd = head->next;
    while (nd != tail && nd->val != key)
        nd = nd->next;
    if (nd == tail)
        return NULL;
    return nd;
}
Node* List::FindPos(int pos)
{
    Node* nd = head;

    for (int i = -1; i < pos && nd != tail; i++)
        nd = nd -> next;

    if (nd == NULL)
        cout << "Index Error\n";

    return nd;
}
Node* List::MaxNode()
{
    Node* nd = head->next;
    Node* m = nd;
    if (nd == tail)
    {
        cout << "List is empty!" << endl;
        return NULL;
    }

    nd = nd->next;
    while (nd != tail)
    {
        if (nd->val > m->val)
            m = nd;
        nd = nd->next;
    }
    return m;
}
Node* List::MinNode()
{
    Node* nd = head->next;
    Node* m = nd;
    if (nd == tail)
    {
        cout << "List is empty!" << endl;
        return NULL;
    }

    nd = nd->next;
    while (nd != tail)
    {
        if (nd->val < m->val)
            m = nd;
        nd = nd->next;
    }
    return m;
}
void List::Clear() {
    Node* nd = head->next;
    for (; nd != tail; nd = head->next)
        DelToHead();
}
int List::ListSize()
{
    return this->listSize;
}
bool List::Equals(List l)
{
    Print(); l.Print();
    if (l.listSize != this->listSize)
        return false;

    Node* n1 = (*head).next;
    Node* n2 = (*l.head).next;

    while (n1 != tail && n2 != l.tail)
    {
        if ((*n1).val != (*n2).val)
            return false;
        n1 = (*n1).next;
        n2 = (*n2).next;
    }
    return true;
}
void List::Input(int size)
{
    int val;
    Clear();
    cout << "Enter " << size << " elements:\n";
    for (int i = 0; i < size; i++)
    {
        cin >> val;
        AddToTail(val);
    }
}
void List::Print()
{
    if (isEmpty()) return;

    Node* p = head->next;
    for (;p != tail; p = p->next)
        cout << p->val << " ";
    cout << endl;
}
istream& operator >> (istream& r, List& X) {
    int n;
    cout << "enter the number of elements in list" << endl;
    cin >> n;
    X.Input(n);
    return r;
}
List& List::Assign(const List &l)
{
    if (this != &l)
    {
        Clear();
        Node* nd = l.head->next;
        while (nd != l.tail)
        {
            AddToTail(nd->val);
            nd = nd->next;
        }
    }
    return *this;
}
List& List::Sum(const List& l)
{
    if (this != &l)
    {
        Node* nd = l.head->next;
        while (nd != l.tail)
        {
            AddToTail(nd->val);
            nd = nd->next;
        }
    }
    return *this;
}
int List::GetIndex(int index)
{
    return FindPos(index)->val;
}
void List::SetIndex(int index, int val)
{
    FindPos(index)->val = val;
}
