#include <iostream>
#include <cctype>
#include <codecvt>
#include <locale>
#include "modAlphaCipher.h"
using namespace std;
bool isValid(const string& s)
{
	locale loc("ru_RU.UTF-8");
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t>
	codec;
	wstring ws = codec.from_bytes(s);
	for(auto wc:ws)
		if (!isalpha(wc,loc) || !isupper(wc,loc))
			return false;
	return true;
}
int main(int argc, char **argv)
{
	string key;
	string text;
	unsigned op;
	cout<<"Cipher ready. Input key: ";
	cin>>key;
	if (!isValid(key)) {
		cerr<<"key not valid\n";
		return 1;
	}
	cout<<"Key loaded\n";
	modAlphaCipher cipher(key);
	do {
		cout<<"Cipher ready. Input operation (0-exit, 1-encrypt, 2-decrypt): ";
		cin>>op;
		if (op > 2) {
			cout<<"Illegal operation\n";
		} else if (op >0) {
			cout<<"Cipher ready. Input text: ";
			cin>>text;
			if (isValid(text)) {
				if (op==1) {
					cout<<"Encrypted text:"<<cipher.encrypt(text)<<endl;
				} else {
					cout<<"Decrypted text:"<<cipher.decrypt(text)<<endl;
				}
			} else {
				cout<<"Operation aborted: invalidtext\n";
			}
		}
	} while (op!=0);
	return 0;
}

/*Заголовочный файл*/
#pragma once
#include <vector>
#include <string>
#include <codecvt>
#include <locale>
#include <map>
class modAlphaCipher
{
private:
	std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
	std::map <wchar_t,int> alphaNum;
	std::vector <int> key;
	std::vector<int> convert(const std::wstring& 	ws);
	std::string convert(const std::vector<int>& v);
	std::wstring towstr(const std::string& s);
	std::string fromwstr(const std::wstring& ws);
public:
	modAlphaCipher()=delete;
	modAlphaCipher(const std::string& skey);
	std::string encrypt(const std::string& 	open_text);
	std::string decrypt(const std::string& 	cipher_text);
};

/*Модифицированный модуль*/

#include "modAlphaCipher.h"
modAlphaCipher::modAlphaCipher(const std::string& skey)
{
	for (unsigned i=0; i<numAlpha.size(); i++) {
		alphaNum[numAlpha[i]]=i;
	}
	std::wstring wskey = towstr(skey);
	key = convert(wskey);
}
std::string modAlphaCipher::encrypt(const std::string& open_text)
{
	std::wstring open_wtext = towstr (open_text);
	std::vector<int> work = convert(open_wtext);
	for(unsigned i=0; i < work.size(); i++) {
		work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
	}
	return convert(work);
}
std::string modAlphaCipher::decrypt(const std::string& cipher_text)
{
	std::wstring cipher_wtext = towstr (cipher_text);
	std::vector<int> work = convert(cipher_wtext);
	for(unsigned i=0; i < work.size(); i++) {
		work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
	}
	return convert(work);
}
inline std::vector<int> modAlphaCipher::convert(const std::wstring& ws)
{
	std::vector<int> result;
	for(auto wc:ws) {
		result.push_back(alphaNum[wc]);
	}
	return result;
}
inline std::string modAlphaCipher::convert(const std::vector<int>& v)
{
	std::wstring wresult;
	for(auto i:v) {
		wresult.push_back(numAlpha[i]);
	}
	std::string result = fromwstr(wresult);
	return result;
}
std::wstring modAlphaCipher::towstr(const std::string& s)
{
	std::locale loc("ru_RU.UTF-8");
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> codec;
	std::wstring ws = codec.from_bytes(s);
	return ws;
}
std::string modAlphaCipher::fromwstr(const std::wstring& ws)
{
	std::locale loc("ru_RU.UTF-8");
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> codec;
	std::string s = codec.to_bytes(ws);
	return s;
}
