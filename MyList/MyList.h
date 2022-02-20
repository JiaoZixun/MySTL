#pragma once
#ifndef _MYLIST_
#define _MYLIST_
#include"_list_node_base.h"
#include"_list_iterator.h"
#include<exception>
#include<iostream>
template<typename _T>
class MyList :protected _list_node_base<_T> {
public:
	typedef _list_node_data<_T> list_node;
	typedef _list_iterator<_T> iterator;
	typedef _list_node_base<_T> _Base;
protected:
	using _Base::m_head;//����ָ���ʾһ��˫����
	size_t len;//�������
public:
	MyList() :_list_node_base<_T>(),len(0) {};//���ø���Ĭ�Ϲ��캯��
	//�вι��캯��
	MyList(size_t _n, const _T& val = _T()) :_list_node_base<_T>(), len(0) {
		for (size_t i = 0; i < _n; i++) {
			insert(begin(), val);
		}
	}
	~MyList() {
		clear();
	}
	/// <summary>
	/// �������
	/// </summary>
	void clear() {
		while (!empty()) {
			pop_back();
		}
	}
	/// <summary>
	/// ����ͷ������һ��
	/// </summary>
	/// <returns></returns>
	iterator begin() {
		return (list_node*)m_head->_m_next;//�����Ϊlist_node*���ͣ������װΪ���������ͣ�ͨ������ָ��������๹�캯��
	}
	/// <summary>
	/// ����ͷ�ڵ�
	/// </summary>
	/// <returns></returns>
	iterator end() {
		return (list_node*)m_head;
	}
	/// <summary>
	/// ��ȡlist����
	/// </summary>
	/// <returns></returns>
	size_t size() const {
		return len;
	}
	/// <summary>
	/// �ж�list�Ƿ�Ϊ��
	/// </summary>
	/// <returns></returns>
	bool empty() const {
		return len == 0;
	}
	/// <summary>
	/// ��posλ����ֵΪval�Ľ��
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="val"></param>
	/// <returns></returns>
	iterator insert(iterator pos, const _T& val) {
		_Base* b = new _Base(val);
		list_node* _tmp = b->m_head;
		_tmp->_m_next = pos._m_node;
		pos._m_node->_m_pre->_m_next = _tmp;
		_tmp->_m_pre = pos._m_node->_m_pre;
		pos._m_node->_m_pre = _tmp;
		++len;
		return _tmp;
	}
	/// <summary>
	/// ɾ��posλ�Ľ��
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	iterator erase(iterator pos) {
		if (!empty()) {
			list_node* node_next = (list_node*)pos._m_node->_m_next;
			pos._m_node->_m_pre->_m_next = pos._m_node->_m_next;
			pos._m_node->_m_next->_m_pre = pos._m_node->_m_pre;
			//������
			--len;
			return (iterator)node_next;
		}
		else {
			throw "����list���ȣ�";
		}
	}
	/// <summary>
	/// ��beginλ�ò�����
	/// </summary>
	/// <param name="val"></param>
	void push_front(const _T& val = _T()) {
		insert(begin(), val);
	}
	/// <summary>
	/// ��endλ�ò�����
	/// </summary>
	/// <param name="val"></param>
	void push_back(const _T& val = _T()) {
		insert(end(), val);
	}
	/// <summary>
	/// ɾ��beginλ�ý��
	/// </summary>
	void pop_front() {
		erase(begin());
	}
	/// <summary>
	/// ɾ��endλ�õ���һ�����
	/// </summary>
	void pop_back() {
		erase(--end());
	}
};
#endif // !_MYLIST_
