/*Заголовочный файл модуля*/
	#pragma once
	#include <string>
	using namespace std;
	class Ciphr
	{
		char** value;
		int a, b; // строки и столбцы
	public:
		Ciphr() = delete;
		Ciphr(int key, const string& s);
		string encrypt(const std::string& open_text);
	//зашифрование
		string decrypt(const std::string& 	cipher_text);//расшифрование
		~Ciphr();
	};

	/*Модуль шифра табличной перестановки*/
	#include "ch.h"
	Ciphr::Ciphr(int key, const string& s)
	{
		a = key;
		b = ((s.size() - 1)/a + 1);
		value = new char * [b];
		for (int i = 0; i < b; i++) {
			value[i] = new char [a];
		}
	}
	string Ciphr::encrypt(const string& open_text)
	{
	//заполнение таблицы " "
		for (int i=0; i < b; i++)
			for (int j=0; j < a; j++)
				value[i][j] = '*';
	//заполнение таблицы текстом
		for (int i = 0; i < open_text.size(); i ++)
			value[i/a][i%a] = open_text[i];
	//вывод таблицы в строку
		string ciphr_text;
		for (int i = a - 1; i >= 0; i --)
			for (int j = 0; j < b; j++)
				ciphr_text = ciphr_text + value[j][i];
		return ciphr_text;
	}
	string Ciphr::decrypt(const string& ciphr_text)
	{
	//заполнение таблицы "*"
		for (int i=0; i < b; i++)
			for (int j=0; j < a; j++)
				value[i][j] = '*';
	//заполнение таблицы текстом
		for (int i = 0; i < ciphr_text.size(); i ++)
			value[i%b][i/b] = ciphr_text[i];
	//вывод таблицы в строку
		string open_text;
		for (int i = 0; i < b; i ++)
			for (int j = a - 1; j >= 0; j--)
				open_text = open_text + value[i][j];
		return open_text;
	}
	Ciphr::~Ciphr()
	{
		for (int i = 0; i < b; i++) {
			delete [] value[i];
		}
		delete [] value;
	}