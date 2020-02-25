#pragma once

#include <string>

class BigInt
{	
private:
	std::string number;	
	int sign;

public:
	BigInt();
	~BigInt();
	BigInt(const BigInt &) = default;
	BigInt(BigInt &&) = default;
	BigInt& operator=(const BigInt &) = default;

	std::string getValue() const { return number;}
	std::string add(std::string b);
	std::string sub(std::string b);
	std::string mul(std::string b);
	std::string div(int b);
	std::string add(int b);
	
	static std::string add(std::string a, std::string b);
	static std::string sub(std::string a, std::string b,int sign=0);
	static std::string mul(std::string a, std::string b);
	static std::string div(std::string a, int  b);

};

