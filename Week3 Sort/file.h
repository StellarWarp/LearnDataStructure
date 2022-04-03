#pragma once
#include<fstream>

template<class T>
class FileData
{
	ifstream infile;
	ofstream outfile;
	string address;

	vector<T> dataArray;
public:
	FileData() {};
	FileData(string address)
	{
		this->address = address;
		infile.open(address, ios::binary | ios::in);
		if (!infile.is_open()) { cerr << "Fail to open file\nadress added : " << address << endl; }
		T temp{};
		infile.seekg(0);
		while (1)
		{
			infile.read((char*)&temp, sizeof(T));
			if (infile.eof()) break;
			dataArray.push_back(temp);
		}
		infile.close();
	}
	vector<T>& GetArray()
	{
		return dataArray;
	}
	void Save()
	{
		outfile.open(address, ios::binary | ios::out);
		if (!outfile.is_open()) cerr << "Fail to open file" << endl;
		outfile.seekp(0);
		for (auto& E : dataArray)
			outfile.write((char*)&E, sizeof(T));
		outfile.close();
	}

	void Print()
	{
		for (auto& E : dataArray)
			cout << E << " ";
		cout << endl;
	}


};