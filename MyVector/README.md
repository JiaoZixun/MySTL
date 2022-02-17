# Vector类实现

第一次自己实现模板类，一开始将定义和实现文件分开写，结果vs不能编译。后来发现模板类的实现需要和定义写在一起，因为模板中的T是在编译中才确定的，因此会找不到.cpp的实现文件。

STL中vector类模板的实现还有一个参数是内存分配器，默认是调用系统自带的分配器对内存进行分配，在本次实现中仅采用new关键字对内存进行分配。模板的类型为_T，将 _T*封装为迭代器，用于遍历 _T类型的变量。类中包装3个迭代器作为存取的指示，实现了基本的构造函数、析构函数以及常用函数。

由于有些参数传入需要使用const关键字，因此这些参数在调用其他函数时，也必须调用const关键字修饰的函数。

类中没有实现例如：

```c++
vector vec(10);
vec[0] = 0;
```

这种赋值形式，只能使用push_back()在vector尾部添加，或insert(it,val)在it位加入val，但每次仅能插入一个。

最后给出简单测试代码，对于一些细节的把控可能还没完善。

## 头文件.h

```c++
#pragma once
#ifndef _MyVector_
#define _MyVector_
#include<iostream>
template<class _T>
class MyVector {
private:
	_T* _my_first;//起始位置
	_T* _my_finish;//最后一个存入元素的后一个
	_T* _my_end;//最大容量的后一个

public:
	typedef _T* iterator;//迭代器
	//默认构造
	MyVector() :_my_first(nullptr), _my_finish(nullptr), _my_end(nullptr) {}
	/// <summary>
	/// 有参构造函数
	/// </summary>
	/// <param name="n">长度</param>
	/// <param name="val">初始值</param>
	MyVector(size_t n, const _T& val = _T()) :_my_first(nullptr), _my_finish(nullptr), _my_end(nullptr) {
		//重新申请空间
		_my_first = new _T[n];
		_my_finish = _my_first;
		_my_end = _my_first + n;
		//赋值
		for (auto it = begin(); it != _my_end; ++it) {
			*_my_finish = val;
			++_my_finish;
		}
		_my_finish = _my_first;//赋完初值后，指针归位
	}
	/// <summary>
	/// 复制构造函数
	/// </summary>
	/// <typeparam name="_T"></typeparam>
	/// <param name="v"></param>
	MyVector(const MyVector& v) {
		//得到v的容量
		size_t n = v.capacity();
		//重新申请空间
		_my_first = new _T[n];
		_my_finish = _my_first;
		_my_end = _my_first + n;
		//赋值
		//传入的v为const，对应取出的begin也要为const
		for (auto it = v.begin(); it != v.end(); ++it) {
			*_my_finish = *it;
			++_my_finish;
		}
	}
	/// <summary>
	/// 析构函数
	/// 是否应该显式调用数组中每个对象的析构函数？
	/// </summary>
	/// <typeparam name="_T"></typeparam>
	~MyVector() {
		if (_my_first) {
			delete[] _my_first;
			_my_first = _my_finish = _my_end = nullptr;
		}
	}
	//返回迭代器
	iterator begin() {
		return _my_first;
	}
	iterator end() {
		return _my_finish;
	}
	//返回常量迭代器
	iterator begin() const {
		return _my_first;
	}
	iterator end() const {
		return _my_finish;
	}
	/// <summary>
	/// 压入myvector
	/// </summary>
	/// <typeparam name="_T"></typeparam>
	/// <param name="val"></param>
	void push_back(const _T& val) {
		if (end() == _my_end) {//空间不足
			this->insert(end(), val);
		}
		else {//有空间，直接存
			this->construction(end(), val);
			_my_finish++;
		}
	}
	/// <summary>
	/// 在迭代器位置加入n个该元素,默认个数为1
	/// </summary>
	/// <param name="v"></param>
	void construction(iterator cur, const _T& val, int n = 1) {
		for (int i = 0; i < n; ++i) {
			*cur = val;
			cur++;
		}
	}
	/// <summary>
	/// 弹出myvector
	/// </summary>
	/// <typeparam name="_T"></typeparam>
	void pop_back() {
		this->erase(end());
	}
	//获取size
	size_t size() {
		return size_t(end() - begin());
	}
	size_t capacity() {
		return _my_first == nullptr ? 0 : _my_end - _my_first;
	}
	size_t capacity() const {
		return _my_first == nullptr ? 0 : _my_end - _my_first;
	}
	/// <summary>
	/// 在MyVector插入val
	/// 1、空间不足
	/// 2、直接插入
	/// </summary>
	/// <typeparam name="_T"></typeparam>
	/// <param name="pos">插入位置</param>
	/// <param name="val">插入值</param>
	void insert(iterator pos, const _T& val) {
		size_t posindex = pos - _my_first;
		if (_my_finish == _my_end){//空间不足
			size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
			resize(newcapacity);//重新申请大小
			pos = _my_first + posindex;
		}
        //后移
		iterator end = _my_finish;
		while (end > pos){
			*end = *(end - 1);
			--end;
		}
		*pos = val;
		++_my_finish;
	}
	/// <summary>
	/// 移除pos位的元素
	/// 后面整体前移一位
	/// finish前移一位
	/// </summary>
	/// <typeparam name="_T"></typeparam>
	/// <param name="pos"></param>
	/// <returns></returns>
	iterator erase(iterator pos) {
		iterator begin = pos;
		for (iterator it = pos; it != end(); ++it) {
			*it = *(it + 1);
		}
		--_my_finish;
		return begin;
	}
	/// <summary>
	/// 重新申请空间
	/// 1.缩容			1）对象在新空间存满  2）对象在新空间只存了一部分
	/// 2.扩容
	/// </summary>
	/// <typeparam name="_T"></typeparam>
	/// <param name="n"></param>
	void resize(size_t n) {
		if (n < capacity()) {	//缩容
			_T* new_data = new _T[n];
			_T* new_fir = new_data;
			//赋值
			for (auto it = begin(); it != begin() + n && it != end(); ++it) {
				*(new_data++) = *it;
			}
			size_t old_size = size() < n ? size() : n;
			delete[] _my_first;//删除原先数据
			_my_first = new_fir;
			_my_finish = begin() + old_size;
			_my_end = begin() + n;

		}
		else if (n > capacity()) {	//扩容
			_T* new_data = new _T[n];
			_T* new_fir = new_data;
			for (auto it = begin(); it != end(); ++it) {
				*(new_data++) = *it;
			}
			size_t old_size = size();
			delete[] _my_first;//删除原先数据
			_my_first = new_fir;
			_my_finish = _my_first + old_size;
			_my_end = _my_first + n;
		}
	}
	/// <summary>
	/// 重载[]
	/// </summary>
	/// <typeparam name="_T"></typeparam>
	/// <param name="n"></param>
	/// <returns></returns>
	_T& operator[](size_t n) {
		return *(_my_first + n);
	}
	/// <summary>
	/// 重载=
	/// </summary>
	/// <typeparam name="_T"></typeparam>
	/// <param name="v"></param>
	/// <returns></returns>
	MyVector<_T>& operator=(const MyVector<_T>& v) {
		//得到v的容量
		size_t n = v.capacity();
		//重新申请空间
		_my_first = new _T[n];
		_my_finish = _my_first;
		_my_end = _my_first + n;
		//赋值
		for (auto it = v.begin(); it != v.end(); ++it) {
			*_my_finish = *it;
			++_my_finish;
		}
		return this;
	}
	bool empty() const {
		return end() == begin();
	}
};
#endif // !_MyVector_

```



## 测试代码

没有实现对于越界等问题的异常处理

```c++
#include"MyVector.h"
#include<iostream>
#include<algorithm>
int main() {
	//测试默认构造函数
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
	//测试有参构造
	MyVector<int> vec2(5);
	for (int i = 0; i < 5; i++) {
		vec2.insert(vec2.begin(), i);
	}
	for (auto it = vec2.begin(); it != vec2.end(); ++it) {
		std::cout << *it << std::endl;
	}
	//测试赋值构造
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
	//测试resize
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
		std::cout << "vec1为空" << std::endl;
	}
	else {
		std::cout << "vec1不空" << std::endl;
	}
	//测试能否适配算法库
	std::sort(vec4.begin(), vec4.end());
	std::cout << "vec4:" << std::endl;
	for (auto it = vec4.begin(); it != vec4.end(); ++it) {
		std::cout << *it << std::endl;
	}
	return 0;
}
```

