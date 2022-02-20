# MyList

平时很少使用STL中的List容器，因此在实现的时候走了很多弯路，也借鉴了不少博主的实现方式，在结合自己的理解进行了实现。这个容器使用了多个类结合的方式，主要有三大部分，结点基类，迭代器，MyList类，最终MyList类提供对外接口，实现容器的构造，析构和一些基本成员函数。

![MyList类](https://img-blog.csdnimg.cn/22cb12e5c7fa47da97e4c8c4d79ebc99.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAamlhb29vb29v,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)

## 一、结点的基类

​	考虑到头节点不需要生成数据域，将结点拆分为指针域和数据域两个结构体表示，结构体内的变量默认为public，继承也是默认public。实现_list_base作为结点的基类，由该类实现对结点的操作。

```cpp
/// <summary>
/// 指针域
/// </summary>
struct _list_node_pointer {
	_list_node_pointer* _m_next;//指向下一个
	_list_node_pointer* _m_pre;//指向上一个
};
/// <summary>
/// 数据域
/// struct中的变量默认public，继承默认public
/// </summary>
template <typename _T>
struct _list_node_data : public _list_node_pointer {//公有继承指针域
	_T _m_data;
};
```

```cpp
template <typename _T>
class _list_node_base {
public:
	_list_node_data<_T>* m_head;
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
```



## 二、迭代器

迭代器是对指针的操作，为了实现对容器内的访问，在迭代器的实现中，只用指针域作为成员变量即可。实现了构造函数和多种符号的重载。存入基类指针，当需要访问数据域时，基类指针转为子类指针进而访问数据域。

```cpp
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
```



## 三、MyList类

STL中的List是双链表，有一个头节点不存任何数据，仅作为标识。begin()是返回头节点的下一个，end()是返回头节点。发生删除时需要考虑当前List是否为空，并且不能删掉头节点。

删除很好理解，跳过pos结点，前后结点相连即可。对于插入则需要小心，先连好一边再连最后一个，不然中间会断开找不到前驱结点或后继结点，按图中步骤即可在pos前插入val结点。

![双链表插入](https://img-blog.csdnimg.cn/3b7870fd19d04c82a3c79f74de8bb3d4.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAamlhb29vb29v,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)

在MyList类保护继承结点基类（ _list_node_base），类中实现了构造函数、析构函数和基本的成员函数，为了方便得到容器的size，将容器长度设为变量，初始化为0。头节点引用基类成员m_head，生成新结点时调用基类构造函数，并由数据域类型（ _list_node_data）的指针指向。

```cpp
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
```



## 四、测试

对于MyList中实现的函数进行了简单测试

```cpp
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
```





