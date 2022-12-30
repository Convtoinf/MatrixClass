#pragma once
#include"fra.h"
class mat
{
private:
	fra** fras;
	unsigned int row;
	unsigned int col;
public:
	//�������������ʼ��
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
	//����һ��E��
	mat(unsigned int n);
	//����һ��r��c�е�����0ΪĬ�ϳ�ʼ��
	mat(unsigned int r, unsigned int c,int n=0);
	//���
	mat(const mat& temp_mat);
	//��������
	~mat();
	//��������
	unsigned int get_row()const;
	//��������
	unsigned int get_col()const;
	//�ж��Ƿ�Ϊ����
	bool is_squ()const;
	//�ж��Ƿ�Ϊ�Գ���
	bool is_symm()const;
	//�ȺŸ�ֵ
	mat& operator=(const mat& temp_mat);
	//��ӡ��������ʽ��������ʽ��С����ʽ��
	void print_fra()const;
	void print_int()const;
	void print_double()const;
	//ת��
	void tran();
	//�����󣬲�����
	const mat inv()const;
	//��������
	void swap_row(unsigned int r1, unsigned int r2);
	//��������
	void swap_col(unsigned int c1, unsigned int c2);
	//��r1�е�k���ӵ�r2����
	void tran_row(fra k, unsigned int r1, unsigned int r2);
	//��c1�е�k���ӵ�c2����
	void tran_col(fra k, unsigned int c1, unsigned int c2);
	//��r�г�k
	void mul_row(fra k, unsigned int r);
	//��c�г�k
	void mul_col(fra k, unsigned int c);
	//�õ���r��
	const mat get_row(unsigned int r)const;
	//�õ���c��
	const mat get_col(unsigned int c)const;
	//��������ʽ
	const fra det()const;
	//����Ӽ���
	const mat operator+(const mat& temp_mat)const;
	const mat operator+(const fra& temp_fra)const;
	friend const mat operator+(const fra& temp_fra, const mat& temp_mat);
	const mat operator-(const mat& temp_mat)const;
	const mat operator-(const fra& temp_fra)const;
	friend const mat operator-(const fra& temp_fra, const mat& temp_mat);
	const mat operator*(const mat& temp_mat)const;
	const mat operator*(const fra& temp_fra)const;
	friend const mat operator*(const fra& temp_fra, const mat& temp_mat);
	//����������
	int rank()const;
	//�ã���ʾ����ƴ��
	const mat operator ,(const mat& temp_mat)const;
	//��| ��ʾ����ƴ��
	const mat operator| (const mat& temp_mat)const;
	//���������
	const mat rref()const;
	//�������ϵ
	const mat null()const;
};

