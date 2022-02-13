#include"MyString.h"
/// <summary>
/// ���캯��
/// </summary>
/// <param name="cstr"></param>
MyString::MyString(const char* cstr) {
	if (cstr) {
		m_data = new char[strlen(cstr) + 1];
		strcpy(m_data, cstr);
		m_size = strlen(cstr);
	}
	else {
		//������ַ������������ַ���
		m_data = new char[1];
		*m_data = '\0';
		m_size = 0;
	}
}
MyString::MyString(const MyString& str) {
	m_data = new char[strlen(str.m_data) + 1];//��������ռ�
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
/// ��������
/// </summary>
MyString::~MyString() {
	delete[] m_data;
}
/// <summary>
/// ����=
/// </summary>
MyString& MyString::operator=(const MyString& str) {
	//�����ж��Ƿ������Ҹ�ֵ�������жϻ�ֱ��ɾ����ǰ�ռ䣬���ز���Ұָ��
	if (this == &str) {
		return *this;
	}
	delete[] m_data;//1.���ԭ�пռ�
	m_data = new char[strlen(str.m_data) + 1];//2.��������ռ�
	strcpy(m_data, str.m_data);//3.����
	m_size = strlen(str.m_data);
	return *this;
}
/*
MyString& MyString:: operator=(const char* ch) {
	delete[] m_data;//1.���ԭ�пռ�
	m_data = new char[strlen(ch) + 1];//2.��������ռ�
	strcpy(m_data, ch);//3.����
	m_size = strlen(ch);
	return *this;
}
*/
/// <summary>
/// ����+=
/// </summary>
MyString& MyString:: operator+=(const MyString& str) {
	char* pre = new char[strlen(m_data) + 1];
	strcpy(pre, m_data);//�洢ԭ�ַ���
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
	strcpy(pre, m_data);//�洢ԭ�ַ���
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
/// ����==
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
/// ����[]
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
char& MyString::operator[](int n) {
	return m_data[n];
}
/// <summary>
/// ����<<
/// </summary>
//ȫ�ֺ���������������Ԫ������ʵ�֣�����<<���
ostream& operator<<(ostream& out, MyString& str) {
	out << str.get_c_str();
	return out;
}
/// <summary>
/// ���ƴ�pos��ʼn���ַ�
/// </summary>
/// <param name="pos"></param>
/// <param name="n"></param>
/// <returns></returns>
MyString MyString::substr(int pos, int n) const {
	//��֤pos�Ϸ���
	//��֤pos+n�Ƿ񳬹�����
	int len = n;
	if (pos < 0 || pos >= m_size) {
		//�׳�Խ���쳣
		throw exception("��Ч������λ�ã�");
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
/// ��posλ�ò���
/// </summary>
/*
MyString& MyString::insert(int pos, const char* c) {
	//��֤pos�Ϸ���
	if (pos < 0 || pos >= m_size) {
		//�׳�Խ���쳣
		throw exception("��Ч������λ�ã�");
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
	//��֤pos�Ϸ���
	if (pos < 0 || pos >= m_size) {
		//�׳�Խ���쳣
		throw exception("��Ч������λ�ã�");
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
/// ��posλ��ɾ��n���ַ�
/// </summary>
MyString& MyString:: erase(int pos, int n) {
	if (pos < 0 || pos >= m_size) {
		//�׳�Խ���쳣
		throw exception("��Ч������λ�ã�");
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
/// �ַ����Ƚ�
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
/// ��ȡĳλ�ַ�
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
char& MyString::at(int n) {
	if (n < 0 || n >= m_size) {
		throw exception("��Ч������λ�ã�");
	}
	return m_data[n];
}
/// <summary>
/// ��pos��Ѱ���ִ��������㷨
/// </summary>
/// <param name="str"></param>
/// <param name="pos"></param>
/// <returns></returns>
int MyString::find(const MyString& str, int pos) {
	return this->find(str.m_data, pos);
}
int MyString::find(const char* ch, int pos) {
	if (pos >= m_size) {
		throw exception("��Ч������λ�ã�");
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