#pragma once

#include "cocos2d.h"

class ScoreManager
{
	static ScoreManager* inst;
	unsigned int score;

	ScoreManager();
	~ScoreManager() {}
public:
	static ScoreManager* getInstance();
	inline int getScore() const { return score; }
	inline void setScore(const unsigned int score) { this->score = score; }

	void end();
};