#pragma once
#include <iostream>
using namespace std;

class BoolVector
{
private:
    int lv, cv; // lv - настоящая длина вектора, cv - длина кратная восьми для отображения
    bool* bv;

public:
    // конструкторы и деструктор
    BoolVector();
    BoolVector(int n);
    BoolVector(char* s, int n);
    BoolVector(bool* b, int n);
    BoolVector(BoolVector& vect);

    ~BoolVector();

    void Input();
    void Print();
    int Weight();

    bool IndexOf(int index); // идексы инвертивны, под индексом 0 будет не первый элемент массива, а младший бит вектора
    bool operator[](int index);

    BoolVector Plus(BoolVector vec2); // сложение векторов

    void Asign(BoolVector vec);
    void operator = (BoolVector vec) { Asign(vec); } // присвоение

    int ToDecimal(); // перевод двоичного вектора в десятичное число
    // операторы сравнения
    bool operator == (BoolVector& vec) { return ToDecimal() == vec.ToDecimal();}
    bool operator != (BoolVector& vec) { return ToDecimal() != vec.ToDecimal();}
    bool operator <= (BoolVector& vec) { return ToDecimal() <= vec.ToDecimal();}
    bool operator >= (BoolVector& vec) { return ToDecimal() >= vec.ToDecimal();}
    bool operator < (BoolVector& vec)  { return ToDecimal() <  vec.ToDecimal();}
    bool operator > (BoolVector& vec)  { return ToDecimal() >  vec.ToDecimal();}

    // побитовые логические операции
    BoolVector NOT();
    BoolVector AND(BoolVector& vec);
    BoolVector XOR(BoolVector& vec);
    BoolVector OR(BoolVector& vec);
    BoolVector EQ(BoolVector& vec);

    BoolVector operator ~ (){ return NOT(); }
    BoolVector operator & (BoolVector& v){ return AND(v); }
    BoolVector operator ^ (BoolVector& v){ return XOR(v); }
    BoolVector operator | (BoolVector& v){ return OR(v);  }
    //BoolVector operator <=> (BoolVector& v){ return EQ(v);}

    // побитовые сдвиги

    BoolVector LeftShift(int n);
    BoolVector RightShift(int n);

    BoolVector operator << (int n) { return LeftShift(n); }
    BoolVector operator >> (int n) { return RightShift(n); }

    BoolVector SetUp(int pos, bool val); // установить значение на позицию, возвращает новый объект
    void SetIndex(int index, bool val); // установить значение на позицию, изменяет текущий объект
    BoolVector Invert(int pos);

    BoolVector SetUp(int pos, int count, bool val);
    BoolVector Invert(int pos, int count);

    int RealSize() {return lv; }

    void Clear();
    friend ostream& operator << (ostream& st, BoolVector& b) { b.Print(); return st; }
    friend istream& operator >> (istream& st, BoolVector& b) { b.Input(); return st; }

};


BoolVector::BoolVector()
{
    lv = 0; cv = 1;
    bv = new bool[1];
    bv[0] = 0;
}

BoolVector::BoolVector(int n)
{
    lv = n; cv = n % 8 ? 8 - n % 8 : 0;
    bv = new bool[lv];
    for (int i = 0; i < cv; i++)
        bv[i] = 0;
}

BoolVector::BoolVector(char* str, int n)
{
    lv = n; cv = n % 8 ? 8 - n % 8 : 0;
    bv = new bool[lv];

    for (int i = 0; i < n; i++)
        switch (str[i])
        {
            case '1' : bv[i] = 1; break;
            case '0' : bv[i] = 0; break;
            default: cout << "Incorrect input\n"; return;
        }
}

BoolVector::BoolVector(bool* b, int n)
{
    lv = n; cv = n % 8 ? 8 - n % 8 : 0;
    bv = new bool[lv];

    for (int i = 0; i < n; i++)
        bv[i] = b[i];
}

BoolVector::BoolVector(BoolVector &vect)
{
    lv = vect.lv; cv = vect.cv;
    bv = new bool[lv];
    for (int i = 0; i < lv; i++)
        bv[i] = vect.bv[i];


}

BoolVector::~BoolVector() {
    delete[]bv;
}
void BoolVector::Input()
{
    cout << "Enter the length of the vector\n";
    cin >> lv; cv = lv % 8 ? 8 - lv % 8 : 0;
    bv = new bool[lv];

    for (int i = 0; i < lv; i++)
        cin >> bv[i];
}

int BoolVector::ToDecimal()
{
    int dec = 0;
    int d = 1;
    for (int i = lv-1; i >= 0; i--)
    {
        dec += d * bv[i];
        d *= 2;
    }
    return dec;
}

BoolVector BoolVector::AND(BoolVector &vec)
{
    int max_lv = lv > vec.lv ? lv : vec.lv;
    BoolVector* nv = new BoolVector(max_lv);

    for (int i = 0; i < max_lv; i++)
    {
        nv->SetIndex(i, (*this)[i] & vec[i]);
    }
    return *nv;
}

