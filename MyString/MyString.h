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
	char* m_data;//ָ��ָ���ַ����飬4�ֽ�
	int m_size;//�ַ�������
public:
	//���캯��
	//����ʱ��Ĭ�ϲ������ڶ���ʱ��Ҫɾ������������ض���Ĭ�ϲ���
	//���캯���в�ʱ������Ĭ�Ϲ��캯�������������Ҫ�ٴ�����Ĭ�Ϲ��캯���ˣ�����������ʾ���Ĭ�Ϲ��캯��
	MyString(const char* cstr = 0);//1���޲ι���2��ʹ��c����ַ�������
	MyString(const MyString& str);//3����������
	MyString(int n, const char c);//4��ʹ��n���ַ�c��ʼ��

	//��������
	~MyString();

	//���ط���
	// ����+
	//�ڽ�����������ʱ����Ҫ����ֵΪ�������ͣ����Բ������Ϊvoid
	MyString& operator=(const MyString& str);//����MyString=MyString
	//MyString& operator=(const char* ch);//����char*=MyString
	//����+=
	MyString& operator+=(const MyString& str);
	//MyString& operator+=(const char* ch);
	//����==
	bool operator==(const MyString& str);
	//bool operator==(const char* ch);
	//����[]
	char& operator[](int n);
	//����<<
	friend ostream& operator<<(ostream& out, MyString& str);//����<<����Ϊ��Ԫ����

	
	//����C����ַ���
	char* get_c_str() const { return m_data; }
	//�����ַ�������
	int size() const { return m_size; }
	//������pos��ʼ��n���ַ���ɵ��ַ���
	MyString substr(int pos , int n) const;
	//��pos������,�������ԭ�ȴ��ڵı����У���������
	//MyString& insert(int pos, const char* c);
	MyString& insert(int pos, const MyString& str);
	//ɾ����pos��ʼ��n���ַ�
	MyString& erase(int pos, int n);
	//�ַ����Ƚ�
	int compare(const MyString& str) const;
	//��ȡĳλ�ַ�
	char& at(int n);
	//�����ַ��Ӵ�,��pos��ʼ���ص�һ����ĸ��λ��
	//ȱʡʱ��ͷ��ʼ�������β�д�ں���
	int find(const MyString& str, int pos = 0);
	int find(const char* ch, int pos = 0);
	//split���������ַ��з��ַ���������MyString����
	vector<MyString> split(const MyString& flag);

};

#endif // _MYSTRING_

