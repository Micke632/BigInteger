#include "pch.h"
#include "..\BigInt\bigint.h"
#include <vector>
#include <memory>

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}


TEST(TestCaseName, TestName2) {
	BigInt b{};
	EXPECT_EQ("0", b.add("0", "0"));
	EXPECT_EQ("3",b.add("1", "2"));
	EXPECT_EQ("10", b.add("5", "5"));
	EXPECT_EQ("11", b.add("5", "6"));
	EXPECT_EQ("12", b.add("6", "6"));
	EXPECT_EQ("11", b.add("1", "10"));
	EXPECT_EQ("15", b.add("10", "5"));
	EXPECT_EQ("20", b.add("10", "10"));
	EXPECT_EQ("35", b.add("16", "19"));
	EXPECT_EQ("100", b.add("50", "50"));
	EXPECT_EQ("100", b.add("99", "1"));
	EXPECT_EQ("100", b.add("1", "99"));
	EXPECT_EQ("100", b.add("2", "98"));
	EXPECT_EQ("101", b.add("4", "97"));
	EXPECT_EQ("108", b.add("98", "10"));
	EXPECT_EQ("200", b.add("100", "100"));
	EXPECT_EQ("200", b.add("200", "0"));
	EXPECT_EQ("200", b.add("0", "200"));
	
	EXPECT_EQ("210", b.add("9", "201"));
	EXPECT_EQ("1001", b.add("2", "999"));
	EXPECT_EQ("1000", b.add("666", "334"));
	EXPECT_EQ("1010", b.add("666", "344"));
	EXPECT_EQ("10092", b.add("9991", "101"));
	EXPECT_EQ("100000000000010", b.add("100000000000009", "1"));

	b.add("233");
	EXPECT_EQ("333", b.add("100"));

	
	
}

TEST(TestCaseName, TestName3) {
	BigInt b{};
	EXPECT_EQ("0", b.sub("5", "5"));
	EXPECT_EQ("1", b.sub("2", "1"));
	EXPECT_EQ("9", b.sub("10", "1"));
	EXPECT_EQ("1", b.sub("10", "9"));
	EXPECT_EQ("0", b.sub("10", "10"));
	EXPECT_EQ("90", b.sub("100", "10"));	
	EXPECT_EQ("1191", b.sub("1231", "40"));
	EXPECT_EQ("10680", b.sub("11111", "431"));
		

	EXPECT_EQ("3", b.sub("102", "99"));
	


   
}

TEST(TestCaseName, TestNameMul) {
	BigInt b{};
	EXPECT_EQ("2", b.mul("1", "2"));
	EXPECT_EQ("9", b.mul("3", "3"));
	EXPECT_EQ("30", b.mul("10", "3"));
	EXPECT_EQ("52", b.mul("13", "4"));
	EXPECT_EQ("52", b.mul("4", "13"));
	
	EXPECT_EQ("100", b.mul("10", "10"));
	EXPECT_EQ("1000", b.mul("100", "10"));
	EXPECT_EQ("10000", b.mul("100", "100"));
	EXPECT_EQ("10000000000", b.mul("100000", "100000"));
	EXPECT_EQ("1000000000000000000000000", b.mul("1000000000000", "1000000000000"));

	EXPECT_EQ("10098", b.mul("187", "54"));
	EXPECT_EQ("132000", b.mul("4000", "33"));
	EXPECT_EQ("1496385", b.mul("45345", "33"));

}


TEST(TestCaseName, TestNameDiv) {
	BigInt b{};
	
	EXPECT_EQ("3", b.div("6", 2));
	EXPECT_EQ("5", b.div("15",3));
	EXPECT_EQ("30", b.div("120", 4));
	EXPECT_EQ("19900", b.div("99500", 5));
	EXPECT_EQ("33", b.div("1496385", 45345));

	EXPECT_EQ("1000000000000000000000", b.div("1000000000000000000000000", 1000));


}
TEST(TestCaseName, TestName5) {
	BigInt b{};
	b.add("233");
	EXPECT_EQ("333", b.add("100"));

	BigInt c(b);
	EXPECT_EQ("333", c.getValue());

	BigInt d;
	d.add("100");

	BigInt e = d;
	EXPECT_EQ("100", e.getValue());
	e.mul("10");
	EXPECT_EQ("1000", e.getValue()); 

	e.div(25);
	EXPECT_EQ("40", e.getValue());

	std::vector<BigInt> v;
	
	v.push_back(BigInt{});

	BigInt f = e;
	v.push_back(f);


	BigInt ff = std::move(b);

	EXPECT_EQ("333", ff.getValue());
	EXPECT_EQ("", b.getValue());

}

TEST(TestCaseName, TestName4) {
	BigInt b{};
	EXPECT_EQ("-1", b.sub("1", "2"));
 	EXPECT_EQ("-3", b.sub("99", "102"));
	EXPECT_EQ("-1", b.sub("10", "11"));
	EXPECT_EQ("-899", b.sub("100", "999"));

	EXPECT_EQ("-10", b.add("-5", "-5"));
	EXPECT_EQ("-20", b.add("-10", "-10"));
	EXPECT_EQ("0", b.add("-5", "5"));
	EXPECT_EQ("1", b.add("-1", "2"));
	EXPECT_EQ("2", b.add("-99", "101"));



	EXPECT_EQ("0", b.add("5", "-5"));
	EXPECT_EQ("1", b.add("2", "-1"));
	EXPECT_EQ("-1", b.add("10", "-11"));


	EXPECT_EQ("-20", b.sub("-10", "-10"));

//	EXPECT_EQ("-11", b.sub("-10", "1"));


}