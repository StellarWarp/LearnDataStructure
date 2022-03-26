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
	int size = 0;

public:
	void push(T n)
	{
		if (C)
		{
			C = new node(n, C);
		}
		else
		{
			C = new node(n, nullptr);
		}
		size++;
	}
	T pop()
	{
		if (C)
		{
			T n = C->data;
			node* D = C;
			C = C->next;
			delete D;
			return n;
			size--;
		}
		else
		{
			cout << "栈空" << endl;
			exit(1);
		}
	}
	T top()
	{
		return C->data;
	}

	bool empty()
	{
		return !C;
	}
	int size()
	{
		return size;
	}
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
	int size = 0;

public:
	void push(T n)
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
	}
	T pop()
	{
		if (C)
		{
			T n = C->data;//要返回的值
			node* D = C;
			C = C->next;
			if (!C)
			{
				E = nullptr;
			}
			delete D;
			return n;
		}
		else
		{
			cout << "列队空" << endl;
			exit(1);
		}
	}
	T front()
	{
		if (C)
		{
			return C->data;
		}
		else
		{
			cout << "列队空" << endl;
			exit(1);
		}
	}
	T back()
	{
		if (E)
		{
			return E->data;
		}
		else
		{
			cout << "列队空" << endl;
			exit(1);
		}
	}
	bool empty()
	{
		return !C;
	}
	int size()
	{
		return size;
	}
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