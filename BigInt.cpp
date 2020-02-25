#include "BigInt.h"
#include <math.h>
#include <algorithm>
#include <queue>

namespace {


	std::string prepare(const std::string &x, int sign)
	{
		std::string res = x;
		std::reverse(res.begin(), res.end());

		//erase leading zeros
		res.erase(0, res.find_first_not_of('0'));
		if (res.empty()) {
			res = "0";
		}
		if (sign == -1) {
			if (res[res.size() - 1] == '-') {
				res.insert(0, 1, '-');
				res.erase(res.size() - 1, 1);
			}
			else {
				res.insert(0, 1, '-');
			}
		}
		return res;
	}

	struct Number {
		Number(std::string a) :number(a), negative(false)
		{
			negative = number[0] == '-';
			if (negative) {
				number.erase(0, 1);
			}
		}


		int getNumberAt(int i) const {
			if (i < 0) return 0;
			return number[i] - '0';
		}
		int getSize() const {
			return number.size();
		}
		std::string number;
		bool negative;
	};
}


BigInt::BigInt()
{
}


BigInt::~BigInt()
{
}


std::string BigInt::add(std::string b)
{
	number = add(this->number, b);
	return number;
}

std::string BigInt::sub(std::string b)
{
	number = sub(this->number, b);
	return number;
}

std::string BigInt::mul(std::string b)
{
	number = mul(this->number, b);
	return number;
}


std::string BigInt::div(int b)
{
	number = div(this->number, b);
	return number;
}


std::string BigInt::add(std::string a, std::string b)
{
	std::string res;

	Number a_number(a);
	Number b_number(b);
	int sign = 0;
	if (a_number.negative && !b_number.negative) {
		std::swap(a, b);
		//b is now negativ, remove -
		b = b.erase(0, 1);
		return sub(a, b);
	}
	else if (!a_number.negative  && b_number.negative) {
		b = b.erase(0, 1);
		return sub(a, b);
	}
	else if (a_number.negative && b_number.negative) {
		sign = -1;
	}

	int a_counter = a_number.getSize() - 1;
	int b_counter = b_number.getSize() - 1;
	int rest = 0;

	while (a_counter >= 0 || b_counter >= 0) {
		int a_val = a_number.getNumberAt(a_counter);
		int b_val = b_number.getNumberAt(b_counter);

		int t = a_val + b_val + rest;
		if (t >= 10) {
			int r = t % 10;
			res += '0' + r;
			rest = 1;

		}
		else {
			rest = 0;
			res += '0' + t;
		}

		a_counter--;
		b_counter--;

	}

	if (rest == 1) {
		res += "1";

	}

	return prepare(res, sign);


}

std::string BigInt::sub(std::string a, std::string b, int sign )
{
	std::string res;

	int rest = 0;

	if (b.size() > a.size()) {
		//b is higher, swap
		std::swap(a, b);
		sign = -1;
	}

	Number a_number(a);
	Number b_number(b);

	if (a_number.negative && b_number.negative) {
		return add(a, b);
	}
	if (a_number.negative && !b_number.negative) {
		return add(a, b);
	}

	int a_counter = a_number.getSize() - 1;
	int b_counter = b_number.getSize() - 1;

	while (a_counter >= 0 || b_counter >= 0) {

		int a_val = a_number.getNumberAt(a_counter);
		int b_val = b_number.getNumberAt(b_counter);

		int s = rest + a_val - b_val;
		if (s < 0) {
			if (a_counter == 0) {
				//b is higher , swap a,b
				return sub(b, a, -1);				
			}
			if (a_counter == 1 && b_counter == 1) {
				int a_v = a_number.getNumberAt(0);
				int b_v = b_number.getNumberAt(0);
				if (a_v - b_v - 1 < 0 ) {
					//b is higher , swap a,b
					return sub(b, a, -1);			
				}
			}	
			rest = -1; 
			s += 10; 
		}
		else    
			rest = 0;

		res += '0' + s;
	

		a_counter--;
		b_counter--;
	
	}
	

	return prepare(res, sign);
}


std::string BigInt::mul(std::string a, std::string b)
{

	int rest = 0;

	if (b.size() > a.size()) {
		std::swap(a, b);
	
	}

	Number a_number(a);
	Number b_number(b);
		
	int a_counter = a_number.getSize() - 1;
	int b_counter = b_number.getSize() - 1;
		
	std::string row;

	BigInt res;
	int rows = 0;
	while (a_counter >= 0 || b_counter >= 0) {

		int a_val = a_number.getNumberAt(a_counter);
		int b_val = b_number.getNumberAt(b_counter);

		int t = (a_val * b_val) + rest;
		rest = t / 10;
		int r = t % 10;
		row += '0'+ r;
	
		if (a_counter >= 0) {
			a_counter--;
		}	
		if (a_counter < 0) {
			b_counter--;
			if (rest)
				row += '0' + rest;

			rest = 0;
			res.add(prepare(row, 0));

			if (b_counter >= 0) {

				row.clear();
				rows++;
				for (int i = 0; i < rows; i++) {
					row += '0';
				}
								
				a_counter = a_number.getSize() - 1;
			}
		}
	
	}

	return res.getValue();
	
}

std::string BigInt::div(std::string a, int divisor)
{
	std::string res;

	int rest = 0;
	
	Number a_number(a);
	
	int a_counter = 0;	
	
	for (int a_counter = 0; a_counter < a.length(); a_counter++) {

		int a_val = a_number.getNumberAt(a_counter);

		int t = rest*10 + a_val;
		rest = t % divisor;
		int q = t / divisor;
		res += '0' + q;			
	}

	res.erase(0, res.find_first_not_of('0'));
	if (res.empty()) {
		res = "0";
	}

	return res;
}