#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameScene : public cocos2d::Layer
{
	//cocos2d::ui::ListView* listView;
	cocos2d::Vec2 toggleOriginVec;
	cocos2d::LabelTTF* crossLabels[4];
	std::string currentCorrect;
	int currentCorrectType; //0이면 영어, 1이면 한글
	bool isFirst;
	float dirAng;
	cocos2d::LabelTTF* scoreLabel;
	enum mDirection {
		TOP,
		LEFT,
		BOTTOM,
		RIGHT
	};
	int correctDir;
	bool bUpdateOnce;

	cocos2d::ProgressTimer* timer;
	float fTime;

	int clearNum;
public:

	cocos2d::Sprite* toggle;

	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void touchEvent(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void updateCross();
	void update();
	void listViewUpdate();
	void addRandomStringInListView(bool isTop = false);

	void completePush(mDirection d);
	void gameOver();

	void setTimerPercent(float percent);
	void pressPause();
	void update(float dt);
	void goHome(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};