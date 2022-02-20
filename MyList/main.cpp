#include"MyList.h"
#include<iostream>
int main() {
	MyList<int> list1;
	list1.insert(list1.begin(), 1);
	list1.insert(list1.begin(), 2);
	list1.push_back(3);
	list1.push_back(4);
	list1.push_front(5);
	list1.push_front(6);
	std::cout << "List1：" << std::endl;
	std::cout << "List1.size：" << list1.size() << std::endl;
	for (auto it = list1.begin(); it != list1.end(); ++it) {
		std::cout << *it << std::endl;
	}
	list1.erase(list1.begin());
	list1.pop_back();
	list1.pop_front();
	std::cout << "删除后List1.size：" << list1.size() << std::endl;
	std::cout << "删除后List1：" << std::endl;
	for (auto it = list1.begin(); it != list1.end(); ++it) {
		std::cout << *it << std::endl;
	}
	MyList<int> list2(10, 2);
	std::cout << "List2.size：" << list2.size() << std::endl;
	std::cout << "List2：" << std::endl;
	for (auto it = list2.begin(); it != list2.end(); ++it) {
		std::cout << *it << std::endl;
	}
	if (list2.empty()) {
		std::cout << "List2为空" << std::endl;
	}
	else {
		std::cout << "List2不为空" << std::endl;
	}
	return 0;
	
}