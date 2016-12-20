#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <iostream>
#include <fstream>
//#include <valarray>

using namespace std;

class IndexOutOfRange { };
class WrongDim { };

class CMatrix
{
private:
    struct matrix;
    matrix* data;
    //typedef valarray<double> ArrayDb;
public:
    class CrefFirst;
    class access;
    CMatrix();
    CMatrix(fstream& fp);
    CMatrix(unsigned lines, unsigned columns, double eleDiagonally, double element);
    CMatrix(unsigned nlines, unsigned ncolumns, double eleDiagonally);
    CMatrix(const CMatrix& co);
    ~CMatrix();
    CMatrix operator* (const CMatrix co) const;
    CMatrix& operator= (const CMatrix& co);
    access operator[](unsigned i);
    friend ostream& operator<<(ostream&, const CMatrix&);
    void check_line(unsigned int i) const;
    void check_column(unsigned int j) const;
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
		
		if(columns == 0 || lines == 0) throw WrongDim(); 
		  
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
    matrix(unsigned nlines, unsigned ncolumns, double **m)
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
                    table[i][j] = m[i][j];
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
            matrix* now = new matrix(lines,columns,table);
            n--;
            return now;
    }
    /*void assign(unsigned int nlines, unsigned int ncolumns, double** ntable)
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
    }*/
};

class CMatrix::CrefFirst 
{
  friend class CMatrix;
  CMatrix& s;
  unsigned lin, col;
public:
    
    CrefFirst(CMatrix& ss, unsigned ii, unsigned jj): s(ss), lin(ii), col(jj) {};
    
    operator double() const
    {
        return s.read(lin,col);
    }
    CMatrix::CrefFirst& operator = (double a)
    {
        s.write(lin,col,a);
        return *this;
    }
    CMatrix::CrefFirst& operator = (const CrefFirst& ref) //tu chyba też trzeba użyć tego Array
    {
        return operator= ((double)ref);
    }
};

class CMatrix::access
{
    friend class CMatrix;
    CMatrix& buf;
    unsigned lin,col,thei;
    double **newtable;
public:
    access(CMatrix& bufNowe,unsigned what): buf(bufNowe)
    {
	lin=bufNowe.data->lines;
	col=bufNowe.data->columns;
        thei = what;
        
        newtable = new double* [col];        
	for(unsigned j=0;j<col;j++)
		newtable[j]=bufNowe.data->table[thei]+j;
    }
    ~access()
    {
        delete [] newtable;
    }
    CrefFirst operator[] (unsigned thej) const
    {
      if(thej>=col) throw IndexOutOfRange();  
      return CrefFirst(buf,thei,thej);
    }
};
#endif