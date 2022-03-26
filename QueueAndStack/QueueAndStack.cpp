#include <iostream>
#include <string>
#include<vector>
#include"QueueAndStack.h"
#include <fstream>
using namespace std;


std::string help;//帮助文本
void init_help()
{
	ifstream infile("help.txt");
	if (infile.is_open())
	{
		string buffer;
		while (getline(infile,buffer))
		{
			help += buffer; help += '\n';
		}
	}
	else
	{
		cout << "Fail to open help.txt" << endl;
	}
}
vector<std::string>  InputCommands()
{
	vector<std::string> commands;
	for (;;)
	{
		std::string temp;
		std::cin >> temp;
		commands.push_back(temp);
		if (getchar() == '\n') return commands;
	}
}
template<class T>
bool Push(T& container, vector<string>& commands)
{
	if (commands[0] == "push")
	{
		if (commands.size() == 2)
		{
			container.push(commands[1]);
			return true;
		}
	}
}
template<class T>
bool Pop(T& container, vector<string>& commands)
{
	if (commands[0] == "pop" && commands.size() == 1)
	{
		if (!container.pop())
		{
			cout << "Fail : empty" << endl;
		}
		return true;
	}
}
template<class T>
bool Top(T& container, vector<string>& commands)
{
	if (commands[0] == "top" && commands.size() == 1)
	{
		if (!container.empty())
		{
			cout << container.top() << endl;
		}
		else
		{
			cout << "Fail : empty" << endl;
		}
		return true;
	}
}
template<class T>
bool Front(T& container, vector<string>& commands)
{
	if (commands[0] == "front" && commands.size() == 1)
	{
		if (!container.empty())
		{
			cout << container.front() << endl;
		}
		else
		{
			cout << "Fail : empty" << endl;
		}
		return true;
	}
}
template<class T>
bool Empty(T& container, vector<string>& commands)
{
	if (commands[0] == "empty" && commands.size() == 1)
	{
		if (!container.empty())
		{
			cout << "False" << endl;
		}
		else
		{
			cout << "True" << endl;
		}
		return true;
	}
}
template<class T>
bool Size(T& container, vector<string>& commands)
{
	if (commands[0] == "size" && commands.size() == 1)
	{
		cout << container.size() << endl;
		return true;
	}
}
template<class T>
bool Clear(T& container, vector<string>& commands)
{
	if (commands[0] == "clear" && commands.size() == 1)
	{
		container.clear();
		return true;
	}
}
template<class T, class IT>
void PrintContainer(T& container, IT& iter)
{
	int width = 1;
	for (auto& E : container)
	{
		std::string lentest;
		lentest = E;
		if (strlen(lentest.c_str()) + 1 > width) width = strlen(lentest.c_str()) + 1;
	}
	for (int i = 0; i < container.size() * width; i++)
	{
		cout << "-";
	}
	cout << std::endl;
	for (auto& E : container)
	{
		cout.width(width);
		cout << E;
	}
	cout << std::endl;
	for (auto& E : container)
	{
		if ((string*)iter.ptr != &E)
		{
			cout.width(width);
			cout << " ";
		}
		else
		{
			cout.width(width);
			cout << "|" << std::endl;
			break;
		}
	}

	for (int i = 0; i < container.size() * width; i++)
	{
		cout << "-";
	}
	cout << std::endl;
}
template<class T, class IT>
bool Iterpp(T& container, IT& iter, vector<string>& commands)
{
	if (commands[0] == "iter++" && commands.size() == 1)
	{

		if (iter != container.end())
		{
			iter++;
			if (!(iter != container.end()))
			{
				cout << "reset to begin" << endl;
				iter = container.begin();
			}
		}
		else
		{
			cout << "reset to begin" << endl;
			iter = container.begin();
		}
		return true;
	}
}
template<class T, class IT>
bool Reset(T& container, IT& iter, vector<string>& commands)
{
	if (commands[0] == "reset" && commands.size() == 1)
	{
		iter = container.begin();
		return true;
	}
}
template<class T, class IT>
bool ChangeValue(T& container, IT& iter, vector<string>& commands)
{
	if (commands[0] == "change" && commands.size() == 2)
	{
		if (iter != container.end())
		{
			*iter = commands[1];
		}
		else
		{
			cout << "reset to begin" << endl;
			iter = container.begin();
		}
		return true;
	}
}
//指令控制
void control_stack(Stack<string>& container)
{
	using namespace std;
	auto iter = container.begin();
	int iter_pos = 0;
	for (;;)
	{
		//打印
		PrintContainer(container, iter);
		cout << "Stack: ";
		//输入指令
		auto  commands = InputCommands();

		//指令
		if (commands[0] == "switch")
		{
			break;
		}
#define SET_COMMAND(function) function(container,commands)
		else if (SET_COMMAND(Push)) { iter = container.begin(); }
		else if (SET_COMMAND(Pop)) { iter = container.begin(); }
		else if (SET_COMMAND(Top)) {}
		else if (SET_COMMAND(Empty)) {}
		else if (SET_COMMAND(Size)) {}
		else if (SET_COMMAND(Clear)) {}
		else if (Iterpp(container, iter, commands));
		else if (Reset(container, iter, commands));
		else if (ChangeValue(container, iter, commands));
		else if (commands[0] == "help") { cout << help; }
		else { cout << "No such command" << endl; }
	}
}
void control_queue(Queue<string>& container)
{
	using namespace std;
	auto iter = container.begin();
	int iter_pos = 0;
	for (;;)
	{
		//打印
		PrintContainer(container, iter);
		cout << "Queue: ";
		//输入指令
		auto  commands = InputCommands();

		//指令
		if (commands[0] == "switch")
		{
			break;
		}
#define SET_COMMAND(function) function(container,commands)
		else if (SET_COMMAND(Push)) { iter = container.begin(); }
		else if (SET_COMMAND(Pop)) { iter = container.begin(); }
		else if (SET_COMMAND(Front)) {}
		else if (SET_COMMAND(Empty)) {}
		else if (SET_COMMAND(Size)) {}
		else if (SET_COMMAND(Clear)) {}
		else if (Iterpp(container, iter, commands));
		else if (Reset(container, iter, commands));
		else if (ChangeValue(container, iter, commands));
		else if (commands[0] == "help") { cout << help; }
		else { cout << "No such command" << endl; }
	}
}


int main()
{
	Stack<string> stack;
	Queue<string> queue;
	init_help();
	cout << help;
	while (1)
	{
		control_stack(stack);
		control_queue(queue);
	}

}
