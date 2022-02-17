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
	typedef _T* iterator;
	//构造函数//默认构造
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
	/// 在MyVector插入n个val
	/// 1、空间不足
	/// 2、直接插入
	/// </summary>
	/// <typeparam name="_T"></typeparam>
	/// <param name="pos">插入位置</param>
	/// <param name="val">插入值</param>
	/// <param name="n">插入数量</param>
	void insert(iterator pos, const _T& val) {
		size_t posindex = pos - _my_first;
		if (_my_finish == _my_end)
		{
			size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
			resize(newcapacity);
			pos = _my_first + posindex;
		}

		iterator end = _my_finish;
		while (end > pos)
		{
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
