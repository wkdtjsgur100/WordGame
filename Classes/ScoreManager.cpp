#include "ScoreManager.h"

ScoreManager* ScoreManager::inst = nullptr;

ScoreManager::ScoreManager() {
	score = 0;
}
ScoreManager * ScoreManager::getInstance()
{
	if (inst == nullptr)
		inst = new ScoreManager();

	return inst;
}

void ScoreManager::end()
{
	if (inst != nullptr)
	{
		delete inst;
		inst = nullptr;
	}
}
