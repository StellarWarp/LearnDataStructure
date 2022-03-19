#pragma once
#include<iostream>
#include <queue>
template<class T>
class LinkedList
{
	struct Node
	{
		T Data{};
		Node* next{};
		Node* prev{};
	};
	Node* C{};//始
	Node* E{};//末
	unsigned int len;//长度
	bool ringed = false;//环

	//内部插入方法//向后插入
	T* insert_after(const T& Data, Node* p_node)
	{
		Node* newnode = new Node;
		newnode->Data = Data;

		if (C)
		{
			//链表插入
			newnode->next = p_node->next;
			if (p_node->next)
				p_node->next->prev = newnode;
			else
				E = newnode;
			p_node->next = newnode;
			newnode->prev = p_node;
			len++;
		}
		else
		{
			//创建第一节点
			newnode->next = nullptr;
			newnode->prev = nullptr;
			C = E = newnode;
			len = 1;
		}
		return &newnode->Data;
	}
	//内部插入方法//向前插入
	T* insert_before(const T& Data, Node* p_node)
	{
		Node* newnode = new Node;
		newnode->Data = Data;

		if (C)
		{
			newnode->prev = p_node->prev;
			if (p_node != C)
				p_node->prev->next = newnode;
			else
				C = newnode;
			p_node->prev = newnode;
			newnode->next = p_node;
			len++;
		}
		else
		{
			//创建第一节点
			newnode->next = nullptr;
			newnode->prev = nullptr;
			C = E = newnode;
			len = 1;
		}
		return &newnode->Data;
	}
	//内部交换函数
	void swap(Node* a, Node* b)
	{
		if (b == E) E = a;
		if (b->next) b->next->prev = a;
		Node*& temp = a->next->prev;
		b->prev->next = a;
		temp = b;
		if (a == C) C = b;
		else a->prev->next = b;
		std::swap(a->next, b->next);
		std::swap(a->prev, b->prev);
		//std::swap(a, b);
	}
public:
	//迭代器
	class iterator : public std::iterator<std::bidirectional_iterator_tag, T>
	{
		bool start = true;
	public:
		Node* ptr{};
		iterator(Node* p = nullptr)
		{
			ptr = p;
		}
		//使用数据指针获取迭代器
		iterator(T* p)
		{
			ptr = (Node*)p;
		}

		T& operator*()
		{
			return ptr->Data;
		}
		bool operator ==(const iterator& iter)
		{
			return (ptr == iter.ptr);
		}
		bool operator !=(const iterator& iter)
		{
			if (!start || !ptr)return (ptr != iter.ptr);
			else { start = false; return true; }
		}
		iterator& operator++()
		{
			ptr = ptr->next;
			return *this;
		}
		iterator& operator++(int)
		{
			iterator temp = *this;
			ptr = ptr->next;
			return temp;
		}
		iterator& operator--()
		{
			ptr = ptr->prev;
			return *this;
		}
		iterator& operator--(int)
		{
			iterator temp = *this;
			ptr = ptr->prev;
			return *this;
		}
		iterator& operator+(int n)
		{
			for (int i = 0; i < n; i++)
				ptr = ptr->next;
			return *this;
		}
		iterator& operator-(int n)
		{
			for (int i = 0; i < n; i++)
				ptr = ptr->prev;
			return *this;
		}
	};

	iterator begin()
	{
		iterator Pointer{ C };
		return Pointer;
	}
	iterator end()
	{
		if (E) return iterator(E->next);
		else return iterator();
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

	LinkedList() {}
	LinkedList(std::initializer_list<T> dataArray)
	{
		for (auto& d : dataArray)
		{
			append(d);
		}
	}

	//向前插入//在末尾增加
	T* append(const T& Data, T* p = nullptr)
	{
		if (p)
		{
			return insert_before(Data, (Node*)p);
		}
		return insert_after(Data, E);
	}
	//用迭代器插入
	T* append(const T& Data, const iterator& iter)
	{
		if (iter.ptr)
		{
			return insert_before(Data, iter.ptr);
		}
		return insert_after(Data, E);
	}
	//向后插入
	T* insert(const T& Data, const iterator& iter)
	{
		return insert_after(Data, iter.ptr);
	}


	//使用迭代器删除
	iterator remove(const iterator& iter)
	{
		Node* node = iter.ptr;
		if (!node) return iter;//空操作
		if (node == C)
		{
			C = node->next;
		}
		if (node == E)
		{
			E = node->prev;
		}
		if (node->prev)
			node->prev->next = node->next;
		if (node->next)
			node->next->prev = node->prev;
		len--;

		if (!len) { C = E = nullptr; ringed = false; }
		auto temp = node->next;
		delete node;
		return iterator(temp);
	}
	//使用数据指针删除
	void remove(T* Data)
	{
		remove(iterator(Data));
	}
	void setEmpty()
	{
		while (C)
		{
			remove(C);
		}
	}
	~LinkedList()
	{
		while (C)
		{
			remove(C);
		}
	}

	void reverse()
	{
		Node* p = C;
		for (;;)
		{
			std::swap(p->next, p->prev);
			if (p == E)
			{
				std::swap(C, E);
				break;
			}
			p = p->prev;
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
		if (E)
		{
			ringed = true;
			E->next = C;
			C->prev = E;
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
		if (E->next == nullptr && C->prev == nullptr)
		{
			return false;
		}
		else if (E->next == nullptr || C->prev == nullptr)
		{
			std::cerr << "Ring Check: corrupted list" << std::endl;
		}
		else
		{
			return true;
		}
	}
	T& middle()
	{
		return (*this)[len / 2];
	}
	//奇偶调换
	void paritySwap()
	{
		iterator iter = this->begin();
		for (int i = 0, t = len / 2; i < t; i++)
		{
			swap(iter.ptr, iter.ptr->next);
			++iter;
		}
		if(ringed&& len%2)
		{
			iter.ptr->next = this->begin().ptr;
		}
	}


};
