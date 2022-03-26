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
	node* Top = nullptr;
	int len = 0;

public:
	//pushLStack
	bool push(T n)
	{
		if (Top)
		{
			Top = new node(n, Top);
		}
		else
		{
			Top = new node(n, nullptr);
		}
		len++;
		return true;
	}
	//popLStack
	bool pop()
	{
		if (Top)
		{
			node* D = Top;
			Top = Top->next;
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
		if (Top)
			return Top->data;
		else
		{
			cerr << "栈空" << endl;
			exit(1);
		}
	}

	//isEmptyLStack
	bool empty()
	{
		return !Top;
	}
	//LStackLength
	int size()
	{
		return len;
	}
	//clearLStack
	void clear()
	{
		while (Top)
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
		return iterator{ Top };
	}
	iterator end()
	{
		return iterator();
	}
	//打印
	friend ostream& operator <<(ostream& out, Stack stack)
	{
		node* ptr = stack.Top;
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
	node* Front = nullptr;
	node* Rear = nullptr;
	int len = 0;

public:
	//EnLQueue
	bool push(T n)
	{
		if (Rear)
		{
			Rear->next = new node(n, nullptr);
			Rear = Rear->next;
		}
		else
		{
			Front = Rear = new node(n, nullptr);
		}
		len++;
		return true;
	}
	//DeLQueue
	bool pop()
	{
		if (Front)
		{
			node* D = Front;
			Front = Front->next;
			if (!Front)
			{
				Rear = nullptr;
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
		if (Front)
		{
			return Front->data;
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
		if (Rear)
		{
			return Rear->data;
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
		return !Front;
	}
	//LengthLQueue
	int size()
	{
		return len;
	}
	//DeLQueue
	void clear()
	{
		while (Front)
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
		return iterator{ Front };
	}
	iterator end()
	{
		return iterator();
	}
	//打印
	friend ostream& operator <<(ostream& out, Queue queue)
	{
		node* ptr = queue.Front;
		while (ptr)
		{
			cout << ptr->data << "  ";
			ptr = ptr->next;
		}
		cout << endl;
	}
};