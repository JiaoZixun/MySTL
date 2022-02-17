#include"MyVector.h"
#include<iostream>
#include<algorithm>
int main() {
	//����Ĭ�Ϲ��캯��
	MyVector<int> vec1;
	vec1.push_back(0);
	vec1.push_back(1);
	vec1.push_back(2);
	vec1.push_back(3);
	vec1.push_back(4);
	vec1.push_back(5);
	std::cout << "vec1:" << std::endl;
	for (auto it = vec1.begin(); it != vec1.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "vec2:" << std::endl;
	//�����вι���
	MyVector<int> vec2(5);
	for (int i = 0; i < 5; i++) {
		vec2.insert(vec2.begin(), i);
	}
	for (auto it = vec2.begin(); it != vec2.end(); ++it) {
		std::cout << *it << std::endl;
	}
	//���Ը�ֵ����
	MyVector<int>vec3(vec2);
	std::cout << "vec3:" << std::endl;
	for (auto it = vec3.begin(); it != vec3.end(); ++it) {
		std::cout << *it << std::endl;
	}
	MyVector<int> vec4 = vec3;
	vec4.pop_back();
	vec4.pop_back();
	vec4.erase(vec4.begin() + 1);
	std::cout << "vec4:" << std::endl;
	for (auto it = vec4.begin(); it != vec4.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "vec4.size():" << vec4.size() << std::endl;
	//����resize
	vec1.resize(3);
	std::cout << "vec1:" << std::endl;
	for (auto it = vec1.begin(); it != vec1.end(); ++it) {
		std::cout << *it << std::endl;
	}
	vec4.resize(10);
	for (int i = 2; i < 10; i++) {
		vec4.push_back(i);
	}
	std::cout << "vec4.size():" << vec4.size() << std::endl;
	vec4.insert(vec4.begin() + 5, 10);
	std::cout << "vec4.size():" << vec4.size() << std::endl;
	std::cout << "vec4:" << std::endl;
	for (auto it = vec4.begin(); it != vec4.end(); ++it) {
		std::cout << *it << std::endl;
	}
	if (vec1.empty()) {
		std::cout << "vec1Ϊ��" << std::endl;
	}
	else {
		std::cout << "vec1����" << std::endl;
	}
	//�����ܷ������㷨��

	std::sort(vec4.begin(), vec4.end());
	std::cout << "vec4:" << std::endl;
	for (auto it = vec4.begin(); it != vec4.end(); ++it) {
		std::cout << *it << std::endl;
	}
	

	return 0;
}