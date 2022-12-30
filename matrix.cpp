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
		std::cout << "���������������û������"<<std::endl;
		return mat(0,0);
	}
	if (this->rank() != row)
	{
		std::cout << "��������ʽΪ0��û������" << std::endl;
		return mat(0,0);
	}
	mat temp_mat = *this;
	mat ret_mat(row);
	fra temp;
	int i;
	//���н���
	for (int j = 0; j != col; ++j)
	{
		//�����ҵ���ǰ�еķ����У�һ�����ڣ������������Խ��ߴ�����E�����ͬ��������
		for (i = j; i != temp_mat.row; ++i)
		{
			if (!temp_mat.fras[i][j].is_zero())
			{
				temp_mat.swap_row(i + 1, j + 1);
				ret_mat.swap_row(i + 1, j + 1);
				break;
			}
		}
		//���Խ��ߴ�Ԫ����Ϊ1����E�����ͬ��������
		temp = temp_mat.fras[j][j];
		temp.rec();
		temp_mat.mul_row(temp, j + 1);
		ret_mat.mul_row(temp, j + 1);
		//����ǰ�У����Խ���Ԫ�أ�ȫ����Ϊ�㡣��E�����ͬ��������
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
	//�ж�r1��r2�Ƿ��ڷ�Χ���Ҳ���ȣ���������Ͼ�ֱ�ӷ���
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
	//�ж�c1��c2�Ƿ��ڷ�Χ���Ҳ���ȣ���������Ͼ�ֱ�ӷ���
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
	//�ж�r1��r2�Ƿ��ڷ�Χ���Ҳ���ȣ���������Ͼ�ֱ�ӷ���
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
	//�ж�c1��c2�Ƿ��ڷ�Χ���Ҳ���ȣ���������Ͼ�ֱ�ӷ���
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
		std::cout << "���������ȣ�û������ʽ" << std::endl;
		return 0;
	}
	fra ret(1);
	mat temp_mat = *this;
	fra temp;
	int i;
	//���н���
	for (int j = 0; j != temp_mat.col; ++j)
	{
		//�����ҵ���ǰ�еķ����У����������Խ��ߴ���
		for (i = j; i != temp_mat.row; ++i)
		{
			if (!temp_mat.fras[i][j].is_zero())
			{
				temp_mat.swap_row(i + 1, j + 1);
				if (i != j)
				{
					//�����л��У�����ʽҪ��-1
					ret *= fra(-1);
				}
				break;
			}
		}
		//���û�ҵ������У��ʹ�������ʽΪ�㣬����0
		if (i == col) return 0;
		//��������������𲽹�������������ʽ
		temp = temp_mat.fras[j][j];
		temp.rec();
		for (i = j + 1; i != row; ++i)
		{
			if (!temp_mat.fras[i][j].is_zero())
			{
				temp_mat.tran_row(temp * (-temp_mat.fras[i][j]), j + 1, i + 1);
			}
		}
		//ֱ���۳˶Խ���Ԫ��
		ret *= temp_mat.fras[j][j];

		//���ÿһ��
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
		std::cout << "��������������ȣ��޷����";
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
		std::cout << "��������������ȣ��޷����";
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
		std::cout << "�޷�����˷�" << std::endl;
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
	//Ĭ����Ϊ0
	int ret=0;
	int i;
	fra temp;
	//���н���
	for (int j = 0; j != temp_mat.col; ++j)
	{
		//�ӵ����п�ʼ�ҷ�����
		for (i = ret; i != temp_mat.row; ++i)
		{
			if (!temp_mat.fras[i][j].is_zero())
			{
				temp_mat.swap_row(i + 1, ret + 1);
				break;
			}
		}
		//û�ҵ��ͼ�����һ��
		if (i == col)
		{
			continue;
		}
		//��������������
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
		std::cout << "�����ƴ�ӣ�������ͬ";
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
		std::cout << "�����ƴ�ӣ�������ͬ";
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
	//���н���
	for (int j = 0; j != ret_mat.col; ++j)
	{
		//��rank�п�ʼ�������ҷ����У�����������rank����Ϊ1
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
		//û�ҵ��ͽ�����һ��
		if (i == row)
		{
			continue;
		}
		//�Ե�ǰ����rank������
		for (i = 0; i != ret_mat.row; ++i)
		{
			if (!ret_mat.fras[i][j].is_zero())
			{
				ret_mat.tran_row((-ret_mat.fras[i][j]), temp_rank + 1, i + 1);
			}
		}
		//rank��1
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
	//��temp���⣬��������0ʱ
	if (int temp = (col - this->rank()))
	{
		mat rref = this->rref();
		mat ret_mat(col, temp, 0);
		mat temp_mat(1, col, 0);
		//��ʼ��temp_mat�����ڽ⣬�ڶ�Ӧ�д��渺��������һ�����ڷǽ⣬����ǰ�����λ�õ�����
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
		//���н���
		for (int j = 0; j != col; ++j)
		{
			////��ȡ��ǰ�е�temp_mat��Ϣ
			//���С���㣬����������н���
			if (((int)temp_mat.fras[0][j]) < 0)
			{
				//������а����λ���򷵻ص�mat������
				for (int jj = j + 1; jj != col; ++jj)
				{
					if (((int)temp_mat.fras[0][jj]) >= 0)
					{
						ret_mat.fras[j][(int)temp_mat.fras[0][jj]] = -rref.fras[-((int)temp_mat.fras[0][j] + 1)][jj];
					}
				}
			}
			else//�����С���㣬���������Ĭ�Ͻ�Ϊ1����򽫶�Ӧ���λ�õĽ��ʼ��Ϊ1
			{
				ret_mat.fras[j][(int)temp_mat.fras[0][j]] = (fra)1;
			}
		}
		return ret_mat;
	}
}

