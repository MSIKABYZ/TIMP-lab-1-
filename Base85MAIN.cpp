#include "Base85HEADER.h"

/**
\brief Main function

The function is used to read file and send file string into class function 

Code:
\code
int main()
{
	setlocale(LC_ALL, ".1251");
	string a, k;
	try
	{
		cout << "Input file way" << endl;
		cin >> a;
		ifstream file(a, ios::binary);
		if (!file)
			throw 'f';
		cout << "Input save file way" << endl;
		cin >> k;
		ofstream file1(k, ios::binary);
		if (!file1)
			throw 'f';
		file.seekg(0, file.end);
		int l = file.tellg();
		file.seekg(0, file.beg);
		char* str = new char[l + 1];
		file.read(str, l);
		int vote;
		cout << "Inpute mode\n1.Code\n2.Decode" << endl;
		cin >> vote;
		if (vote != 1 && vote != 2)
			throw 'm';
		if (vote == 1)
		{
			string c;
			Base85 q;
			c = q.coder(str, l);
			file1 << c;
		}
		if (vote == 2)
		{
			string c;
			Base85 l1;
			c = l1.decoder(str, l);
			file1 << c;
		}
	}
	catch (char e)
	{
		switch (e)
		{
		case 'm':
			{
				cout << "Wrong mode" << endl;
				break;
			}
		case 'f':
		{
			cout << "Can't open file" << endl;
			break;
		}
		case 'i':
		{
			cout << "Wrong string" << endl;
			break;
		}
		}
	}
}
\endcode
*/
int main()
{
	setlocale(LC_ALL, ".1251");
	string a, k;
	try
	{
		cout << "Input file way" << endl;
		cin >> a;
		ifstream file(a, ios::binary);
		if (!file)
			throw 'f';
		cout << "Input save file way" << endl;
		cin >> k;
		ofstream file1(k, ios::binary);
		if (!file1)
			throw 'f';
		file.seekg(0, file.end);
		int l = file.tellg();
		file.seekg(0, file.beg);
		char* str = new char[l + 1];
		file.read(str, l);
		int vote;
		cout << "Inpute mode\n1.Code\n2.Decode" << endl;
		cin >> vote;
		if (vote != 1 && vote != 2)
			throw 'm';
		if (vote == 1)
		{
			string c;
			Base85 q;
			c = q.coder(str, l);
			file1 << c;
		}
		if (vote == 2)
		{
			string c;
			Base85 l1;
			c = l1.decoder(str, l);
			file1 << c;
		}
	}
	catch (char e)
	{
		switch (e)
		{
		case 'm':
			{
				cout << "Wrong mode" << endl;
				break;
			}
		case 'f':
		{
			cout << "Can't open file" << endl;
			break;
		}
		case 'i':
		{
			cout << "Wrong string" << endl;
			break;
		}
		}
	}
}