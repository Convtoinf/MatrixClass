#include"matrix.h"
#include<iostream>

mat::mat(unsigned int r,unsigned int c,int n):row(r),col(c)
{
	fras = new fra * [row];
	for (unsigned int i = 0; i != row; ++i)
	{
		fras[i] = new fra[col];
	}
	for (unsigned int i = 0; i != row; ++i)
	{
		for (unsigned int j = 0; j != col; ++j)
		{
			fras[i][j] = n;
		}
	}
}

mat::mat(unsigned int n):row(n),col(n)
{
	fras = new fra * [row];
	for (unsigned int i = 0; i != row; ++i)
	{
		fras[i] = new fra[col];
	}
	for (unsigned int i = 0; i != row; ++i)
	{
		for (unsigned int j = 0; j != col; ++j)
		{
			if (i == j)
			{
				fras[i][j] = 1;
			}
			else
			{
				fras[i][j] = 0;
			}
		}
	}
}

mat::mat(const mat& temp_mat)
{
	if (this == &temp_mat) return;
	row = temp_mat.row;
	col = temp_mat.col;
	fras = new fra * [row];
	for (int i = 0; i != row; ++i)
	{
		fras[i] = new fra[col];
	}
	for (int i = 0; i != row; ++i)
	{
		for (int j = 0; j != col; ++j)
		{
			fras[i][j] = temp_mat.fras[i][j];
		}
	}
}

mat::~mat()
{
	if (fras != NULL)
	{
		for (int i = 0; i != row; ++i)
		{
			delete[] fras[i];
			fras[i] = NULL;
		}
		fras = NULL;
	}
}

unsigned int mat::get_row()const
{
	return row;
}

unsigned int mat::get_col()const
{
	return col;
}

bool mat::is_squ()const
{
	return row == col;
}

