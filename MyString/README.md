# String类的实现

对string类的基本功能进行复现，找到了一些错误和c++编程中的细节问题，都在此记录下来。MyString中实现了基本的构造函数、析构函数，重载了常用符号，并且给出了一些常用函数的实现。

在实现过程中，对于是否加入const有两种情况：1.在参数前加入说明该函数不更改此参数；2.在函数后加入说明该函数不更改成员的值。

## MyString头文件

```c++
class MyString {
private:
	char* m_data;//指针指向字符数组，4字节
	size_t m_size;//字符串长度
public:
	//构造函数
	MyString(const char* cstr = 0);//1、无参构造 2、使用c风格字符串构造
	MyString(const MyString& str);//3、拷贝构造
	MyString(int n, const char c);//4、使用n个字符c初始化
	//析构函数
	~MyString();
	// 重载=
	MyString& operator=(const MyString& str);//重载MyString=MyString
	//重载+=
	MyString& operator+=(const MyString& str);
	//重载==
	bool operator==(const MyString& str);
	//重载[]
	char& operator[](int n);
	//重载<<
	friend ostream& operator<<(ostream& out, MyString& str);//重载<<声明为友元函数
	//返回C风格字符串
	char* get_c_str() const { return m_data; }
	//返回字符串长度
	size_t size() const { return m_size; }
	//返回由pos开始的n个字符组成的字符串
	MyString substr(int pos , int n) const;
	//在pos处插入,结果传入原先存在的变量中，返回引用
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

```

## 具体实现

以下分别给出每个函数的具体实现、遇到的问题和需要关注的细节。

### 1.构造函数

在声明构造函数时，若有默认参数，则不应该再次声明和该默认参数相同的构造函数，例如：

```c++
MyString(const char* cstr = 0);
MyString();//无参构造函数和上述构造函数的默认参数情况重合，会提示多个默认构造函数
```

```c++
MyString::MyString(const char* cstr) {
	if (cstr) {
		m_data = new char[strlen(cstr) + 1];
		strcpy(m_data, cstr);
		m_size = strlen(cstr);
	}
	else {//对应无参构造函数
		//传入空字符串，创建空字符串
		m_data = new char[1];
		*m_data = '\0';
		m_size = 0;
	}
}
MyString::MyString(const MyString& str) {//拷贝构造函数，深拷贝
	m_data = new char[strlen(str.m_data) + 1];//重新申请空间
	strcpy(m_data, str.m_data);
	m_size = strlen(str.m_data);
}
MyString::MyString(int n, const char c) {
    if(n < 0)	throw exception("无效的个数！");
	m_data = new char[n + 1];
	m_size = n;
	int i;
	for (i = 0; i < m_size; i++) {
		m_data[i] = c;
	}
	m_data[i] = '\0';
}
```

### 2.析构函数

```c++
MyString::~MyString() {
	delete[] m_data;
}
```

### 3.重载

#### 1）重载=

两个参数格式，传入MyString或c风格字符串，在进行连续等于时，需要返回值为引用类型，所以不能设计为void

```c++
MyString& MyString::operator=(const MyString& str) {
	//必须判断是否是自我赋值，若无判断会直接删除当前空间，返回产生野指针
	if (this == &str) {
		return *this;
	}
	delete[] m_data;//1.清空原有空间
	m_data = new char[strlen(str.m_data) + 1];//2.重新申请空间
	strcpy(m_data, str.m_data);//3.复制
	m_size = strlen(str.m_data);
	return *this;
}
```

#### 2）重载+=

```c++
MyString& MyString:: operator+=(const MyString& str) {
	char* pre = new char[strlen(m_data) + 1];
	strcpy(pre, m_data);//存储原字符串
	delete[] m_data;
	m_data = new char[strlen(pre) + strlen(str.m_data) + 1];
	m_size = strlen(pre) + strlen(str.m_data);
	strcpy(m_data, pre);
	strcat(m_data, str.m_data);
	delete[] pre;//清除申请空间，防止内存泄漏
	return *this;
}
```

#### 3）重载==

根据内部函数compare返回结果

```c++
bool MyString::operator==(const MyString& str) {
	if (this->compare(str) == 0)
		return true;
	else
		return false;
}
```

