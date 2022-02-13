#include"MyString.h"
/// <summary>
/// 构造函数
/// </summary>
/// <param name="cstr"></param>
MyString::MyString(const char* cstr) {
	if (cstr) {
		m_data = new char[strlen(cstr) + 1];
		strcpy(m_data, cstr);
		m_size = strlen(cstr);
	}
	else {
		//传入空字符串，创建空字符串
		m_data = new char[1];
		*m_data = '\0';
		m_size = 0;
	}
}
MyString::MyString(const MyString& str) {
	m_data = new char[strlen(str.m_data) + 1];//重新申请空间
	strcpy(m_data, str.m_data);
	m_size = strlen(str.m_data);
}
MyString::MyString(int n, const char c) {
	m_data = new char[n + 1];
	m_size = n;
	int i;
	for (i = 0; i < m_size; i++) {
		m_data[i] = c;
	}
	m_data[i] = '\0';
}
/// <summary>
/// 析构函数
/// </summary>
MyString::~MyString() {
	delete[] m_data;
}
/// <summary>
/// 重载=
/// </summary>
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
/*
MyString& MyString:: operator=(const char* ch) {
	delete[] m_data;//1.清空原有空间
	m_data = new char[strlen(ch) + 1];//2.重新申请空间
	strcpy(m_data, ch);//3.复制
	m_size = strlen(ch);
	return *this;
}
*/
/// <summary>
/// 重载+=
/// </summary>
MyString& MyString:: operator+=(const MyString& str) {
	char* pre = new char[strlen(m_data) + 1];
	strcpy(pre, m_data);//存储原字符串
	delete[] m_data;
	m_data = new char[strlen(pre) + strlen(str.m_data) + 1];
	m_size = strlen(pre) + strlen(str.m_data);
	strcpy(m_data, pre);
	strcat(m_data, str.m_data);
	delete[] pre;
	return *this;
}
/*
MyString& MyString:: operator+=(const char* ch) {
	char* pre = new char[strlen(m_data) + 1];
	strcpy(pre, m_data);//存储原字符串
	delete[] m_data;
	m_data = new char[strlen(pre) + strlen(ch) + 1];
	m_size = strlen(pre) + strlen(ch);
	strcpy(m_data, pre);
	strcat(m_data, ch);
	delete[] pre;
	return *this;
}
*/
/// <summary>
/// 重载==
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
bool MyString::operator==(const MyString& str) {
	if (this->compare(str) == 0) {
		return true;
	}
	else
	{
		return false;
	}
}
/*
bool MyString:: operator==(const char* ch) {
	MyString str(ch);
	if (this->compare(str) == 0) {
		return true;
	}
	else
	{
		return false;
	}
}
*/
/// <summary>
/// 重载[]
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
char& MyString::operator[](int n) {
	return m_data[n];
}
/// <summary>
/// 重载<<
/// </summary>
//全局函数：不在声明友元的类中实现，重载<<输出
ostream& operator<<(ostream& out, MyString& str) {
	out << str.get_c_str();
	return out;
}
/// <summary>
/// 复制从pos开始n个字符
/// </summary>
/// <param name="pos"></param>
/// <param name="n"></param>
/// <returns></returns>
MyString MyString::substr(int pos, int n) const {
	//验证pos合法性
	//验证pos+n是否超过长度
	int len = n;
	if (pos < 0 || pos >= m_size) {
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
	MyString reslut(res);
	delete[] res;
	return reslut;
}
/// <summary>
/// 在pos位置插入
/// </summary>
/*
MyString& MyString::insert(int pos, const char* c) {
	//验证pos合法性
	if (pos < 0 || pos >= m_size) {
		//抛出越界异常
		throw exception("无效的索引位置！");
	}
	char* pre = new char[m_size + 1];
	strcpy(pre, m_data);
	delete[] m_data;
	m_data = new char[strlen(pre) + strlen(c) + 1];
	m_size = strlen(pre) + strlen(c);
	int i;
	for (i = 0; i < pos; i++) {
		m_data[i] = pre[i];
	}
	for (int j = 0; j < strlen(c); j++) {
		m_data[i++] = c[j];
	}
	for (int j = 0; j < strlen(pre) - pos; j++) {
		m_data[i++] = pre[pos + j];
	}
	m_data[i] = '\0';
	delete[] pre;
	return *this;
}
*/
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
/// <summary>
/// 从pos位置删除n个字符
/// </summary>
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
/// <summary>
/// 字符串比较
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
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
/// <summary>
/// 获取某位字符
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
char& MyString::at(int n) {
	if (n < 0 || n >= m_size) {
		throw exception("无效的索引位置！");
	}
	return m_data[n];
}
/// <summary>
/// 从pos处寻找字串，朴素算法
/// </summary>
/// <param name="str"></param>
/// <param name="pos"></param>
/// <returns></returns>
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