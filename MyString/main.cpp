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
	MyString str9 = str8.substr(0, 0);
	cout << "str9:" << str9 << endl;
	vector<MyString>ans = str8.split(".");
	for (auto it : ans)	cout << it << endl;
	return 0;
}