#### 4）重载[]

使用[]取值不会进行越界检查，越界会直接中断程序

```c++
char& MyString::operator[](int n) {
	return m_data[n];
}
```

#### 5）重载<<

通过内部函数get_c_str()在流对象中返回c风格字符串

```c++
ostream& operator<<(ostream& out, MyString& str) {
	out << str.get_c_str();
	return out;
}
```

### 4.其他成员函数

当传入参数为c风格字符串时，会首先调用构造函数生成MyString对象，再进入该函数，并在函数结束时调用析构函数销毁该对象。

在函数中使用new在堆中申请空间，需要在函数结束前手动销毁空间。

1）从pos为开始，复制n位

```c++
MyString MyString::substr(int pos, int n) const {
	//验证pos合法性
	//验证pos+n是否超过长度
	int len = n;
	if (pos < 0 || pos >= m_size || n < 0) {
		//抛出越界异常
		throw exception("无效的索引位置！");
	}
	else if (pos + n > m_size) {
		len = m_size - pos;
	}
	char* res = new char[len + 1];
	int i;
	for (i = 0; i < len; i++) {
		res[i] = m_data[pos + i];
	}
	res[i] = '\0';
	MyString reslut(res);//重新包装为MyString对象
	delete[] res;
	return reslut;//在函数结束后会调用reslut对象的析构函数，在接收端调用拷贝构造函数生成结果对象
}
```

2）在pos位插入字符串

```c++
MyString& MyString::insert(int pos, const MyString& str) {
	//验证pos合法性
	if (pos < 0 || pos >= m_size) {
		//抛出越界异常
		throw exception("无效的索引位置！");
	}
	char* pre = new char[m_size + 1];
	strcpy(pre, m_data);
	delete[] m_data;
	m_data = new char[strlen(pre) + strlen(str.m_data) + 1];
	m_size = strlen(pre) + strlen(str.m_data);
	int i;
	for (i = 0; i < pos; i++) {
		m_data[i] = pre[i];
	}
	for (int j = 0; j < strlen(str.m_data); j++) {
		m_data[i++] = str.m_data[j];
	}
	for (int j = 0; j < strlen(pre) - pos; j++) {
		m_data[i++] = pre[pos + j];
	}
	m_data[i] = '\0';
	delete[] pre;
	return *this;
}
```

3）从pos位删除n位

```c++
MyString& MyString:: erase(int pos, int n) {
	if (pos < 0 || pos >= m_size) {
		//抛出越界异常
		throw exception("无效的索引位置！");
	}
	else if (pos + n > m_size) {
		char* pre = new char[m_size + 1];
		strcpy(pre, m_data);
		delete[] m_data;
		m_data = new char[pos + 1];
		m_size = pos;
		strncpy(m_data, pre, pos);
		m_data[pos] = '\0';
		delete[] pre;
		return *this;
	}
	char* pre = new char[m_size + 1];
	strcpy(pre, m_data);
	delete[] m_data;
	m_data = new char[m_size - n + 1];
	m_size = m_size - n;
	int i;
	for (i = 0; i < pos; i++) {
		m_data[i] = pre[i];
	}
	for (int j = pos + n; j < strlen(pre); j++) {
		m_data[i++] = pre[j];
	}
	m_data[i] = '\0';
	delete[] pre;
	return *this;
}
```

4）字符串比较函数，自身大返回1，相等为0，小于为-1

```c++
int MyString::compare(const MyString& str) const {
	int i = 0, j = 0;
	while (m_data[i] != '\0' && str.m_data[j] != '\0') {
		if ((int)m_data[i] > (int)str.m_data[j]) {
			return 1;
		}
		else if ((int)m_data[i] < (int)str.m_data[j]) {
			return -1;
		}
		i++; j++;
	}
	if (m_data[i] != '\0')	return 1;
	else if (str.m_data[j] != '\0')	return -1;
	return 0;
}
```

5）获取某位，会检查数组越界情况

```c++
char& MyString::at(int n) {
	if (n < 0 || n >= m_size) {
		throw exception("无效的索引位置！");
	}
	return m_data[n];
}
```

6）查找函数，在主串中pos位起始，查找子串开始位置

