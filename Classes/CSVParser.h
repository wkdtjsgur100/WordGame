#pragma once

#include "cocos2d.h"

class CSVParser
{
private:
	static CSVParser* instance;
	std::map<std::string, std::string > _map;

public:
	static CSVParser* getInstance();
	static void release();

	void convertToMap(std::string data);

	std::string getKorAnswer(std::string eng);
	std::string getEngAnswer(std::string kor);

	std::string getRandomEngExceptParam(std::string param);
	std::string getRandomKorExceptParam(std::string param);

	std::pair<std::string,std::string> getRandomPair();
};