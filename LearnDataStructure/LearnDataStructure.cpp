#include <iostream>
#include <string>
#include "LinkedList.h"
#include "OneWayLinkedList.h"


//打印
template<class LT>
void printlist(LT& list, int iterpos = 0)
{
	int width = 1;
	for (auto& E : list)
	{
		std::string lentest;
		lentest = std::to_string(E);
		if (strlen(lentest.c_str()) + 1 > width) width = strlen(lentest.c_str()) + 1;
	}
	for (int i = 0; i < list.size() * width; i++)
	{
		std::cout << "—";
	}
	std::cout << std::endl;
	for (auto& E : list)
	{
		std::cout.width(width);
		std::cout << E;
	}
	std::cout << std::endl;
	if (iterpos >= 0)
	{
		for (int i = 0; i < iterpos; i++)
		{
			std::cout.width(width);
			std::cout << " ";
		}
		std::cout.width(width);
		std::cout << "|" << std::endl;
	}
	/*std::cout << "iterator : [" << iter_value << "]" << std::endl;*/
	for (int i = 0; i < list.size() * width; i++)
	{

		std::cout << "—";
	}
	std::cout << std::endl;
}

std::string help;//帮助文本

//指令控制
template<class T>
void control_O(T& list)
{
	using namespace std;
	auto iter = list.begin();
	int iter_pos = 0;
	for (;;)
	{
		//迭代器位置//可视化输出参数
		iter_pos = 0;
		//更新位置
		for (auto& E : list)
		{
			if ((int*)iter.ptr == &E)
			{
				break;
			}
			iter_pos++;
		}
		if (list.size() == 0) iter = list.begin();
		else if (!iter.ptr || iter_pos >= list.size()) { iter = list.begin();  iter_pos = 0; }
		printlist(list, iter_pos);
		std::cout << "OneWayLinkedList: ";
		//输入指令
		std::vector<std::string>  commands;
		for (;;)
		{
			std::string temp;
			std::cin >> temp;
			commands.push_back(temp);
			if (getchar() == '\n') break;
		}

		//指令
		if (commands[0] == "00" || commands[0] == "switch")
		{
			break;
		}
		else if (commands[0] == "01" || commands[0] == "size")
		{
			std::cout << list.size() << std::endl;
		}
		else if (commands[0] == "02" || commands[0] == "print")
		{
			printlist(list);
		}
		else if (commands[0] == "10" || commands[0] == "append")
		{
			commands.erase(commands.begin());
			for (auto& s : commands)
				list.append(atoi(s.c_str()));
		}
		else if (commands[0] == "11" || commands[0] == "insert")
		{
			int v = atoi(commands[1].c_str());
			if (commands[2] == "before")
			{
				if (commands.size() == 4)
				{
					int s = atoi(commands[3].c_str());
					if (s < 0 || s >= list.size())
					{
						cout << "out of range" << endl;
						continue;
					}
					list.append(v, &list[s]);
				}
				else
					list.append(v, iter);
			}
			else if (commands[2] == "after")
			{
				if (commands.size() == 4)
				{
					int s = atoi(commands[3].c_str());
					if (s < 0 || s >= list.size())
					{
						cout << "out of range" << endl;
						continue;
					}
					list.insert(v, &list[s]);
				}
				else
					list.insert(v, iter);
			}
			else { std::cout << "No such command" << std::endl; }
		}
		else if (commands[0] == "12" || commands[0] == "remove")
		{
			if (commands.size() == 2)
			{
				int s = atoi(commands[1].c_str());
				if (s < 0 || s >= list.size())
				{
					cout << "out of range" << endl;
					continue;
				}
				list.remove(&list[s]);
			}
			else
				iter = list.remove(iter);

		}
		else if (commands[0] == "13" || commands[0] == "set_empty")
		{
			list.setEmpty();
		}
		else if (commands[0] == "14" || commands[0] == "reverse")
		{
			list.reverse();
			if (iter.prev_ptr)iter.ptr = iter.prev_ptr->next;
			else iter = list.begin();
		}
		else if (commands[0] == "15" || commands[0] == "search")
		{
			int s = atoi(commands[1].c_str());
			queue<int*> result = list.search(s);
			while (!result.empty())
			{
				cout << result.front() << " ";
				result.pop();
			}
			cout << endl;
		}
		else if (commands[0] == "16" || commands[0] == "parity_swap")
		{
			list.paritySwap();
			if (iter.prev_ptr)iter.ptr = iter.prev_ptr->next;
			else iter = list.begin();
		}
		else if (commands[0] == "17" || commands[0] == "set_ringed")
		{
			if (list.setRing())
			{
				cout << "Success" << endl;
				iter = list.begin();
			}
			else
			{
				cout << "Empty List" << endl;
			}
		}
		else if (commands[0] == "18" || commands[0] == "check_ring")
		{
			if (list.isRing_ForceCheck())
			{
				cout << "True" << endl;
			}
			else
			{
				cout << "False" << endl;
			}
		}
		else if (commands[0] == "19" || commands[0] == "middle")
		{
			cout << list.middle() << endl;
		}
		else if (commands[0] == "20" || commands[0] == "iter++")
		{
			if ((iter_pos + 1 > list.size() - 1) && !list.isRing())
			{
				cout << "out of range" << endl;
			}
			else
			{
				iter++;
				iter_pos++;
			}
		}
		else if (commands[0] == "22" || commands[0] == "iter+=")
		{
			int s = atoi(commands[1].c_str());
			if ((iter_pos + s > list.size() - 1 || iter_pos + s < 0) && !list.isRing())
			{
				cout << "out of range" << endl;
			}
			else
			{
				iter = iter + s;
				iter_pos += s;
			}
		}
		else if (commands[0] == "24" || commands[0] == "reset")
		{
			iter = list.begin();
		}
		else if (commands[0] == "help") { cout << help; }
		else { std::cout << "No such command" << std::endl; }
	}
}
//指令控制
template<class T>
void control_D(T& list)
{
	using namespace std;
	auto iter = list.begin();
	int iter_pos = 0;

	for (;;)
	{
		iter_pos = 0;
		for (auto& E : list)
		{
			if ((int*)iter.ptr == &E)
			{
				break;
			}
			iter_pos++;
		}
		if (list.size() == 0) iter.ptr = nullptr;
		else if (!iter.ptr || iter_pos >= list.size()) { iter = list.begin();  iter_pos = 0; }
		printlist(list, iter_pos);
		std::cout << "DoubleWayLinkedList: ";

		std::vector<std::string>  commands;
		for (;;)
		{
			std::string temp;
			std::cin >> temp;
			commands.push_back(temp);
			if (getchar() == '\n') break;
		}

		//指令
		if (commands[0] == "00" || commands[0] == "switch")
		{
			break;
		}
		else if (commands[0] == "01" || commands[0] == "size")
		{
			std::cout << list.size() << std::endl;
		}
		else if (commands[0] == "02" || commands[0] == "print")
		{
			printlist(list);
		}
		else if (commands[0] == "10" || commands[0] == "append")
		{
			commands.erase(commands.begin());
			for (auto& s : commands)
			{
				list.append(atoi(s.c_str()));
			}

		}
		else if (commands[0] == "11" || commands[0] == "insert")
		{
			int v = atoi(commands[1].c_str());
			if (commands[2] == "before")
			{
				if (commands.size() == 4)
				{
					int s = atoi(commands[3].c_str());
					if (s < 0 || s >= list.size())
					{
						cout << "out of range" << endl;
						continue;
					}
					list.append(v, &list[s]);
				}
				else
					list.append(v, iter);
			}
			else if (commands[2] == "after")
			{
				if (commands.size() == 4)
				{
					int s = atoi(commands[3].c_str());
					if (s < 0 || s >= list.size())
					{
						cout << "out of range" << endl;
						continue;
					}
					list.insert(v, &list[s]);
				}
				else
					list.insert(v, iter);
			}
			else { std::cout << "No such command" << std::endl; }
		}
		else if (commands[0] == "12" || commands[0] == "remove")
		{
			if (commands.size() == 2)
			{
				int s = atoi(commands[1].c_str());
				if (s < 0 || s >= list.size())
				{
					cout << "out of range" << endl;
					continue;
				}
				list.remove(&list[s]);
			}
			else
				iter = list.remove(iter);

		}
		else if (commands[0] == "13" || commands[0] == "set_empty")
		{
			list.setEmpty();
		}
		else if (commands[0] == "14" || commands[0] == "reverse")
		{
			list.reverse();
		}
		else if (commands[0] == "15" || commands[0] == "search")
		{
			int s = atoi(commands[1].c_str());
			queue<int*> result = list.search(s);
			while (!result.empty())
			{
				cout << result.front() << " ";
				result.pop();
			}
			cout << endl;
		}
		else if (commands[0] == "16" || commands[0] == "parity_swap")
		{
			list.paritySwap();
		}
		else if (commands[0] == "17" || commands[0] == "set_ringed")
		{
			if (list.setRing())
			{
				cout << "Success" << endl;
			}
			else
			{
				cout << "Empty List" << endl;
			}
		}
		else if (commands[0] == "18" || commands[0] == "check_ring")
		{
			if (list.isRing_ForceCheck())
			{
				cout << "True" << endl;
			}
			else
			{
				cout << "False" << endl;
			}
		}
		else if (commands[0] == "19" || commands[0] == "middle")
		{
			cout << list.middle() << endl;
		}
		else if (commands[0] == "20" || commands[0] == "iter++")
		{
			if ((iter_pos + 1 > list.size() - 1) && !list.isRing())
			{
				cout << "out of range" << endl;
			}
			else
			{
				iter++;
				iter_pos++;
			}
		}
		else if (commands[0] == "21" || commands[0] == "iter--")
		{
			if ((iter_pos - 1 < 0) && !list.isRing())
			{
				cout << "out of range" << endl;
			}
			else
			{
				iter--;
				iter_pos--;
			}
		}
		else if (commands[0] == "22" || commands[0] == "iter+=")
		{
			int s = atoi(commands[1].c_str());
			if ((iter_pos + s > list.size() - 1 || iter_pos + s < 0) && !list.isRing())
			{
				cout << "out of range" << endl;
			}
			else
			{
				iter = iter + s;
				iter_pos += s;
			}
		}
		else if (commands[0] == "23" || commands[0] == "iter-=")
		{
			int s = atoi(commands[1].c_str());
			if ((iter_pos + s > list.size() - 1 || iter_pos + s < 0) && !list.isRing())
			{
				cout << "out of range" << endl;
			}
			else
			{
				iter = iter - s;
				iter_pos -= s;
			}
		}
		else if (commands[0] == "24" || commands[0] == "reset")
		{
			iter = list.begin();
		}
		else if (commands[0] == "help") { cout << help; }
		else { std::cout << "No such command" << std::endl; }
	}
}

int main()
{
	using namespace std;
	OneWayLinkedList<int> list1({ 1,2,3,4,5,6 });
	LinkedList<int> list2({ 1,2,3,4,5,6 });

	help += "command list:\nBasicOperation: \n	(00)switch\n	(01)size\n	(02)print\n";
	help += "ListOperation:\n	(10)append datalist\n	(11)insert value *before/after elementOrder/(left empty to use iterator)\n";
	help += "	    * don't need this tern if use OneWayLinkedList \n	     *elementOrder start form 0\n";
	help += "	(12)remove elementOrder/(left empty to use iterator)\n	(13)set_empty\n";
	help += "	(14)reverse\n	(15)search value\n	(16)parity_swap\n	(17)set_ringed\n	(18)check_ring\n	(19)middle\n";
	help += "IteratorOperation:\n	(20)iter++\n	(21)iter--\n	(22)iter+= num\n	(23)iter-= num\n	(24)reset\n\n";
	cout << help;
	cout << "tip: using [help] to call command list again \ncommand example:\n	append 1 2 3 4\n	10 1 2 3 4\n\n";
	while (1)
	{

		control_O(list1);
		control_D(list2);
	}

}
