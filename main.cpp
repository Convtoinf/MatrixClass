#include"matrix.h"
#include<iostream>
using namespace std;


int main()
{
	int arr1[1][4] =
	{
		{1,4,2,5}
	};
	int arr2[2][4] =
	{
		{2,6,2,6},
		{4,4,2,5}
	};
	int arr3[1][4] =
	{
		{7,2,9,4}
	};

	mat mat1(arr1);
	mat mat2(arr2);
	mat mat3(arr3);

	mat mat0 = mat1 | mat2 | mat3;

	mat0.print_fra();

	cout << "rank:" << mat0.rank() << endl;

	cout << "det:" << mat0.det() << endl;

	cout << "inv:" << endl;
	mat mat0_inv = mat0.inv();
	mat0_inv.print_fra();

	cout << "mul:" << endl;
	(mat0 * mat0_inv).print_fra();

	cout << "rref:" << endl;
	mat mat0_rref = mat0.rref();
	mat0_rref.print_fra();

	cout << "null:" << endl;
	mat mat0_null = mat0.null();
	mat0_null.print_fra();

	cout << "mul:" << endl;
	(mat0 * mat0_null).print_fra();
	
	system("pause");
	return 0;
}