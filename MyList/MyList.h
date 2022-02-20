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
	using _Base::m_head;//结点的指针表示一个双链表
	size_t len;//结点数量
public:
	MyList() :_list_node_base<_T>(),len(0) {};//调用父类默认构造函数
	//有参构造函数
	MyList(size_t _n, const _T& val = _T()) :_list_node_base<_T>(), len(0) {
		for (size_t i = 0; i < _n; i++) {
			insert(begin(), val);
		}
	}
	~MyList() {
		clear();
	}
	/// <summary>
	/// 清空容器
	/// </summary>
	void clear() {
		while (!empty()) {
			pop_back();
		}
	}
	/// <summary>
	/// 返回头结点的下一个
	/// </summary>
	/// <returns></returns>
	iterator begin() {
		return (list_node*)m_head->_m_next;//最后结果为list_node*类型，将其包装为迭代器类型，通过父类指针调用子类构造函数
	}
	/// <summary>
	/// 返回头节点
	/// </summary>
	/// <returns></returns>
	iterator end() {
		return (list_node*)m_head;
	}
	/// <summary>
	/// 获取list长度
	/// </summary>
	/// <returns></returns>
	size_t size() const {
		return len;
	}
	/// <summary>
	/// 判断list是否为空
	/// </summary>
	/// <returns></returns>
	bool empty() const {
		return len == 0;
	}
	/// <summary>
	/// 在pos位插入值为val的结点
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
	/// 删除pos位的结点
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	iterator erase(iterator pos) {
		if (!empty()) {
			list_node* node_next = (list_node*)pos._m_node->_m_next;
			pos._m_node->_m_pre->_m_next = pos._m_node->_m_next;
			pos._m_node->_m_next->_m_pre = pos._m_node->_m_pre;
			//清除结点
			--len;
			return (iterator)node_next;
		}
		else {
			throw "超出list长度！";
		}
	}
	/// <summary>
	/// 在begin位置插入结点
	/// </summary>
	/// <param name="val"></param>
	void push_front(const _T& val = _T()) {
		insert(begin(), val);
	}
	/// <summary>
	/// 在end位置插入结点
	/// </summary>
	/// <param name="val"></param>
	void push_back(const _T& val = _T()) {
		insert(end(), val);
	}
	/// <summary>
	/// 删除begin位置结点
	/// </summary>
	void pop_front() {
		erase(begin());
	}
	/// <summary>
	/// 删除end位置的上一个结点
	/// </summary>
	void pop_back() {
		erase(--end());
	}
};
#endif // !_MYLIST_
