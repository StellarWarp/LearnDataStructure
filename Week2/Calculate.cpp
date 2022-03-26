#include <iostream>
#include"Formula.h"
using namespace std;
int main()
{
	string expression;
	cout << "Input expression support integer only" << endl;;
	while (1)
	{
		cout << "Expression : ";
		cin >> expression;
		Formula test(expression);
		if(test.Check())
			cout << test.Calculate() << endl;
	}
}

