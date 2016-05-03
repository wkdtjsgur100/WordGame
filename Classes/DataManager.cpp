#include "DataManager.h"

using namespace std;
using namespace cocos2d;

MirrorData DataManager::getDataByIndex(int index)
{
	if (index < 0 || index >= datas.size())
	{
		log("index is not valid!!!");

		return MirrorData();
	}
	MirrorData md = datas.at(index);

	return md;
}

string DataManager::getChineseByIndex(int index)
{
	return datas.at(index).chinese;
}

string DataManager::getKorByIndex(int index)
{
	return datas.at(index).kor;
}

string DataManager::getPinyinByIndex(int index)
{
	return datas.at(index).pinyin;
}

int DataManager::getRandomIndexExceptParam(int exceptIndex)
{
	int r = RandomHelper::random_int<int>(0, datas.size() - 1);

	if (exceptIndex == r)
		return getRandomIndexExceptParam(exceptIndex);
	else
		return r;
}

void DataManager::parsingData(string scvData)
{
	if (scvData == "")
	{
		cocos2d::log("data is empty..");
		return;
	}
	int s_pos = 0, e_pos = 0;
	
	string str;
	
	int cnt = 0;
	MirrorData newMD;

	for (size_t i = 0; i < scvData.size(); i++)
	{
		char chk_c = scvData.at(i);
		if (chk_c == ';' || chk_c == '\n')
		{
			cnt %= 4;

			switch (cnt)
			{
			case 0:
				break;
			case 1:
				newMD.chinese = str;
				break;
			case 2:
				newMD.pinyin = str;
				break;
			case 3:
				newMD.kor = str;
				datas.push_back(newMD);

				break;
			}
			str = "";
			cnt++;
		}
		else
			str += chk_c;
	}
}
