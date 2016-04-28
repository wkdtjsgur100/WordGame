#pragma once

#include "cocos2d.h"

/*
*	틀린 단어들 map으로 관리해 주는 함수
*/
class WordManager
{
private:
	static WordManager* instance;
public:
	std::map<std::string, std::string > _wrongWords;

	static WordManager* getInstance();
	void end();
};