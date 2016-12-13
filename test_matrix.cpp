#include <iostream>
#include <fstream>
#include "matrix.h"
/*Napisz definicję klasy implementującej macierz ze zliczaniem odwołań tak, aby mogła ona zostać użyta w przykładzie zaprezentowanym w pliku test_matrix.cpp.
Jako pliku wymaganego w funkcji main() użyj matrix.dat. Rozważ możliwości modyfikacji funkcji main() tak aby wystąpiły wyszczególnione w niej wyjątki. */

using namespace std;

int main()
{
	try
	{
		cout << endl;

	  	CMatrix A1(2,5,1.0);			//Create matrix A1 = [	1.0  0.0  0.0  0.0  0.0
							//			0.0  1.0  0.0  0.0  0.0] 

                cout << A1 << endl;
		
		CMatrix A2(5,3,0.0,6.3);		//Create matrix A1 = [	0.0  6.3  6.3 
							//			6.3  0.0  6.3 
							//			6.3  6.3  0.0
							//			6.3  6.3  6.3
							//			6.3  6.3  6.3  ]
		cout << A2 << endl;
                
		CMatrix S = A1 * A2;			//Multiply A1 by A2
		cout << S << endl;
                
		fstream f1;
		f1.open("matrix.dat", fstream::in);
                if(f1.good()){
                    cout << "Uzyskano dostęp do pliku" <<endl;
                }
                else
                    cout<< "Nie udało się otworzyć pliku" <<endl;
                 
                CMatrix B(f1);				//Read the matrix data from file matrix.dat
		f1.close();				//First two values in this file specify the matrix dimensions
		cout << B << endl;
		
		/*S = B;						//Assign B to S
		S[0][0] = 1.4;					//Modify S
		cout << "S[0][0]=" << S[0][0] << endl;		//Verify S
		cout << "B[0][0]=" << B[0][0] << endl;	//Verify B
		f1.close();*/
	}
	catch(IndexOutOfRange& e) 
	{
		cout << "Index Out of Range" << endl;
	}
	catch(WrongDim& e)
	{
		cout << "Wrong Matrix Dimensions" << endl;
	}
	catch(bad_alloc)
	{
		cout << "Out of Memory" << endl;
	}
	return 0;
}
