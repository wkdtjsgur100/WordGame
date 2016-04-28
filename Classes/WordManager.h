#pragma once

#include "cocos2d.h"

/*
*	Ʋ�� �ܾ�� map���� ������ �ִ� �Լ�
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