#pragma once
#include"fra.h"
class mat
{
private:
	fra** fras;
	unsigned int row;
	unsigned int col;
public:
	//利用整型数组初始化
	template<unsigned int R, unsigned int C>
	mat(int(&arr)[R][C])
	{
		row = R;
		col = C;
		fras = new fra * [R];
		for (int i = 0; i != R; ++i)
		{
			fras[i] = new fra[C];
		}
		for (int i = 0; i != R; ++i)
		{
			for (int j = 0; j != C; ++j)
			{
				fras[i][j] = fra(arr[i][j]);
			}
		}
	}
	//构造一个E阵
	mat(unsigned int n);
	//申请一个r行c列的阵，以0为默认初始化
	mat(unsigned int r, unsigned int c,int n=0);
	//深拷贝
	mat(const mat& temp_mat);
	//析构函数
	~mat();
	//返回行数
	unsigned int get_row()const;
	//返回列数
	unsigned int get_col()const;
	//判断是否为方阵
	bool is_squ()const;
	//判断是否为对称阵
	bool is_symm()const;
	//等号赋值
	mat& operator=(const mat& temp_mat);
	//打印（分数形式，整数形式，小数形式）
	void print_fra()const;
	void print_int()const;
	void print_double()const;
	//转置
	void tran();
	//求逆阵，并返回
	const mat inv()const;
	//交换两行
	void swap_row(unsigned int r1, unsigned int r2);
	//交换两列
	void swap_col(unsigned int c1, unsigned int c2);
	//将r1行的k倍加到r2行上
	void tran_row(fra k, unsigned int r1, unsigned int r2);
	//将c1列的k倍加到c2列上
	void tran_col(fra k, unsigned int c1, unsigned int c2);
	//将r行乘k
	void mul_row(fra k, unsigned int r);
	//将c列乘k
	void mul_col(fra k, unsigned int c);
	//得到第r行
	const mat get_row(unsigned int r)const;
	//得到第c列
	const mat get_col(unsigned int c)const;
	//计算行列式
	const fra det()const;
	//矩阵加减乘
	const mat operator+(const mat& temp_mat)const;
	const mat operator+(const fra& temp_fra)const;
	friend const mat operator+(const fra& temp_fra, const mat& temp_mat);
	const mat operator-(const mat& temp_mat)const;
	const mat operator-(const fra& temp_fra)const;
	friend const mat operator-(const fra& temp_fra, const mat& temp_mat);
	const mat operator*(const mat& temp_mat)const;
	const mat operator*(const fra& temp_fra)const;
	friend const mat operator*(const fra& temp_fra, const mat& temp_mat);
	//计算矩阵的秩
	int rank()const;
	//用，表示按行拼接
	const mat operator ,(const mat& temp_mat)const;
	//用| 表示按列拼接
	const mat operator| (const mat& temp_mat)const;
	//求行最简形
	const mat rref()const;
	//求基础解系
	const mat null()const;
};

