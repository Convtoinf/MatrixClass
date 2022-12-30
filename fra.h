#pragma once
#include<ostream>

class fra
{
private:
	//false表示正数或0
	bool sign;
	unsigned int num;
	unsigned int den;
	fra(unsigned int temp_num, unsigned int temp_den = 1, bool temp_sign = false);
public:
	//默认构造
	fra();
	//构造分数
	fra(int temp_num, int temp_den = 1);
	//拷贝构造
	fra(const fra& temp_fra);
	//约分
	void gcd();
	//负号
	const fra operator-() const;
	//取倒数
	void rec();
	//是否为0
	bool is_zero() const;
	//是否为整数
	bool is_int()const;
	//是否为正数
	bool is_pos()const;
	//是否为负数
	bool is_neg()const;
	//打印分数
	void print_fra() const;
	void print_int()const;
	void print_double()const;
	//cout重载
	friend std::ostream& operator<<(std::ostream& os, const fra& temp_fra);
	//基本判断
	bool operator==(const fra& temp_fra) const;
	bool operator>(const fra& temp_fra) const;
	bool operator<(const fra& temp_fra) const;
	bool operator!=(const fra& temp_fra) const;
	bool operator>=(const fra& temp_fra) const;
	bool operator<=(const fra& temp_fra) const;
	//赋值，加减乘除
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
	//自，加减乘除
	void operator+=(const fra& temp_fra);
	void operator-=(const fra& temp_fra);
	void operator*=(const fra& temp_fra);
	void operator/=(const fra& temp_fra);
	//为整型
	operator int()const;
	//转换为小数
	operator double()const;
	//转化为bool
	operator bool()const;
};


