#pragma once
#ifndef _LIST_NODE_BASE_
#define _LIST_NODE_BASE_
/// <summary>
/// ָ����
/// </summary>
struct _list_node_pointer {
	_list_node_pointer* _m_next;//ָ����һ��
	_list_node_pointer* _m_pre;//ָ����һ��
	//_list_node_pointer():_m_next(nullptr), _m_pre(nullptr){}
};
/// <summary>
/// ������
/// struct�еı���Ĭ��public���̳�Ĭ��public
/// </summary>
template <typename _T>
struct _list_node_data : public _list_node_pointer {//���м̳�ָ����
	_T _m_data;
	//_list_node_data(const _T& val):_list_node_pointer(),_m_data(val){}
};
/// <summary>
/// ��װ���Ļ���
/// �ṩ�ս��ʹ�ֵ���Ĺ��캯��
/// �����������ٸý��
/// �����������ڴ�����ղ������ƣ�û���ṩ���ٽ�������ݵĽӿ�
/// �����ٽ����ڴ洦����
/// </summary>
/// <typeparam name="_T"></typeparam>
template <typename _T>
class _list_node_base {
public:
	_list_node_data<_T>* m_head;	//���
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
