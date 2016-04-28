#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameOverScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	void goHome(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	CREATE_FUNC(GameOverScene);
};