BoolVector BoolVector::OR(BoolVector &vec)
{
    int max_lv = lv > vec.lv ? lv : vec.lv;
    BoolVector* nv = new BoolVector(max_lv);

    for (int i = 0; i < max_lv; i++)
    {
        nv->SetIndex(i, (*this)[i] | vec[i]);
    }
    return *nv;
}

BoolVector BoolVector::XOR(BoolVector &vec)
{
    int max_lv = lv > vec.lv ? lv : vec.lv;
    BoolVector* nv = new BoolVector(max_lv);

    for (int i = 0; i < max_lv; i++)
    {
        nv->SetIndex(i, (*this)[i] ^ vec[i]);
    }
    return *nv;
}

BoolVector BoolVector::EQ(BoolVector &vec)
{
    int max_lv = lv > vec.lv ? lv : vec.lv;
    BoolVector* nv = new BoolVector(max_lv);

    for (int i = 0; i < max_lv; i++)
    {
        nv->SetIndex(i, (*this)[i] == vec[i]);
    }
    return *nv;
}

BoolVector BoolVector::NOT()
{
    BoolVector* nv = new BoolVector(lv);

    for (int i = 0; i < lv; i++)
    {
        nv->SetIndex(i, (!(*this)[i]));
    }
    return *nv;
}


void BoolVector::Print()
{
    for (int i = 0; i < cv; i++)
        cout << 0;
    for (int i = 0; i < lv; i++)
        cout << bv[i];
    cout << endl;
}
int BoolVector::Weight()
{
    int weight = 0;
    for (int i = 0; i < lv; i++)
        weight += bv[i];
    return weight;
}
bool BoolVector::IndexOf(int index)
{
    if (index >= 0)
    {
        if (index < lv)
            return bv[lv - index - 1];
        else
            return 0;
    }
    else
    {
        if (-index <= lv)
            return bv[-index -1];
        else
        {
            cout << "Incorrect index\n"; return 0;
        }
    }
}
void BoolVector::Clear()
{
    delete [] bv;
    bv = new bool [0];
    lv = 0; cv = 0;

}
bool BoolVector::operator[](int index)
{
    return IndexOf(index);
}

BoolVector BoolVector::Plus(BoolVector vec2)
{
    int p = 0;
    int m = this->lv > vec2.lv ? this->lv : vec2.lv;
    bool base[this->lv + vec2.lv];

    for (int i = 0; i < m; i++)
    {
        base[m-i-1] = this->IndexOf(i) + vec2[i];
        if (base[m-i-1] > 1)
            base[m-i-2] += 1;
        base[m-i-1] %= 2;
    }

    int k = 0;
    for (int i = 0; i < this->lv + vec2.lv; i++)
    {
        if (base[i] == 1) break;
        k++;
    }

    return *this;
}

BoolVector BoolVector::SetUp(int pos, bool val)
{
    BoolVector* vec = new BoolVector(*this);

    if (pos >= 0)
    {
        if (pos < vec->lv)
            vec->bv[vec->lv - pos - 1] = val;
        else
            cout << "Incorrect index\n";
    }
    else
    {
        if (-pos <= vec->lv)
            vec->bv[-pos -1] = val;
        else
        {
            cout << "Incorrect index\n";
        }
    }
    return *vec;
}

void BoolVector::SetIndex(int index, bool val)
{
    if (index >= 0)
    {
        if (index < lv)
            bv[lv - index - 1] = val;
        else
            cout << "Incorrect index\n";
    }
    else
    {
        if (-index <= lv)
            bv[-index -1] = val;
        else
        {
            cout << "Incorrect index\n";
        }
    }
}

void BoolVector::Asign(BoolVector vec)
{
    lv = vec.lv; cv = vec.cv;
    bv = new bool[lv];
    for (int i = 0; i < lv; i++)
        bv[i] = vec.bv[i];
}

BoolVector BoolVector::SetUp(int pos, int count, bool val)
{
    BoolVector* NV = new BoolVector(*this);
    for(int i = 0; i < count; i++)
    {
        NV->SetIndex(pos+i, val);
    }
    return *NV;
}

BoolVector BoolVector::LeftShift(int n)
{
    bool* nbv = new bool[lv+n];
    for (int i = 0; i < lv; i++)
    {
        nbv[i] = bv[i];
    }
    for (int i = lv; i < lv+n; i++)
    {
        nbv[i] = 0;
    }

    BoolVector* nv = new BoolVector(nbv, lv+n);
    return *nv;
}

BoolVector BoolVector::RightShift(int n)
{
    bool* nbv = new bool[lv-n];
    for (int i = 0; i < lv-n; i++)
    {
        nbv[i] = bv[i];
    }
    BoolVector* nv = new BoolVector(nbv, lv-n);
    return *nv;
}