```c++
int MyString::find(const MyString& str, int pos) {
	return this->find(str.m_data, pos);
}
int MyString::find(const char* ch, int pos) {
	if (pos >= m_size) {
		throw exception("无效的索引位置！");
	}
	int len = strlen(ch);
	if (len > m_size - pos) {
		return -1;
	}
	int i = pos, j = 0;
	while (m_data[i] != '\0' && ch[j] != '\0') {
		while (m_data[i] != '\0' && ch[j] != '\0'&& m_data[i] == ch[j]) {
			i++; j++;
		}
		if (m_data[i] == '\0' || ch[j] == '\0') {
			break;
		}
		
		i++;
		j = 0;
	}
	if (ch[j] == '\0') {
		return i - len;
	}
	if (m_data[i] == '\0') {
		return -1;
	}
	return -1;
}
```

7）split函数，将字符串按给定标志切分，放入MyString数组

对于返回数组的函数，在函数内部声明的数组不能返回引用，当函数结束时空间被销毁

```c++
vector<MyString> MyString::split(const MyString& flag) {
	vector<MyString>res;
	int i = 0;
	for (; i < m_size;) {
		int pos = this->find(flag, i);
		if (pos == -1) {
			break;
		}
		MyString str = this->substr(i, pos - i);
		res.push_back(str);
		i = pos + 1;
	}
	MyString str = this->substr(i, m_size - i);
	res.push_back(str);
	return res;
}
```

## 简单测试

简单的测试了上述函数，对于很大的字符串和一些边界问题没有深入研究，希望读者可以提出。在该类中借助exception标准异常库只实现了一部分的异常处理功能，还不够完善。

```c++
#include"MyString.h"
#include<iostream>
#include<string>
using namespace std;
int main() {
	const char* ch = "hello";
	MyString str1;
	MyString str2(ch);
	MyString str3(str2);
	MyString str4(10,'c');
	str1 = str2;
	str1 += str2;
	str4 += ch;
	MyString str5 = str4.substr(0, 6);
	MyString str6 = str4.substr(10, 6);
	std::cout << "str1:" << str1 << std::endl;
	std::cout << "str1.size():" << str1.size() << std::endl;
	std::cout << "str2:" << str2 << std::endl;
	std::cout << "str2.size():" << str2.size() << std::endl;
	std::cout << "str3:" << str3 << std::endl;
	std::cout << "str3.size():" << str3.size() << std::endl;
	std::cout << "str4:" << str4 << std::endl;
	std::cout << "str4.size():" << str4.size() << std::endl;
	std::cout << "str5:" << str5 << std::endl;
	std::cout << "str5.size():" << str5.size() << std::endl;
	std::cout << "str6:" << str6 << std::endl;
	std::cout << "str6.size():" << str6.size() << std::endl;
	MyString str7 = "0123456";
	str7.insert(6, "7");
	std::cout << "str7:" << str7 << std::endl;
	std::cout << "str7.size():" << str7.size() << std::endl;
	str7.insert(6, str3);
	std::cout << "str7:" << str7 << std::endl;
	std::cout << "str7.size():" << str7.size() << std::endl;
	str7.erase(0, 1);
	std::cout << "str7:" << str7 << std::endl;
	std::cout << "str7.size():" << str7.size() << std::endl;
	cout << "str7.compare(str1):" << str7.compare(str1) << endl;
	if (str1 == str2) {
		cout << "str1 == str2" << endl;
	}
	else {
		cout << "str1 != str2" << endl;
	}
	if (str1 == "hellohello") {
		cout << "str1 == hellohello" << endl;
	}
	else {
		cout << "str1 != hellohello" << endl;
	}
	cout << "str1[5]= " << str1[5] << endl;
	try {
		cout << str1.at(100);

	}
	catch(exception& e){
		cout << e.what() << endl;
	}

	cout << "str4.find('ccccccc',3):" << str4.find("ccccccc",3) << endl;
	cout << "str7.find(str1):" << str7.find(str1) << endl;
	cout << "str1.find(str2):" << str1.find(str2) << endl;
	cout << "str4.find(str2):" << str4.find(str2) << endl;
    
	MyString str8 = "www.baidu.com";
	vector<MyString>ans = str8.split(".");
	for (auto it : ans)	cout << it << endl;
	return 0;
}
```

