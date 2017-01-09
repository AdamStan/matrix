#include <iostream>
#include <fstream>
#include "matrix.h"

using namespace std;

/*Funkcje dla matrixa tu będą*/
CMatrix::CMatrix()//dziala
{
    data = new matrix(1,1,0.0,0.0);
}
CMatrix::CMatrix(unsigned nlines, unsigned ncolumns, double eleDiagonally, double element)//dziala
{
    data = new matrix(nlines,ncolumns,eleDiagonally,element);
}
CMatrix::CMatrix(unsigned nlines, unsigned ncolumns, double eleDiagonally)//dziala
{
    double element=0.0;
    data = new matrix(nlines,ncolumns,eleDiagonally,element);
}

CMatrix::CMatrix(fstream& fp)
{
    unsigned a,b;
    fp>>a>>b;
    
    data = new matrix(a,b,0.0,0.0);
    
    for(unsigned i =0;i<a;i++)
      for(unsigned j=0;j<b;j++)
	fp>>data->table[i][j];
}

CMatrix::CMatrix(const CMatrix& co) //konstruktor kopiujacy
{
    co.data->n++;
    data=co.data;
}

CMatrix::~CMatrix()
{
    if(--data->n == 0) delete data;
}
CMatrix CMatrix::operator* (const CMatrix co) const //dziala
{
    CMatrix pom(this->data->lines,co.data->columns,0.0,0.0);
    if (this->data->columns != co.data->lines) 
    {
        throw WrongDim();
    }
    for(unsigned a=0; a<this->data->lines;a++)
        for(unsigned b=0; b<co.data->columns;b++)
            for(unsigned i=0; i<co.data->columns;i++)
                pom.data->table[a][b] += (this->data->table[a][i]*co.data->table[i][b]);
    return pom;
}

CMatrix& CMatrix::operator= (const CMatrix& co)
{
    co.data->n++;
    if(--data->n == 0) delete data;
    data = co.data;
    return *this;
}
ostream& operator<< (ostream& o,const CMatrix& A) //dziala
{
    for(unsigned i=0; i<A.data->lines;i++)
    {
        for(unsigned j=0;j<A.data->columns;j++)
            o << A.data->table[i][j]<< " ";
        o << "\n";
    }
    return o;
}
CMatrix::access CMatrix::operator[](unsigned i)
{
    if(i>data->lines)throw IndexOutOfRange();
    return access(*this, i);
}
void CMatrix::check_line(unsigned int i) const
{
    if(data->lines<=i) throw WrongDim();
}
void CMatrix::check_column(unsigned int j) const
{
    if(data->columns<=j) throw WrongDim();
}
double CMatrix::read(unsigned int i, unsigned int j) const
{
    return data->table[i][j];
}
void CMatrix::write(unsigned int i, unsigned int j, double t)
{
    data = data->detach();
    data->table[i][j] = t;
}