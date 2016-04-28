#include "WordManager.h"

WordManager* WordManager::instance = nullptr;

using namespace std;

WordManager * WordManager::getInstance()
{
	if (instance == nullptr)
		instance = new WordManager();
	
	return instance;
}
void WordManager::end()
{
	delete instance;
	instance = nullptr;
}
