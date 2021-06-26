#pragma once
#include <iostream>
#include "boolvector.h"
using namespace std;

class BoolMatrix
{
private:
    int m, n; // m- кол-во векторов, n - длина
    BoolVector* vectors;

public:
    BoolMatrix();
    BoolMatrix(int m, int n);
    BoolMatrix(bool ** bm, int M, int N);
    BoolMatrix(char ** bm, int M, int N);
    BoolMatrix(BoolMatrix& bm);
    ~BoolMatrix();

    // индексы булева вектора инвертивны, при обращении к вектору индекс 0 означает младший бит.
    BoolVector GetIndex(int index);
    BoolVector operator[](int index) { return GetIndex(index); };

    void Asign(BoolMatrix& matr);
    void operator = (BoolMatrix& matr) { Asign(matr); }

    void Print();

    BoolMatrix& SetUp(bool val, int i, int j); // возвращает новый объект
    void SetIndex(bool val, int i, int j); // изменяет текущий объект

    BoolMatrix& operator ~();
    BoolMatrix& operator &(BoolMatrix & matrix);
    BoolMatrix& operator |(BoolMatrix & matrix);
    BoolMatrix& operator ^(BoolMatrix & matrix);

    BoolVector Conj();  //конъюнкция всех строк матрицы
    BoolVector Disj();  //дизъюнкция всех строк матрицы
    BoolVector Xor();  //XOR всех строк матрицы


    friend BoolMatrix;
};

BoolMatrix::BoolMatrix()
{
    m = 1; n = 1;
    vectors = new BoolVector[m];
    vectors[0] = BoolVector(1);
}
BoolMatrix::BoolMatrix(int M, int N)
{
    m = M; n = N;
    vectors = new BoolVector[m];
    for (int i = 0; i < m; i++)
    {
        vectors[i] = BoolVector(n);
    }
}
BoolMatrix::BoolMatrix(bool **bm, int M, int N)
{
    m = M; n = N;
    vectors = new BoolVector[m];
    for (int i = 0; i < m;  i++)
    {
        vectors[i] = BoolVector(bm[i], n);
    }
}
BoolMatrix::BoolMatrix(char **bm, int M, int N)
{
    m = M; n = N;
    vectors = new BoolVector[m];
    for (int i = 0; i < m;  i++)
    {
        vectors[i] = BoolVector(bm[i], n);
    }
}
BoolMatrix::BoolMatrix(BoolMatrix &bm)
{
    m = bm.m; n = bm.n;
    vectors = new BoolVector[m];
    for (int i = 0; i < m; i++)
    {
        vectors[i] = BoolVector(bm.vectors[i]);
    }
}
BoolMatrix::~BoolMatrix()
{
    delete [] vectors;
}

void BoolMatrix::Print()
{
    for (int i = 0; i < m; i++)
    {
        vectors[i].Print();
    }
}

void BoolMatrix::Asign(BoolMatrix& matr)
{
    m = matr.m; n = matr.n;
    cout << "m = " << m << " n = " << n << endl;
    vectors = new BoolVector[m];
    for (int i = 0; i < m; i++)
    {
        vectors[i] = BoolVector(matr.vectors[i]);
    }
}

BoolVector BoolMatrix::GetIndex(int index)
{
    return vectors[index];
}

void BoolMatrix::SetIndex(bool val, int i, int j)
{
    vectors[i].SetIndex(val, j);
}

BoolMatrix& BoolMatrix::SetUp(bool val, int i, int j)
{
    BoolMatrix* nm = new BoolMatrix(*this);
    nm->SetIndex(val, i, j);
    return *nm;
}

BoolMatrix& BoolMatrix::operator ~()
{
    BoolMatrix* nm = new BoolMatrix(*this);
    for (int i = 0; i < m; i++)
    {
        nm->vectors[i] = ~ vectors[i];
    }
    return * nm;
}
BoolMatrix& BoolMatrix::operator &(BoolMatrix & matrix)
{
    BoolMatrix* nm = new BoolMatrix(*this);
    BoolVector* vec = new BoolVector;
    for (int i = 0; i < m; i++)
    {
        (*vec) = matrix[i];
        nm->vectors[i] = vectors[i] & (*vec);
    }
    return * nm;
}
BoolMatrix& BoolMatrix::operator |(BoolMatrix & matrix)
{
    BoolMatrix* nm = new BoolMatrix(*this);
    BoolVector* vec = new BoolVector;
    for (int i = 0; i < m; i++)
    {
        (*vec) = matrix[i];
        nm->vectors[i] = vectors[i] | (*vec);
    }
    return * nm;
}
BoolMatrix& BoolMatrix::operator ^(BoolMatrix & matrix)
{
    BoolMatrix* nm = new BoolMatrix(*this);
    BoolVector* vec = new BoolVector;
    for (int i = 0; i < m; i++)
    {
        (*vec) = matrix[i];
        nm->vectors[i] = vectors[i] ^ (*vec);
    }
    return * nm;
}

BoolVector BoolMatrix::Conj()
{
    BoolVector* NV = new BoolVector();
    *NV = vectors[0];

    for(int i = 1; i < m; i++)
    {
        *NV = *NV & vectors[i];
    }

    return *NV;
}

BoolVector BoolMatrix::Disj()
{
    BoolVector* NV = new BoolVector();
    *NV = vectors[0];

    for(int i = 1; i < m; i++)
    {
        *NV = *NV | vectors[i];
    }

    return *NV;
}

BoolVector BoolMatrix::Xor()
{
    BoolVector* NV = new BoolVector();
    *NV = vectors[0];

    for(int i = 1; i < m; i++)
    {
        *NV = *NV ^ vectors[i];
    }

    return *NV;
}
