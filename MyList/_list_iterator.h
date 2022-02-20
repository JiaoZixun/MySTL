#pragma once
#ifndef _LIST_ITERATOR_
#define _LIST_ITERATOR_
#include"_list_node_base.h"
/// <summary>
/// 迭代器的实现
/// 仅需包含一个指针域
/// 对指针进行操作
/// 重载一系列运算符号
/// </summary>
/// <typeparam name="_T"></typeparam>
template<typename _T>
class _list_iterator {
public:
	_list_node_pointer* _m_node;
	_list_iterator():_m_node(nullptr) {}
	_list_iterator(_list_node_pointer* _x) :_m_node(_x){}

	_list_iterator& operator++();//前++
	_list_iterator& operator++(int);//后++
	_list_iterator& operator--();//前--
	_list_iterator& operator--(int);//后--
	_T operator*()const;
	_list_node_data<_T>* operator->()const;
	bool operator!=(const _list_iterator& it) const;
	bool operator==(const _list_iterator& it) const;
};
template<typename _T>
_list_iterator<_T>& _list_iterator<_T>::operator++() {
	_m_node = _m_node->_m_next;
	return *this;
}
template<typename _T>
_list_iterator<_T>& _list_iterator<_T>::operator++(int) {
	_list_iterator old = *this;
	++(*this);
	return old;
}
template<typename _T>
_list_iterator<_T>& _list_iterator<_T>::operator--() {
	_m_node = _m_node->_m_pre;
	return *this;
}
template<typename _T>
_list_iterator<_T>& _list_iterator<_T>::operator--(int) {
	_list_iterator old = *this;
	--(*this);
	return old;
}
template<typename _T>
_T _list_iterator<_T>::operator*() const{
	return ((_list_node_data<_T>*)_m_node)->_m_data;
}
template<typename _T>
_list_node_data<_T>* _list_iterator<_T>::operator->() const {
	return ((_list_node_data<_T>*)_m_node);
}
template<typename _T>
bool _list_iterator<_T>::operator!=(const _list_iterator& it) const {
	return _m_node != it._m_node;
}
template<typename _T>
bool _list_iterator<_T>::operator==(const _list_iterator& it) const {
	return _m_node == it._m_node;
}
#endif // !_LIST_ITERATOR_