bool mat::is_symm()const
{
	if (!this->is_squ()) return false;
	for (int i = 1; i < row; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (fras[i][j] == fras[j][i])
			{
				continue;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

mat& mat::operator=(const mat& temp_mat)
{
	if (this == &temp_mat) return *this;
	this->~mat();
	row = temp_mat.row;
	col = temp_mat.col;
	fras = new fra * [row];
	for (int i = 0; i != row; ++i)
	{
		fras[i] = new fra[col];
	}
	for (int i = 0; i != row; ++i)
	{
		for (int j = 0; j != col; ++j)
		{
			fras[i][j] = temp_mat.fras[i][j];
		}
	}
	return *this;
}

void mat::print_fra()const
{
	for (int i = 0; i != row; ++i)
	{
		for (int j = 0; j != col; ++j)
		{
			fras[i][j].print_fra();
			std::cout << "\t";
		}
		std::cout << std::endl;
	}
}

void mat::print_int()const
{
	for (int i = 0; i != row; ++i)
	{
		for (int j = 0; j != col; ++j)
		{
			fras[i][j].print_int();
			std::cout << "\t";
		}
		std::cout << std::endl;
	}
}

void mat::print_double()const
{
	for (int i = 0; i != row; ++i)
	{
		for (int j = 0; j != col; ++j)
		{
			fras[i][j].print_double();
			std::cout << "\t";
		}
		std::cout << std::endl;
	}
}

void mat::tran()
{
	mat temp_mat(col, row);
	for (int i = 0; i != col; ++i)
	{
		for (int j = 0; j != row; ++j)
		{
			temp_mat.fras[i][j] = fras[j][i];
		}
	}
	*this = temp_mat;
}

const mat mat::inv()const
{
	if (row != col)
	{
		std::cout << "错误：行列数不相等没有逆阵"<<std::endl;
		return mat(0,0);
	}
	if (this->rank() != row)
	{
		std::cout << "错误：行列式为0，没有逆阵" << std::endl;
		return mat(0,0);
	}
	mat temp_mat = *this;
	mat ret_mat(row);
	fra temp;
	int i;
	//逐列进行
	for (int j = 0; j != col; ++j)
	{
		//向下找到当前列的非零行（一定存在），并交换到对角线处。对E阵进行同样操作。
		for (i = j; i != temp_mat.row; ++i)
		{
			if (!temp_mat.fras[i][j].is_zero())
			{
				temp_mat.swap_row(i + 1, j + 1);
				ret_mat.swap_row(i + 1, j + 1);
				break;
			}
		}
		//将对角线处元素置为1。对E阵进行同样操作。
		temp = temp_mat.fras[j][j];
		temp.rec();
		temp_mat.mul_row(temp, j + 1);
		ret_mat.mul_row(temp, j + 1);
		//将当前列，除对角线元素，全部置为零。对E阵进行同样操作。
		for (i = 0; i != col; ++i)
		{
			if (!temp_mat.fras[i][j].is_zero())
			{
				temp = -temp_mat.fras[i][j];
				temp_mat.tran_row(temp, j + 1, i + 1);
				ret_mat.tran_row(temp, j + 1, i + 1);
			}
		}
	}
	return ret_mat;
}

void mat::swap_row(unsigned int r1, unsigned int r2)
{
	//判断r1和r2是否在范围里且不相等，如果不符合就直接返回
	if (r1 > 0 && r1 <= row && r2>0 && r2 <= row && r1 != r2)
	{
		--r1;
		--r2;
	}
	else
	{
		return;
	}
	fra temp;
	for (int i = 0; i != col; ++i)
	{
		temp = fras[r1][i];
		fras[r1][i] = fras[r2][i];
		fras[r2][i] = temp;
	}
}

void mat::swap_col(unsigned int c1, unsigned int c2)
{
	//判断c1和c2是否在范围里且不相等，如果不符合就直接返回
	if (c1 > 0 && c1 <= col && c2>0 && c2 <= col && c1 != c2)
	{
		--c1;
		--c2;
	}
	else
	{
		return;
	}
	fra temp;
	for (int j = 0; j != row; ++j)
	{
		temp = fras[j][c1];
		fras[j][c1] = fras[j][c2];
		fras[j][c2] = temp;
	}
}

void mat::tran_row(fra k, unsigned int r1, unsigned int r2)
{
	//判断r1和r2是否在范围里且不相等，如果不符合就直接返回
	if (r1 > 0 && r1 <= row && r2 > 0 && r2 <= row && r1 != r2)
	{
		--r1;
		--r2;
	}
	else
	{
		return;
	}
	for (int i = 0; i != col; ++i)
	{
		fras[r2][i] += (k * fras[r1][i]);
	}
}

void mat::tran_col(fra k, unsigned int c1, unsigned int c2)
{
	//判断c1和c2是否在范围里且不相等，如果不符合就直接返回
	if (c1 > 0 && c1 <= col && c2 > 0 && c2 <= col && c1 != c2)
	{
		--c1;
		--c2;
	}
	else
	{
		return;
	}
	for (int j = 0; j != row; ++j)
	{
		fras[j][c2] += (fras[j][c1] * k);
	}
}

void mat::mul_row(fra k, unsigned int r)
{
	if (r > 0 && r <= row)
	{
		--r;
	}
	else
	{
		return;
	}
	for (int j = 0; j != col; ++j)
	{
		fras[r][j] *= k;
	}
}

void mat::mul_col(fra k, unsigned int c)
{
	if (c > 0 && c <= col)
	{
		--c;
	}
	else
	{
		return;
	}
	for (int i = 0; i != row; ++i)
	{
		fras[i][c] *= k;
	}
}

const mat mat::get_row(unsigned int r)const
{
	if (r > 0 && r <= row)
	{
		--r;
	}
	else
	{
		return mat(0,0);
	}
	mat ret_mat(1, col);
	for (int j = 0; j != col; ++j)
	{
		ret_mat.fras[0][j] = fras[r][j];
	}
	return ret_mat;
}

const mat mat::get_col(unsigned int c)const
{
	if (c > 0 && c <= col)
	{
		--c;
	}
	else
	{
		return mat(0,0);
	}
	mat ret_mat(row, 1);
	for (int i = 0; i != row; ++i)
	{
		ret_mat.fras[i][0] = fras[i][c];
	}
	return ret_mat;
}

const fra mat::det()const
{
	if (col != row)
	{
		std::cout << "行列数不等，没有行列式" << std::endl;
		return 0;
	}
	fra ret(1);
	mat temp_mat = *this;
	fra temp;
	int i;
	//逐列进行
	for (int j = 0; j != temp_mat.col; ++j)
	{
		//向下找到当前列的非零行，并交换到对角线处。
		for (i = j; i != temp_mat.row; ++i)
		{
			if (!temp_mat.fras[i][j].is_zero())
			{
				temp_mat.swap_row(i + 1, j + 1);
				if (i != j)
				{
					//交换行或列，行列式要×-1
					ret *= fra(-1);
				}
				break;
			}
		}
		//如果没找到非零行，就代表行列式为零，返回0
		if (i == col) return 0;
		//向下消掉非零项，逐步构建上三角行列式
		temp = temp_mat.fras[j][j];
		temp.rec();
		for (i = j + 1; i != row; ++i)
		{
			if (!temp_mat.fras[i][j].is_zero())
			{
				temp_mat.tran_row(temp * (-temp_mat.fras[i][j]), j + 1, i + 1);
			}
		}
		//直接累乘对角线元素
		ret *= temp_mat.fras[j][j];

		//输出每一步
		//ret.print_fra();
		//std::cout << std::endl;
		//temp_mat.print_fra();
	}
	return ret;
}

const mat mat::operator+(const mat& temp_mat)const
{
	if (!(row == temp_mat.row && col == temp_mat.col))
	{
		std::cout << "错误：行列数不相等，无法相加";
	}
	mat ret_mat(row, col);
	for (int i = 0; i != ret_mat.row; ++i)
	{
		for (int j = 0; j != ret_mat.col; ++j)
		{
			ret_mat.fras[i][j] = fras[i][j] + temp_mat.fras[i][j];
		}
	}
	return ret_mat;
}

const mat mat::operator+(const fra& temp_fra)const
{
	if (!this->is_squ())
	{
		return*this;
	}
	mat ret_mat(*this);
	return ret_mat + (temp_fra * (mat(row)));
}

const mat operator+(const fra& temp_fra, const mat& temp_mat)
{
	return temp_mat + temp_fra;
}

const mat mat::operator-(const mat& temp_mat)const
{
	if (!(row == temp_mat.row && col == temp_mat.col))
	{
		std::cout << "错误：行列数不相等，无法相加";
	}
	mat ret_mat(row, col);
	for (int i = 0; i != ret_mat.row; ++i)
	{
		for (int j = 0; j != ret_mat.col; ++j)
		{
			ret_mat.fras[i][j] = fras[i][j] - temp_mat.fras[i][j];
		}
	}
	return ret_mat;
}

const mat mat::operator-(const fra& temp_fra)const
{
	return (*this) + (-temp_fra);
}

const mat operator-(const fra& temp_fra, const mat& temp_mat)
{
	return temp_mat + (-temp_fra);
}

const mat mat::operator*(const mat& temp_mat)const
{
	if (col != temp_mat.row)
	{
		std::cout << "无法计算乘法" << std::endl;
		mat mat0(0,0);
		return mat0;
	}
	mat ret_mat(row, temp_mat.col);
	fra temp;
	for (int i = 0; i != ret_mat.row; ++i)
	{
		for (int j = 0; j != ret_mat.col; ++j)
		{
			temp = (fra)0;
			for (int k = 0; k != col; ++k)
			{
				temp += fras[i][k] * temp_mat.fras[k][j];
			}
			ret_mat.fras[i][j] = temp;
		}
	}
	return ret_mat;
}

const mat mat::operator*(const fra& temp_fra)const
{
	mat ret_mat(*this);
	for (int i = 0; i != row; ++i)
	{
		for (int j = 0; j != col; ++j)
		{
			ret_mat.fras[i][j] *= temp_fra;
		}
	}
	return ret_mat;
}

const mat operator*(const fra& temp_fra, const mat& temp_mat)
{
	return temp_mat * temp_fra;
}

int mat::rank()const
{
	mat temp_mat = *this;
	if (temp_mat.col > temp_mat.row)
	{
		temp_mat.tran();
	}
	//默认秩为0
	int ret=0;
	int i;
	fra temp;
	//逐列进行
	for (int j = 0; j != temp_mat.col; ++j)
	{
		//从第秩行开始找非零行
		for (i = ret; i != temp_mat.row; ++i)
		{
			if (!temp_mat.fras[i][j].is_zero())
			{
				temp_mat.swap_row(i + 1, ret + 1);
				break;
			}
		}
		//没找到就继续下一列
		if (i == col)
		{
			continue;
		}
		//向下消掉非零项
		temp = temp_mat.fras[ret][j];
		temp.rec();
		for (i = ret; i != row; ++i)
		{
			if (!temp_mat.fras[i][j].is_zero())
			{
				temp_mat.tran_row(temp * (-temp_mat.fras[i][j]), j + 1, i + 1);
			}
		}
		++ret;
	}
	return ret;
}

const mat mat::operator ,(const mat& temp_mat)const
{
	if (row != temp_mat.row)
	{
		std::cout << "错误的拼接：行数不同";
	}
	mat ret_mat(row, col + temp_mat.col);
	for (int i = 0; i != row; ++i)
	{
		int j;
		for (j = 0; j != col ; ++j)
		{
			ret_mat.fras[i][j] = fras[i][j];
		}
		for (;j != col + temp_mat.col; ++j)
		{
			ret_mat.fras[i][j] = temp_mat.fras[i][j-col];
		}
	}
	return ret_mat;
}

const mat mat::operator | (const mat& temp_mat)const
{
	if (col != temp_mat.col)
	{
		std::cout << "错误的拼接：列数不同";
	}
	mat ret_mat(row + temp_mat.row, col);
	for (int j = 0; j != col; ++j)
	{
		int i;
		for (i = 0; i != row; ++i)
		{
			ret_mat.fras[i][j] = fras[i][j];
		}
		for (; i != row + temp_mat.row; ++i)
		{
			ret_mat.fras[i][j] = temp_mat.fras[i-row][j];
		}
	}
	return ret_mat;
}

const mat mat::rref()const
{
	mat ret_mat = *this;
	int i;
	int temp_rank=0;
	fra temp;
	//逐列进行
	for (int j = 0; j != ret_mat.col; ++j)
	{
		//从rank行开始，向下找非零行，交换，并将rank行置为1
		for (i = temp_rank; i != ret_mat.row; ++i)
		{
			if (!ret_mat.fras[i][j].is_zero())
			{
				ret_mat.swap_row(i + 1, temp_rank + 1);
				temp = ret_mat.fras[temp_rank][j];
				temp.rec();
				ret_mat.mul_row(temp, temp_rank + 1);
				break;
			}
		}
		//没找到就进行下一列
		if (i == row)
		{
			continue;
		}
		//对当前列用rank行消项
		for (i = 0; i != ret_mat.row; ++i)
		{
			if (!ret_mat.fras[i][j].is_zero())
			{
				ret_mat.tran_row((-ret_mat.fras[i][j]), temp_rank + 1, i + 1);
			}
		}
		//rank加1
		++temp_rank;
	}
	return ret_mat;
}

const mat mat::null()const
{
	if (this->rank() == col)
	{
		mat ret_mat(row, 1, 0);
		return ret_mat;
	}
	if (this->rank() == 0)
	{
		mat ret_mat(col);
		return ret_mat;
	}
	//有temp个解，它不等于0时
	if (int temp = (col - this->rank()))
	{
		mat rref = this->rref();
		mat ret_mat(col, temp, 0);
		mat temp_mat(1, col, 0);
		//初始化temp_mat，对于解，在对应列储存负的行数减一；对于非解，储存前后相对位置的坐标
		for (int i = 0; i != row; ++i)
		{
			for (int j = 0; j != col; ++j)
			{
				if (!rref.fras[i][j].is_zero())
				{
					temp_mat.fras[0][j] = (fra)(-i - 1);
					break;
				}
			}
		}
		for (int i = 0, j = 0; j != col; ++j)
		{
			if (temp_mat.fras[0][j].is_zero())
			{
				temp_mat.fras[0][j] = (fra)i;
				++i;
			}
		}
		//逐行进行
		for (int j = 0; j != col; ++j)
		{
			////读取当前行的temp_mat信息
			//如果小于零，即储存的是有解项
			if (((int)temp_mat.fras[0][j]) < 0)
			{
				//向后逐列按相对位置向返回的mat中填充解
				for (int jj = j + 1; jj != col; ++jj)
				{
					if (((int)temp_mat.fras[0][jj]) >= 0)
					{
						ret_mat.fras[j][(int)temp_mat.fras[0][jj]] = -rref.fras[-((int)temp_mat.fras[0][j] + 1)][jj];
					}
				}
			}
			else//如果不小于零，即储存的是默认解为1的项，则将对应相对位置的解初始化为1
			{
				ret_mat.fras[j][(int)temp_mat.fras[0][j]] = (fra)1;
			}
		}
		return ret_mat;
	}
}

