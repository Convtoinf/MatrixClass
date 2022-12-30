#pragma once
#include"fra.h"
#include<iostream>

fra::fra() :sign(false), num(0), den(1)
{ }

fra::fra(const fra& temp_fra) : sign(temp_fra.sign), num(temp_fra.num), den(temp_fra.den)
{ }

fra::fra(unsigned int temp_num, unsigned int temp_den, bool temp_sign)
{ 
	if (temp_den == 0)
	{
		std::cout << "error:分母不能为零" << std::endl;
		sign = false;
		num = 0;
		den = 1;
		return;
	}
	if (temp_num == 0)
	{
		sign = false;
		num = 0;
		den = 1;
		return;
	}
	sign = temp_sign;
	num = temp_num;
	den = temp_den;
	this->gcd();
}

fra::fra(int temp_num, int temp_den)
{
	if (temp_den == 0)
	{
		std::cout << "error:分母不能为零" << std::endl;
		sign = false;
		num = 0;
		den = 1;
		return;
	}
	if (temp_num == 0)
	{
		sign = false;
		num = 0;
		den = 1;
		return;
	}
	sign = false;
	if (temp_num < 0)
	{
		temp_num *= -1;
		sign = !sign;
	}
	if (temp_den < 0)
	{
		temp_den *= -1;
		sign = !sign;
	}
	num = temp_num;
	den = temp_den;
	this->gcd();
}
//约分
void fra::gcd()
{
	unsigned int temp_num = num;
	unsigned int temp_den = den;
	unsigned int temp = temp_den;
	while (temp_num % temp_den)
	{
		temp = temp_num % temp_den;
		temp_num = temp_den;
		temp_den = temp;
	}
	num /= temp;
	den /= temp;
}

//负号
const fra fra::operator-() const
{
	if (this->is_zero())
	{
		return *this;
	}
	return fra(num,den,!sign);
}

//取倒数
void fra::rec()
{
	if (this->is_zero())
	{
		std::cout << "error:分数为零，没有倒数。" << std::endl;
		return;
	}
	else
	{
		unsigned int temp = num;
		num = den;
		den = temp;
	}
}
//判断是否为0
bool fra::is_zero() const
{
	return !num;
}

bool fra::is_int()const
{
	return den == 1;
}

bool fra::is_pos()const
{
	if (num == 0)
	{
		return false;
	}
	return !sign;
}

bool fra::is_neg()const
{
	return sign;
}

bool fra::operator==(const fra& temp_fra) const
{
	return (sign == temp_fra.sign) && (num == temp_fra.num) && (den == temp_fra.den);
}

bool fra::operator>(const fra& temp_fra) const
{
	if ((!sign) && temp_fra.sign)
	{
		return true;
	}
	if (sign && (!temp_fra.sign))
	{
		return false;
	}
	if ((!sign) && (!temp_fra.sign))
	{
		return num * temp_fra.den > den * temp_fra.num;
	}
	if (sign && temp_fra.sign)
	{
		return num * temp_fra.den < den* temp_fra.num;
	}
}

bool fra::operator<(const fra& temp_fra) const
{
	return (!(*this > temp_fra)) && (!(*this == temp_fra));
}

bool fra::operator!=(const fra& temp_fra) const
{
	return !(*this == temp_fra);
}

bool fra::operator>=(const fra& temp_fra) const
{
	return !(*this < temp_fra);
}

bool fra::operator<=(const fra& temp_fra) const
{
	return !(*this > temp_fra);
}

fra& fra::operator=(const fra& temp_fra)
{
	sign = temp_fra.sign;
	num = temp_fra.num;
	den = temp_fra.den;
	return *this;
}

