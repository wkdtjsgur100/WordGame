#pragma once

#include "cocos2d.h"

struct MirrorData
{
	std::string chinese;  //한자
	std::string pinyin;   //병음
	std::string kor;		 //한국어
};

/**
*  DataManager class
*
*  Data를 관리함
*/

class DataManager
{
	std::vector<MirrorData> datas; //

public:
	int getDataSize() 
	{ 
		return datas.size(); 
	}

	MirrorData getDataByIndex(int index);

	std::string getChineseByIndex(int index);
	std::string getPinyinByIndex(int index);
	std::string getKorByIndex(int index);

	int getRandomIndexExceptParam(int exceptIndex);
	
	// 
	// csv파일 요소들을 분리해서 vector data들로 만들어 준다.
	//
	void parsingData(std::string scvData);
};