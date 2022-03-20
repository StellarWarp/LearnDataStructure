#pragma once
#include <iostream>
#include <queue>

template<class T>
class OneWayLinkedList
{
	struct Node
	{
		T Data{};
		Node* next{};
	};
	int pointerOffset = offsetof(Node, Node::next);
	Node* C{};//始
	Node* E{};//末

	unsigned int len;//长度
	bool ringed = false;//环

	//内部插入方法//向后插入
	T* insert_inlist(const T& Data, Node*& node)
	{
		Node* newnode = new Node;
		newnode->Data = Data;
		if (C)
		{
			//链表插入
			if (node)
			{
				newnode->next = node;
				node = newnode;
				if (&node == &E->next) E = newnode;
			}
			else
			{
				newnode->next = C;
				C = newnode;
			}
			len++;
		}
		else
		{
			//创建第一节点
			newnode->next = nullptr;
			C = E = newnode;
			len = 1;
		}
		return &newnode->Data;
	}
	T* insert(const T& Data, Node* p_node)
	{
		Node* newnode = new Node;
		newnode->Data = Data;
		if (C)
		{
			//链表插入
			if (p_node)
			{
				newnode->next = p_node->next;
				p_node->next = newnode;
				if (p_node == E) E = newnode;
			}
			else
			{
				newnode->next = C;
				C = newnode;
			}
			len++;
		}
		else
		{
			//创建第一节点
			newnode->next = nullptr;
			C = E = newnode;
			len = 1;
		}
		return &newnode->Data;
	}
	//内部交换函数
	void swap(Node* a_prev, Node* b_prev)
	{
		if (b_prev->next == E)
		{
			if (a_prev == nullptr) E = C;
			else
				E = a_prev->next;
		}
		if (a_prev == nullptr)
		{
			std::swap(C, b_prev->next);
			C = b_prev->next;
		}
		else
			std::swap(a_prev->next, b_prev->next);

		std::swap(a_prev->next->next, b_prev->next->next);

	}
	void swap_inlist(Node*& a, Node*& b)
	{
		if (b == E)E = a;
		std::swap(a, b);
		std::swap(a->next, b->next);
	}

public:
	//迭代器
	class iterator : public std::iterator<std::forward_iterator_tag, T>
	{
		bool start = true;
		Node** _ptr{};
	public:

		iterator(Node** _ptr_)
		{
			_ptr = _ptr_;
		}
		//使用前一节点获得迭代器
		iterator(Node* ptr_prev)
		{
			if (ptr_prev)
				_ptr = &ptr_prev->next;
			else _ptr = nullptr;
		}
		//使用数据指针获取迭代器
		iterator(T* p_prev) :iterator((Node*)p_prev) {}

		Node*& ptr()
		{
			return *_ptr;
		}
		Node* prev_ptr(int pointerOffset)
		{
			return (Node*)((char*)_ptr - pointerOffset);
		}
		operator Node*& ()
		{
			return *_ptr;
		}
		bool IsNull()
		{
			if (_ptr)return *_ptr;
			else return false;
		}
		bool IsPreNode(Node* p_prev)
		{
			if (&p_prev->next == _ptr) return true;
			else return false;
		}

		T& operator*()
		{
			return (*_ptr)->Data;
		}
		bool operator ==(const iterator& iter)
		{
			return (_ptr == iter._ptr);
		}
		bool operator !=(const iterator& iter)
		{
			if (!start || !_ptr || !ptr())return (_ptr != iter._ptr);
			else { start = false; return true; }
		}
		iterator& operator++()
		{
			_ptr = &(*_ptr)->next;
			return *this;
		}
		iterator operator++(int)
		{
			iterator temp = *this;
			_ptr = &(*_ptr)->next;
			return temp;
		}
		iterator& operator+(int n)
		{
			for (int i = 0; i < n; i++)
			{
				_ptr = &(*_ptr)->next;
			}
			return *this;
		}
	};

	iterator begin()
	{
		if (ringed)return iterator(E);
		else return iterator(&C);
	}
	iterator end()
	{
		if (ringed) return iterator(E);
		if (len)return iterator(E);
		else return iterator(&C);
	}
	T& operator[](int i)
	{
		Node* p = C;
		for (int j = 0; j < i; j++)
		{
			p = p->next;
		}
		return p->Data;
	}

	OneWayLinkedList() {}
	OneWayLinkedList(std::initializer_list<T> dataArray)
	{
		for (auto& d : dataArray)
		{
			append(d);
		}
	}


	//插入或在末尾增加//向后插入
	T* insert(const T& Data, T* p = nullptr)
	{
		return insert(Data, (Node*)p);
	}
	T* insert(const T& Data, iterator& iter)
	{
		return insert(Data, iter.ptr());
	}
	//用迭代器插入//向前插入
	T* append(const T& Data, iterator& iter)
	{
		return insert_inlist(Data, iter.ptr());
	}
	//末增
	T* append(const T& Data)
	{
		return insert(Data, E);
	}


	//使用迭代器删除
	void remove(iterator& iter)
	{
		//空操作
		if (!iter.IsNull()) return;
		//删除首节点
		if (iter.ptr() == C && ringed && iter != begin())
		{
			iter = begin();
			std::cout << "can no delete headNode with headptr in ring\n auto transfer to ring begin\n";
		}

		Node* temp = iter.ptr()->next;
		if (iter.ptr() == E) E = iter.prev_ptr(pointerOffset);
		delete iter.ptr();
		iter.ptr() = temp;
		len--;
		if (!len) { C = E = nullptr; ringed = false; }
	}
	//使用数据指针删除//删除下一节点
	void remove(T* Data_prev)
	{
		iterator iter(Data_prev);
		remove(iter);
	}
	void setEmpty()
	{
		while (C)
		{
			iterator iter = begin();
			remove(iter);
		}
	}
	~OneWayLinkedList()
	{
		setEmpty();
	}


	void reverse()
	{
		if (C)
		{
			Node* p = C;
			Node* np = C;
			if (C) np = p->next;
			p->next = nullptr;
			while (np)
			{
				Node* temp = np->next;
				np->next = p;
				p = np;
				np = temp;
			}
			E = C;
			C = p;
		}
	}
	int size()
	{
		return len;
	}


	//AdditionalFunction
	std::queue<T*> search(const T& Data)
	{
		std::queue<T*> searchList;
		for (auto& E : *this)
		{
			if (E == Data)
			{
				searchList.push(&E);
			}
		}
		return searchList;
	}
	//环形链表操作
	bool setRing()
	{
		if (C)
		{
			ringed = true;
			E->next = C;
			return true;
		}
		else return false;
	}
	bool isRing()
	{
		return ringed;
	}
	bool isRing_ForceCheck()
	{
		iterator iter = this->begin();
		if (!C) return false;
		iter++;
		for (;; iter++)
		{
			if (iter.ptr() == C)return true;
			if (iter.ptr() == nullptr)return false;
		}
	}

	T& middle()
	{
		return (*this)[len / 2];
	}
	//奇偶调换
	void paritySwap()
	{
		Node** p = &C;
		for (int i = 0, t = len / 2; i < t; i++)
		{
			swap_inlist(*p, (*p)->next);

			p = &(*p)->next->next;
		}
		if (ringed)
		{
			if (len % 2)(*p)->next = C;
			else *p = C;
		}
	}

};
