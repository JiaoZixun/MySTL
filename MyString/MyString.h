#pragma once
#ifndef _MYSTRING_
#define _MYSTRING_
#include<cstringt.h>
#include<iostream>
#include<exception>
#include<vector>
using namespace std;
/// <summary>
/// 
/// </summary>
class MyString {
private:
	char* m_data;//指针指向字符数组，4字节
	int m_size;//字符串长度
public:
	//构造函数
	//声明时用默认参数，在定义时需要删除，否则出现重定义默认参数
	//构造函数有参时包含了默认构造函数的情况，不需要再次声明默认构造函数了，否则会出现提示多个默认构造函数
	MyString(const char* cstr = 0);//1、无参构造2、使用c风格字符串构造
	MyString(const MyString& str);//3、拷贝构造
	MyString(int n, const char c);//4、使用n个字符c初始化

	//析构函数
	~MyString();

	//重载符号
	// 重载+
	//在进行连续等于时，需要返回值为引用类型，所以不能设计为void
	MyString& operator=(const MyString& str);//重载MyString=MyString
	//MyString& operator=(const char* ch);//重载char*=MyString
	//重载+=
	MyString& operator+=(const MyString& str);
	//MyString& operator+=(const char* ch);
	//重载==
	bool operator==(const MyString& str);
	//bool operator==(const char* ch);
	//重载[]
	char& operator[](int n);
	//重载<<
	friend ostream& operator<<(ostream& out, MyString& str);//重载<<声明为友元函数

	
	//返回C风格字符串
	char* get_c_str() const { return m_data; }
	//返回字符串长度
	int size() const { return m_size; }
	//返回由pos开始的n个字符组成的字符串
	MyString substr(int pos , int n) const;
	//在pos处插入,结果传入原先存在的变量中，返回引用
	//MyString& insert(int pos, const char* c);
	MyString& insert(int pos, const MyString& str);
	//删除从pos开始的n个字符
	MyString& erase(int pos, int n);
	//字符串比较
	int compare(const MyString& str) const;
	//获取某位字符
	char& at(int n);
	//查找字符子串,从pos开始返回第一个字母的位置
	//缺省时从头开始，带参形参写在后面
	int find(const MyString& str, int pos = 0);
	int find(const char* ch, int pos = 0);
	//split方法，按字符切分字符串，返回MyString数组
	vector<MyString> split(const MyString& flag);

};

#endif // _MYSTRING_

