#pragma once
#include<iostream>
using namespace std;

static class input
{
	bool err = false;
	string message;
	void Update()
	{
		if (err)
		{
			cerr << message << endl;
			err = false;
		}
	}
	int Integer()
	{
		string inputcache;
		int data;

		cin >> inputcache;

		//检查
		for (auto c : inputcache)
		{
			if (!isdigit(c))
			{
				message = "Invalid integer";
				err = true;
				return 0;
			}
		}
		data = atoi(inputcache.c_str());

		return data;
	}
	float Float()
	{
		string inputcache;
		float data;

		cin >> inputcache;

		//检查
		for (auto c : inputcache)
		{
			if (!isdigit(c) && c != '.')
			{
				message = "Invalid float";
				err = true;
				return 0;
			}
		}
		data = atof(inputcache.c_str());

		return data;
	}
};