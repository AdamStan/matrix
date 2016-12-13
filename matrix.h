#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <iostream>
#include <fstream>

using namespace std;

class IndexOutOfRange { };
class WrongDim { };

class CMatrix
{
private:
    struct matrix;
    matrix* data;
public:
    class helpful;
    CMatrix();
    CMatrix(fstream& fp);
    CMatrix(unsigned lines, unsigned columns, double eleDiagonally, double element);
    CMatrix(unsigned nlines, unsigned ncolumns, double eleDiagonally);
    CMatrix(const CMatrix& co);
    ~CMatrix();
    CMatrix operator* (const CMatrix co) const;
    CMatrix& operator= (const CMatrix& co);
    double operator[] (unsigned int i) const;
    friend ostream& operator<<(ostream&, const CMatrix&);
    void check(unsigned int i, unsigned int j) const;
    double read(unsigned int i, unsigned int j) const;
    void write(unsigned int i, unsigned int j, double t);
};

struct CMatrix::matrix
{
    unsigned int lines,columns;
    unsigned int n;
    double** table;
    
    matrix(unsigned int nlines,unsigned int ncolumns, double eleDiagonally=0.0, double element = 0.0)
    {
		n=1;
		lines = nlines;
		columns = ncolumns;

		table = new double* [nlines];
		for(unsigned i=0; i<lines; i++)
			table[i] = new double [ncolumns];

		for(unsigned i=0; i<lines;i++)
		    for(unsigned j=0; j<columns;j++)
			{
				if(i==j) table[i][j] = eleDiagonally;
				else table[i][j] = element;
			}
    };
    ~matrix()
    {
	for(unsigned i=0; i<lines;i++)
	  delete [] table[i];
	delete [] table;
    };
    matrix* detach()
    {
            if(n==1) return this;
            matrix* now = new matrix(lines,columns,table[0][0],table[0][1]);
            n--;
            return now;
    }
    void assign(unsigned int nlines, unsigned int ncolumns, double** ntable)
    {
	if (nlines != lines && ncolumns != columns)
	{
		double** t = new double* [nlines];
			for (unsigned i =0; i<nlines; i++)
				t[i] = new double [columns];
		
		lines = nlines;
		columns = ncolumns;
		
		for(unsigned i =0; i<lines;i++)
                    for(unsigned j=0; j<columns;j++)
			{
				t[i][j] = ntable[i][j];
			}
		for(unsigned i=0; i<lines;i++)
                    delete [] table[i];
		delete [] table;
		table = t;
	}
		else table = ntable;
	}
};

class CMatrix::helpful
{
  friend class CMatrix;
  CMatrix s;
  unsigned raw, col;
public:
   
};
#endif