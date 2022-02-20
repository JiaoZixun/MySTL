#pragma once
#ifndef _LIST_NODE_BASE_
#define _LIST_NODE_BASE_
/// <summary>
/// 指针域
/// </summary>
struct _list_node_pointer {
	_list_node_pointer* _m_next;//指向下一个
	_list_node_pointer* _m_pre;//指向上一个
	//_list_node_pointer():_m_next(nullptr), _m_pre(nullptr){}
};
/// <summary>
/// 数据域
/// struct中的变量默认public，继承默认public
/// </summary>
template <typename _T>
struct _list_node_data : public _list_node_pointer {//公有继承指针域
	_T _m_data;
	//_list_node_data(const _T& val):_list_node_pointer(),_m_data(val){}
};
/// <summary>
/// 包装结点的基类
/// 提供空结点和带值结点的构造函数
/// 析构函数销毁该结点
/// 析构函数对内存的掌握不够完善，没有提供销毁结点内数据的接口
/// 对销毁结点的内存处理不好
/// </summary>
/// <typeparam name="_T"></typeparam>
template <typename _T>
class _list_node_base {
public:
	_list_node_data<_T>* m_head;	//结点
	_list_node_base() {
		m_head = new _list_node_data<_T>();
		m_head->_m_next = m_head;
		m_head->_m_pre = m_head;
	}
	_list_node_base(const _T& val) {
		m_head = new _list_node_data<_T>();
		m_head->_m_next = nullptr;
		m_head->_m_pre = nullptr;
		m_head->_m_data = val;
	}
	~_list_node_base() {
		m_head->_m_next = nullptr;
		m_head->_m_pre = nullptr;
		delete m_head;
	}
};
#endif // !_LIST_NODE_BASE_
