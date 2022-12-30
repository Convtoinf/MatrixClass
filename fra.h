#pragma once
#include<ostream>

class fra
{
private:
	//false��ʾ������0
	bool sign;
	unsigned int num;
	unsigned int den;
	fra(unsigned int temp_num, unsigned int temp_den = 1, bool temp_sign = false);
public:
	//Ĭ�Ϲ���
	fra();
	//�������
	fra(int temp_num, int temp_den = 1);
	//��������
	fra(const fra& temp_fra);
	//Լ��
	void gcd();
	//����
	const fra operator-() const;
	//ȡ����
	void rec();
	//�Ƿ�Ϊ0
	bool is_zero() const;
	//�Ƿ�Ϊ����
	bool is_int()const;
	//�Ƿ�Ϊ����
	bool is_pos()const;
	//�Ƿ�Ϊ����
	bool is_neg()const;
	//��ӡ����
	void print_fra() const;
	void print_int()const;
	void print_double()const;
	//cout����
	friend std::ostream& operator<<(std::ostream& os, const fra& temp_fra);
	//�����ж�
	bool operator==(const fra& temp_fra) const;
	bool operator>(const fra& temp_fra) const;
	bool operator<(const fra& temp_fra) const;
	bool operator!=(const fra& temp_fra) const;
	bool operator>=(const fra& temp_fra) const;
	bool operator<=(const fra& temp_fra) const;
	//��ֵ���Ӽ��˳�
	fra& operator=(const fra& temp_fra);
	const fra operator+(const fra& temp_fra) const;
	const fra operator+(const int& temp_int) const;
	friend const fra operator+(const int& temp_int, const fra& temp_fra);
	const fra operator-(const fra& temp_fra) const;
	const fra operator-(const int& temp_int) const;
	friend const fra operator-(const int& temp_int, const fra& temp_fra);
	const fra operator*(const fra& temp_fra) const;
	const fra operator*(const int& temp_int) const;
	friend const fra operator*(const int& temp_int,const fra& temp_fra);
	const fra operator/(const fra& temp_fra) const;
	const fra operator/(const int& temp_int) const;
	friend const fra operator/(const int& temp_int, const fra& temp_fra);
	//�ԣ��Ӽ��˳�
	void operator+=(const fra& temp_fra);
	void operator-=(const fra& temp_fra);
	void operator*=(const fra& temp_fra);
	void operator/=(const fra& temp_fra);
	//Ϊ����
	operator int()const;
	//ת��ΪС��
	operator double()const;
	//ת��Ϊbool
	operator bool()const;
};


