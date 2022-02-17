#pragma once
#ifndef _MyVector_
#define _MyVector_
#include<iostream>
template<class _T>
class MyVector {
private:
	_T* _my_first;//��ʼλ��
	_T* _my_finish;//���һ������Ԫ�صĺ�һ��
	_T* _my_end;//��������ĺ�һ��

public:
	typedef _T* iterator;
	//���캯��//Ĭ�Ϲ���
	MyVector() :_my_first(nullptr), _my_finish(nullptr), _my_end(nullptr) {}
	/// <summary>
	/// �вι��캯��
	/// </summary>
	/// <param name="n">����</param>
	/// <param name="val">��ʼֵ</param>
	MyVector(size_t n, const _T& val = _T()) :_my_first(nullptr), _my_finish(nullptr), _my_end(nullptr) {
		//��������ռ�
		_my_first = new _T[n];
		_my_finish = _my_first;
		_my_end = _my_first + n;
		//��ֵ
		for (auto it = begin(); it != _my_end; ++it) {
			*_my_finish = val;
			++_my_finish;
		}
		_my_finish = _my_first;//�����ֵ��ָ���λ
	}
	/// <summary>
	/// ���ƹ��캯��
	/// </summary>
	/// <typeparam name="_T"></typeparam>
	/// <param name="v"></param>
	MyVector(const MyVector& v) {
		//�õ�v������
		size_t n = v.capacity();
		//��������ռ�
		_my_first = new _T[n];
		_my_finish = _my_first;
		_my_end = _my_first + n;
		//��ֵ
		//�����vΪconst����Ӧȡ����beginҲҪΪconst
		for (auto it = v.begin(); it != v.end(); ++it) {
			*_my_finish = *it;
			++_my_finish;
		}
	}
	/// <summary>
	/// ��������
	/// �Ƿ�Ӧ����ʽ����������ÿ�����������������
	/// </summary>
	/// <typeparam name="_T"></typeparam>
	~MyVector() {
		if (_my_first) {
			delete[] _my_first;
			_my_first = _my_finish = _my_end = nullptr;
		}
	}
	//���ص�����
	iterator begin() {
		return _my_first;
	}
	iterator end() {
		return _my_finish;
	}
	//���س���������
	iterator begin() const {
		return _my_first;
	}
	iterator end() const {
		return _my_finish;
	}
	/// <summary>
	/// ѹ��myvector
	/// </summary>
	/// <typeparam name="_T"></typeparam>
	/// <param name="val"></param>
	void push_back(const _T& val) {
		if (end() == _my_end) {//�ռ䲻��
			this->insert(end(), val);
		}
		else {//�пռ䣬ֱ�Ӵ�
			this->construction(end(), val);
			_my_finish++;
		}
	}
	/// <summary>
	/// �ڵ�����λ�ü���n����Ԫ��,Ĭ�ϸ���Ϊ1
	/// </summary>
	/// <param name="v"></param>
	void construction(iterator cur, const _T& val, int n = 1) {
		for (int i = 0; i < n; ++i) {
			*cur = val;
			cur++;
		}
	}
	/// <summary>
	/// ����myvector
	/// </summary>
	/// <typeparam name="_T"></typeparam>
	void pop_back() {
		this->erase(end());
	}
	//��ȡsize
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
	/// ��MyVector����n��val
	/// 1���ռ䲻��
	/// 2��ֱ�Ӳ���
	/// </summary>
	/// <typeparam name="_T"></typeparam>
	/// <param name="pos">����λ��</param>
	/// <param name="val">����ֵ</param>
	/// <param name="n">��������</param>
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
	/// �Ƴ�posλ��Ԫ��
	/// ��������ǰ��һλ
	/// finishǰ��һλ
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
	/// ��������ռ�
	/// 1.����			1���������¿ռ����  2���������¿ռ�ֻ����һ����
	/// 2.����
	/// </summary>
	/// <typeparam name="_T"></typeparam>
	/// <param name="n"></param>
	void resize(size_t n) {
		if (n < capacity()) {	//����
			_T* new_data = new _T[n];
			_T* new_fir = new_data;
			//��ֵ
			for (auto it = begin(); it != begin() + n && it != end(); ++it) {
				*(new_data++) = *it;
			}
			size_t old_size = size() < n ? size() : n;
			delete[] _my_first;//ɾ��ԭ������
			_my_first = new_fir;
			_my_finish = begin() + old_size;
			_my_end = begin() + n;

		}
		else if (n > capacity()) {	//����
			_T* new_data = new _T[n];
			_T* new_fir = new_data;
			for (auto it = begin(); it != end(); ++it) {
				*(new_data++) = *it;
			}
			size_t old_size = size();
			delete[] _my_first;//ɾ��ԭ������
			_my_first = new_fir;
			_my_finish = _my_first + old_size;
			_my_end = _my_first + n;
		}
	}
	/// <summary>
	/// ����[]
	/// </summary>
	/// <typeparam name="_T"></typeparam>
	/// <param name="n"></param>
	/// <returns></returns>
	_T& operator[](size_t n) {
		return *(_my_first + n);
	}
	/// <summary>
	/// ����=
	/// </summary>
	/// <typeparam name="_T"></typeparam>
	/// <param name="v"></param>
	/// <returns></returns>
	MyVector<_T>& operator=(const MyVector<_T>& v) {
		//�õ�v������
		size_t n = v.capacity();
		//��������ռ�
		_my_first = new _T[n];
		_my_finish = _my_first;
		_my_end = _my_first + n;
		//��ֵ
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
