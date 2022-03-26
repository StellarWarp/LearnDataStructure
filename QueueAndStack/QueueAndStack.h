#pragma once
#include<iostream>
using namespace std;
template<class T>
class Stack
{
	struct node
	{
		T data;
		node* next;

		node(T n, node* p)
		{
			data = n;
			next = p;
		}
	};
	node* C = nullptr;
	int len = 0;

public:
	//pushLStack
	bool push(T n)
	{
		if (C)
		{
			C = new node(n, C);
		}
		else
		{
			C = new node(n, nullptr);
		}
		len++;
		return true;
	}
	//popLStack
	bool pop()
	{
		if (C)
		{
			node* D = C;
			C = C->next;
			delete D;
			len--;
			return true;
		}
		else
		{
			return false;
		}
	}
	//getTopLStack
	T top()
	{
		if (C)
			return C->data;
		else
		{
			cerr << "栈空" << endl;
			exit(1);
		}
	}

	//isEmptyLStack
	bool empty()
	{
		return !C;
	}
	//LStackLength
	int size()
	{
		return len;
	}
	//clearLStack
	void clear()
	{
		while (C)
		{
			this->pop();
		}
	}
	~Stack()
	{
		clear();
	}

	//迭代器//用于遍历
	class iterator : public std::iterator<std::forward_iterator_tag, T>
	{
	public:
		node* ptr{};
		iterator(node* p = nullptr)
		{
			ptr = p;
		}
		T& operator*()
		{
			return ptr->data;
		}
		bool operator !=(const iterator& iter)
		{
			return ptr != iter.ptr;
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
	};
	iterator begin()
	{
		return iterator{ C };
	}
	iterator end()
	{
		return iterator();
	}
	//打印
	friend ostream& operator <<(ostream& out, Stack stack)
	{
		node* ptr = stack.C;
		while (ptr)
		{
			cout << ptr->data << "  ";
			ptr = ptr->next;
		}
		cout << endl;
	}
};
template<class T>
class Queue
{
	struct node
	{
		T data;
		node* next;

		node(T n, node* p)
		{
			data = n;
			next = p;
		}
	};
	node* C = nullptr;
	node* E = nullptr;
	int len = 0;

public:
	//EnLQueue
	bool push(T n)
	{
		if (E)
		{
			E->next = new node(n, nullptr);
			E = E->next;
		}
		else
		{
			C = E = new node(n, nullptr);
		}
		len++;
		return true;
	}
	//DeLQueue
	bool pop()
	{
		if (C)
		{
			node* D = C;
			C = C->next;
			if (!C)
			{
				E = nullptr;
			}
			delete D;
			len--;
			return true;
		}
		else
		{
			return false;
		}
	}
	//GetHeadLQueue
	T front()
	{
		if (C)
		{
			return C->data;
		}
		else
		{
			cerr << "列队空" << endl;
			exit(1);
		}
	}
	//
	T back()
	{
		if (E)
		{
			return E->data;
		}
		else
		{
			cerr << "列队空" << endl;
			exit(1);
		}
	}

	//IsEmptyLQueue
	bool empty()
	{
		return !C;
	}
	//LengthLQueue
	int size()
	{
		return len;
	}
	//DeLQueue
	void clear()
	{
		while (C)
		{
			this->pop();
		}
	}
	~Queue()
	{
		clear();
	}

	//迭代器//用于遍历
	class iterator : public std::iterator<std::forward_iterator_tag, T>
	{
	public:
		node* ptr{};
		iterator(node* p = nullptr)
		{
			ptr = p;
		}
		T& operator*()
		{
			return ptr->data;
		}
		bool operator !=(const iterator& iter)
		{
			return ptr != iter.ptr;
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
	};
	iterator begin()
	{
		return iterator{ C };
	}
	iterator end()
	{
		return iterator();
	}
	//打印
	friend ostream& operator <<(ostream& out, Queue queue)
	{
		node* ptr = queue.C;
		while (ptr)
		{
			cout << ptr->data << "  ";
			ptr = ptr->next;
		}
		cout << endl;
	}
};