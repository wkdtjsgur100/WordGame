#include "CSVParser.h"

CSVParser* CSVParser::instance = nullptr;

using namespace std;

CSVParser * CSVParser::getInstance()
{
	if (instance == nullptr)
		instance = new CSVParser();
	
	return instance;
}

void CSVParser::release()
{
	delete instance;
	instance = nullptr;
}

void CSVParser::convertToMap(string data)
{

	for (int i = 1; i <= 10; i++)
	{
		size_t find_idx = -1;

		char format[255] = { 0 };
		
		sprintf(format, "day%d", i);
		
		int formatLength;

		for (formatLength = 0; format[formatLength] != 0; formatLength++)
		{
		}

		while ( (find_idx = data.find(format, find_idx+1)) != string::npos)
		{
			pair<string, string> p;
			
			size_t eng_findidx = data.find(",", find_idx + formatLength + 1);

			size_t front = find_idx + formatLength + 1;
			string eng = data.substr(front, eng_findidx-front);
			
			size_t kor_findidx = data.find(",", eng_findidx+1);

			size_t tFind = data.find(",", eng_findidx + 1);

			string kor = data.substr(eng_findidx + 1, tFind - eng_findidx - 1);
			
			if (kor.find("\"") != string::npos)
				kor.append("\"");

			p.first = eng;
			p.second = kor;

			_map.insert(p);
		}
	}

}

std::string CSVParser::getKorAnswer(std::string eng)
{
	return _map[eng.c_str()];
}

std::string CSVParser::getEngAnswer(std::string kor)
{
	for (auto i = _map.begin(); i != _map.end(); ++i)
	{
		if (!strcmp(i->second.c_str(), kor.c_str()))
			return i->first;
	}
}

std::string CSVParser::getRandomEngExceptParam(std::string param)
{
	int r = cocos2d::RandomHelper::random_int<int>(0, _map.size()-1);

	int c = 0;
	for (auto i = _map.begin(); i != _map.end(); ++i,c++)
	{
		if (r == c)
		{
			if (!strcmp(param.c_str(), i->first.c_str()))
				return getRandomEngExceptParam(param);
			else
				return i->first;
		}
	}
	return "null";
}

std::string CSVParser::getRandomKorExceptParam(std::string param)
{
	int r = cocos2d::RandomHelper::random_int<int>(0, _map.size() - 1);

	int c = 0;
	for (auto i = _map.begin(); i != _map.end(); ++i, c++)
	{
		if (r == c)
		{
			if (!strcmp(param.c_str(), i->first.c_str()))
				return getRandomKorExceptParam(param);
			else
				return i->second;
		}
	}
	return "null";
}

pair<string, string> CSVParser::getRandomPair()
{
	int r = cocos2d::RandomHelper::random_int<int>(0, _map.size());
	int c = 0;

	pair<string, string> p;
	for (auto i = _map.begin(); i != _map.end(); c++,i++)
	{
		if (c == r)
		{
			p.first = i->first;
			p.second = i->second;
			break;
		}
	}
	return p;
}
