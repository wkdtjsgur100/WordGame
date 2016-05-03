#pragma once

#include "cocos2d.h"

struct MirrorData
{
	std::string chinese;  //����
	std::string pinyin;   //����
	std::string kor;		 //�ѱ���
};

/**
*  DataManager class
*
*  Data�� ������
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
	// csv���� ��ҵ��� �и��ؼ� vector data��� ����� �ش�.
	//
	void parsingData(std::string scvData);
};