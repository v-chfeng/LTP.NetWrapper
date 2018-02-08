// DU.LTPNer.Lib.cpp : main project file.

#include "stdafx.h"
#include "postag_dll.h"
#include "ner_dll.h"
#include "string.h"
#include <iostream>
#include <vector>
#include <string>
#include <locale>
#include <codecvt>
#include "DU.LTPNer.Lib.h"

#pragma comment(lib, "postagger.lib")
#pragma comment(lib, "ner.lib")
#pragma comment(lib, "libpostagger.lib")
#pragma comment(lib, "libner.lib")

using namespace System;

int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"Hello World");
	Console::ReadKey();

	// test pos dll
	const char* model_path = "pos.model";
	const char* wb_str = "IBM#N#普华#N#永#N#道#N#全球#N#矿业#N#公司#N#40#N#强#N#在#N#2016#N#年#N#恢复#N#盈利";
	char** result;
	ltp_ner_wrapper(wb_str, result);

    return 0;
}

extern "C" _declspec(dllexport) int _stdcall ltp_ner_wrapper(const char* wb_array, char** result)
{ 	
	void* pos_engine = postagger_create_postagger("pos.model");
	if (!pos_engine)
	{
		return -1;
	}

	std::vector<std::string> words;
	
	char* wbstr = new char[strlen(wb_array) + 1];
	strcpy(wbstr, wb_array);
	const char* split_str = "#N#";
	char* p;
	p = strtok(wbstr, split_str);
	while (p != NULL)
	{
		std::string oneword = p;
		words.push_back(oneword);
		p = strtok(NULL, split_str);
	}

	std::vector<std::string> tags;

	postagger_postag(pos_engine, words, tags);

	for (int i = 0; i < tags.size(); ++i) 
	{
		const char* words_char = words[i].c_str();
		const char* tags_char = tags[i].c_str();
		std::cout << words_char << "/" << tags_char;
		if (i == tags.size() - 1) std::cout << std::endl;
		else std::cout << " ";

	}

	postagger_release_postagger(pos_engine);

	void* ner_engine = ner_create_recognizer("ner.model");
	if (!ner_engine)
	{
		return -1;
	}

	std::vector<std::string> nertags;
	ner_recognize(ner_engine, words, tags, nertags);
	std::string totalResult = "";

	for (int i = 0; i < nertags.size(); ++i)
	{
		std::cout << words[i] << "\t" << tags[i] << "\t" << nertags[i] << std::endl;	
		if (nertags[i] != "O")
		{
			totalResult += ";"+ words[i] + "||" + nertags[i];
		}
	}

	strcpy(*result, (char*)totalResult.c_str());
	
	ner_release_recognizer(ner_engine);

	//getchar();
	return 0;
}


std::wstring UTF8_To_UTF16(const std::string &source)
{
	try
	{
		static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> cvt;
		return cvt.from_bytes(source);
	}
	catch (std::range_error &)
	{
		return std::wstring();
	}
}

std::string UTF16_To_UTF8(const std::wstring &source)
{
	try
	{
		static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> cvt;
		return cvt.to_bytes(source);
	}
	catch (std::range_error &)
	{
		return std::string();
	}
}