const fra fra::operator+(const fra& temp_fra)const
{
	if (this->is_zero()) return temp_fra;
	if (temp_fra.is_zero()) return *this;
	if (((!sign) && (!temp_fra.sign))||(sign && temp_fra.sign))
	{
		if (den == temp_fra.den)
		{
			return fra(num + temp_fra.num, den, sign);
		}
		else
		{
			return fra(num * temp_fra.den + den * temp_fra.num, den * temp_fra.den, sign);
		}
	}
	if ((!sign) && (temp_fra.sign))
	{
		if (den == temp_fra.den)
		{
			long temp_num = num - temp_fra.num;
			if (temp_num >= 0)
			{
				return fra(temp_num, den, false);
			}
			else
			{
				temp_num *= -1;
				return fra(temp_num, den, true);
			}
		}
		else
		{
			long temp_num = num * temp_fra.den - den * temp_fra.num;
			long temp_den = den * temp_fra.den;
			if (temp_num >= 0)
			{
				return fra(temp_num, temp_den, false);
			}
			else
			{
				temp_num *= -1;
				return fra(temp_num, temp_den, true);
			}
		}
	}
	else
	{
		return temp_fra + *this;
	}
}

const fra fra::operator+(const int& temp_int)const
{
	return (fra)temp_int + (*this);
}

const fra operator+(const int& temp_int, const fra& temp_fra)
{
	return (fra)temp_int + temp_fra;
}

const fra fra::operator-(const fra& temp_fra)const
{
	return *this + (-temp_fra);
}

const fra fra::operator-(const int& temp_int)const
{
	return (*this) - (fra)temp_int;
}

const fra operator-(const int& temp_int, const fra& temp_fra)
{
	return (fra)temp_int - temp_fra;
}

const fra fra::operator*(const fra& temp_fra)const
{
	if (this->is_zero()) return *this;
	if (temp_fra.is_zero()) return temp_fra;
	if ((sign && temp_fra.sign) || ((!sign) && (!temp_fra.sign)))
	{
		return fra(num * temp_fra.num, den * temp_fra.den, false);
	}
	else
	{
		return fra(num * temp_fra.num, den * temp_fra.den, true);
	}
}

const fra fra::operator*(const int& temp_int)const
{
	return (*this) * (fra)temp_int;
}

const fra operator*(const int& temp_int, const fra& temp_fra)
{
	return (fra)temp_int * temp_fra;
}

const fra fra::operator/(const fra& temp_fra) const
{
	if (temp_fra.is_zero())
	{
		std::cout << "error:除数不能为零" << std::endl;
		return fra(0);
	}
	fra temp = temp_fra;
	temp.rec();
	return (*this) * (temp);
}

const fra fra::operator/(const int& temp_int)const
{
	return (*this) / (fra)temp_int;
}

const fra operator/(const int& temp_int, const fra& temp_fra)
{
	return (fra)temp_int / temp_fra;
}

void fra::operator+=(const fra& temp_fra)
{
	*this = *this + temp_fra;
}

void fra::operator-=(const fra& temp_fra)
{
	*this += -temp_fra;
}

void fra::operator*=(const fra& temp_fra) 
{
	*this = (*this) * temp_fra;
}

void fra::operator/=(const fra& temp_fra)
{

	*this = (*this) / temp_fra;
}

void fra::print_fra() const
{
	if (sign)
	{
		std::cout << "-" << num << "/" << den;
	}
	else
	{
		std::cout << num << "/" << den;
	}
}

void fra::print_int()const
{
	std::cout << (int)(*this);
}

void fra::print_double()const
{
	std::cout << (double)(*this);
}

std::ostream& operator<<(std::ostream& os, const fra& temp_fra)
{
	if (temp_fra.sign)
	{
		os << "-" << temp_fra.num << "/" << temp_fra.den;
	}
	else
	{
		os << temp_fra.num << "/" << temp_fra.den;
	}
	return os;
}

fra::operator int()const
{
	return (int)((double)*this);
}

fra::operator double()const
{
	if (sign)
	{
		return -((double)(num / den));
	}
	return (double)(num / den);
}

fra::operator bool()const
{
	return (bool)num;
}