#include <iostream>
#include<time.h>
#include<format>
#include"Sort.h"
#include"file.h"
using namespace std;

void Timer(bool st)
{
	static clock_t start, end;
	if (st)
		start = clock();
	else
	{
		end = clock();   //结束时间
		cout << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;  //输出时间（单位：ｓ）
	}
}

void  LevelTest(int maxlevel, int test_times)
{
	vector<int> Level = { (int)1e2,(int)1e3,(int)1e4,(int)1e5,(int)1e6,(int)1e7 };
	Level.resize(maxlevel);
	vector<vector<vector<int>>> LevelArrays;
	LevelArrays.resize(Level.size());

	srand(time(0));
	int level_index = 0;
	for (auto& Arrays : LevelArrays)
	{
		int level = Level[level_index];
		Arrays.resize(test_times);
		for (auto& Array : Arrays)
			for (int i = 0; i < level; i++)
				Array.push_back(rand() % 100);
		level_index++;
	}

#define TEST(func , title)\
	{																																								   \
		auto TestArray = LevelArrays;																											   \
		cout <<"\n"<< #title << endl;																														\
		for (int i = 0; i < Level.size(); i++)																											\
		{																																							   \
			cout << format("Test times : {}  level {} : {:8}	", test_times, i + 1, Level[i]);								  \
			Timer(true);																																	   \
			for (auto& Array : LevelArrays[i])																									   \
				func;																																			   \
			Timer(false);																																	   \
		}																																							   \
	}

	{
		auto TestArray = LevelArrays;
		cout << "\n" << "insertSort" << endl;
		for (int i = 0; i < 3 && i < Level.size(); i++)
		{
			cout << format("Test times : {}  level {} : {:8}	", test_times, i + 1, Level[i]);
			Timer(true);
			for (auto& Array : LevelArrays[i])
				insertSort(&Array[0], Array.size());
			Timer(false);
		}
	}
	TEST(MergeSort(&Array[0], 0, Array.size() - 1), MergeSort);
	TEST(QuickSort_Recursion(&Array[0], 0, Array.size() - 1), QuickSort_Recursion);
	//cout << "can't use QuickSort_Recursion in high level : Stack Overflow" << endl;
	TEST(QuickSort(&Array[0], Array.size()), QuickSort);
	TEST(CountSort(&Array[0], Array.size(), 1000), CountSort);
	TEST(RadixCountSort(&Array[0], Array.size()), RadixCountSort);
	TEST(OrderIn(&Array[0], Array.size(), 50), OrderIn 50);

	for (auto& Arrays : LevelArrays)
	{
		Arrays.resize(0);
	}
	level_index = 0;
	for (auto& Arrays : LevelArrays)
	{
		int level = Level[level_index];
		Arrays.resize(test_times);
		for (auto& Array : Arrays)
			for (int i = 0; i < level; i++)
				Array.push_back(rand() % 2);
		level_index++;
	}
	TEST(ColorSort(&Array[0], Array.size()), ColorSort);

}

std::string help;//帮助文本
void init_help()
{
	ifstream infile("help.txt");
	if (infile.is_open())
	{
		string buffer;
		while (getline(infile, buffer))
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

void Control()
{
	FileData<int> FD;
	while (1)
	{
		auto commands = InputCommands();
		if (commands[0] == "open")
		{
			if (commands.size() == 1)
				FD = (string)"test.bin";
			else if (commands.size() == 2)
				FD = commands[1];
		}
		else if (commands[0] == "print")
		{
			FD.Print();
		}
		else if (commands[0] == "save")
		{
			FD.Save();
		}
		else if (commands[0] == "input")
		{
			auto& Array = FD.GetArray();
			commands.erase(commands.begin());
			for (auto& s : commands)
				Array.push_back(atoi(s.c_str()));
		}
		else if (commands[0] == "clear")
		{
			FD.GetArray().resize(0);
		}
		else if (commands[0] == "sort" && commands.size() >= 2)
		{
			auto& Array = FD.GetArray();
			if (commands[1] == "insert")
			{
				insertSort(&Array[0], Array.size());
			}
			else if (commands[1] == "merge")
			{
				MergeSort(&Array[0], 0, Array.size() - 1);
			}
			else if (commands[1] == "quick_recursion")
			{
				QuickSort_Recursion(&Array[0], 0, Array.size() - 1);
			}
			else if (commands[1] == "quick")
			{
				QuickSort(&Array[0], Array.size());
			}
			else if (commands[1] == "count")
			{
				int max = 0;
				for (auto& E : Array)
					if (E > max)max = E;
				if (max <= 100000)
				{
					CountSort(&Array[0], Array.size(), max);
				}
				else
				{
					cout << "max num over 100000, may cause allocate fail" << endl;
				}
			}
			else if (commands[1] == "color")
			{
				bool err = false;
				for (auto& E : Array)
					if (E != 0 && E != 1 && E != 2)
					{
						cout << "Contain number besides 0 1 2" << endl;
						err = true;
						break;
					}
				if (err) continue;
				ColorSort(&Array[0], Array.size());
			}
			else if (commands[1] == "radix")
			{
				RadixCountSort(&Array[0], Array.size());
			}
			else
				cout << "No such command" << endl;
		}
		else if (commands[0] == "orderin" && commands.size() == 2)
		{
			auto& Array = FD.GetArray();
			cout << OrderIn(&Array[0], Array.size(), atoi(commands[1].c_str())) << endl;;
		}
		else if (commands[0] == "help")
			cout << help;
		else
			cout << "No such command" << endl;
	}
}
int main()
{
	/*LevelTest(5, 1);
	LevelTest(2, 10000);*/

	init_help();
	cout << help;
	Control();

}

