#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "DataManager.h"

#define BUTTON_NUM 4

class GameScene : public cocos2d::Layer
{
	//cocos2d::ui::ListView* listView;
	DataManager dataManager;
	
	cocos2d::ProgressTimer* timer;
	float fTime;

	int clearNum;

	cocos2d::Label* ansLabel[BUTTON_NUM];
	cocos2d::Label* questionLabel;
	cocos2d::Label* pinLabel;
	cocos2d::Label* scoreLabel;

	int currentAnsIndex;	//현재 정답의 인덱스를 저장. 
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void touchEvent(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	
	void correct();		//맞았다면
	void uncorrect();	//틀렸다면
	void update();

	void gameOver();

	void setTimerPercent(float percent);
	void pressPause();
	void update(float dt);
	void goHome(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};