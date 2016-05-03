#include "GameScene.h"
#include "base\ccUTF8.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "ScoreManager.h"

#define CONV_Y(y) 800 - y

USING_NS_CC;
using namespace ui;
using namespace std;
using namespace CocosDenshion;

cocos2d::Scene * GameScene::createScene()
{
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
		return false;

	ssize_t bufferSize = 0;
	string getData = FileUtils::getInstance()->getStringFromFile("db/chinese_db.csv");

	log("%s", getData.c_str());
	if (getData != "")
	{
		dataManager.parsingData(getData);
	}

	/*
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	*/

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto game_back = Sprite::create("game_background.png");
	game_back->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(game_back, -10);


	/////////////////////////////////////////////////
	/*
	auto touchListener = EventListenerTouchOneByOne::create();
	// When "swallow touches" is true, then returning 'true' from the onTouchBegan method will "swallow" the touch event, preventing other listeners from using it.
	touchListener->setSwallowTouches(true);

	isFirst = true;
	dirAng = 0.0f;
	bUpdateOnce = false;

	touchListener->onTouchBegan = [=](Touch* touch, Event* event) {
		// event->getCurrentTarget() returns the *listener's* sceneGraphPriority node.
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		//Get the position of the current point relative to the button
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		//Check the click area
		if (rect.containsPoint(locationInNode))
		{
			log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
			target->setOpacity(180);
			return true;
		}
		return false;
	};

	//Trigger when moving touch
	touchListener->onTouchMoved = [=](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		//Move the position of current button sprite
		float moveAccessDt = 70.0f;

		float touchDtLength = fabs((touch->getStartLocation() - touch->getLocation()).length());
		if (touchDtLength < 20.0f)
		{
			target->setPosition(target->getPosition() + touch->getDelta());
			return;
		}
		if (isFirst)
		{
			dirAng = touch->getDelta().getAngle();

			dirAng = CC_RADIANS_TO_DEGREES(dirAng);
			isFirst = false;
		}
		int dir = 0;

		if (dirAng >= 45.0f && dirAng <= 45.0f + 90.0f)
			dir = 0;
		else if (dirAng >= -135.0f && dirAng <= -45.0f)
			dir = 0;
		else
			dir = 1;

		switch (dir)
		{
		case 0:
		{
			if (target->getPositionY() > toggleOriginVec.y - moveAccessDt &&
				target->getPositionY() < toggleOriginVec.y + moveAccessDt)
			{
				target->setPositionY(target->getPosition().y + touch->getDelta().y);
			}
		}
		break;

		case 1:
		{
			if (target->getPositionX() > toggleOriginVec.x - moveAccessDt &&
				target->getPositionX() < toggleOriginVec.x + moveAccessDt)
			{
				target->setPositionX(target->getPosition().x + touch->getDelta().x);
			}
		}
		break;
		}
		if (target->getPositionY() < toggleOriginVec.y - moveAccessDt)
		{
			completePush(mDirection::BOTTOM);
			target->setPositionY(toggleOriginVec.y - moveAccessDt);
		}
		if (target->getPositionY() > toggleOriginVec.y + moveAccessDt)
		{
			completePush(mDirection::TOP);
			target->setPositionY(toggleOriginVec.y + moveAccessDt);
		}
		if (target->getPositionX() < toggleOriginVec.x - moveAccessDt)
		{
			completePush(mDirection::LEFT);
			target->setPositionX(toggleOriginVec.x - moveAccessDt);
		}
		if (target->getPositionX() > toggleOriginVec.x + moveAccessDt)
		{
			completePush(mDirection::RIGHT);
			target->setPositionX(toggleOriginVec.x + moveAccessDt);
		}
	};

	//Process the touch end event
	touchListener->onTouchEnded = [=](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		log("sprite onTouchesEnded.. ");
		target->setOpacity(255);
		//Reset zOrder and the display sequence will change
		target->setPosition(toggleOriginVec);
		isFirst = true;
		bUpdateOnce = false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,toggle);
	*/
	///////////////////////////////////////////////////////

	//영단어 목록보여주는 부분

	/*
	listView = ListView::create();

	listView->setDirection(ScrollView::Direction::VERTICAL);
	listView->setContentSize(Size(500, 410));
	listView->setPosition(Vec2(100, 40));
	listView->setBackGroundColor(Color3B::BLUE);
	listView->setScrollBarEnabled(false);

	listView->setItemsMargin(10.0f);

	addRandomStringInListView(true);

	for (int i = 0; i < 6; i++)
	{
		addRandomStringInListView();
	}

	this->addChild(listView,100);
	*/
	///////////////////////////

	////////////////////////////////// score setting
	scoreLabel = Label::createWithTTF("0", "fonts/font.ttf", 50);

	scoreLabel->setPosition(Vec2(343, CONV_Y(53)));
	scoreLabel->setColor(Color3B::BLACK);

	addChild(scoreLabel);

	///////////////////////////////////// timer

	timer = ProgressTimer::create(Sprite::create("timer.png"));


	timer->setPercentage(100.0f);
	timer->setType(ProgressTimer::Type::BAR);
	timer->setBarChangeRate(Vec2(1, 0));
	timer->setMidpoint(Vec2(0, 1));
	timer->setPosition(visibleSize.width*0.5, CONV_Y(375));

	fTime = 20.0f;			//제한시간 30초

	setTimerPercent(100.0f);

	addChild(timer, 5);

	///////////////////////////////////// pause_button

	auto pauseBtn = Button::create("pause.png");

	pauseBtn->setZoomScale(0.7f);
	pauseBtn->setPosition(Vec2(35, CONV_Y(767)));

	addChild(pauseBtn);
	/*
	auto pauseListener = EventListenerTouchOneByOne::create();

	pauseListener->onTouchBegan = [](Touch* touch, Event* event) {
		auto target = static_cast<Button*>(event->getCurrentTarget());
		return true;
	};
	pauseListener->onTouchEnded = [=](Touch* touch, Event* event) {
		auto target = static_cast<Button*>(event->getCurrentTarget());

		pressPause();
	};
	*/
	//////////////////////////question setting

	questionLabel = Label::createWithTTF("0", "fonts/chinese_font.ttf", 30);
	pinLabel = Label::createWithTTF("", "fonts/chinese_font.ttf", 20);

	questionLabel->setPosition(visibleSize.width/2,CONV_Y(185));
	pinLabel->setPosition(10, -30);
	pinLabel->setName("pin");

	addChild(questionLabel);
	questionLabel->addChild(pinLabel);
	///////////////////////////answer Setting

	Button* ansBtns[BUTTON_NUM];

	for (int i = 0; i < BUTTON_NUM; i++)
	{
		ansBtns[i] = Button::create("button.png");
		ansLabel[i] = Label::createWithTTF("", "fonts/chinese_font.ttf", 30.0f, Size(141, 141), TextHAlignment::CENTER, TextVAlignment::CENTER);
		ansLabel[i]->setPosition(ansBtns[i]->getContentSize().width / 2, ansBtns[i]->getContentSize().height / 2); 
	}

	ansBtns[0]->setPosition(ccp(110, CONV_Y(482)));
	ansBtns[1]->setPosition(ccp(343, CONV_Y(482)));
	ansBtns[2]->setPosition(ccp(110, CONV_Y(670)));
	ansBtns[3]->setPosition(ccp(343, CONV_Y(670)));

	for (int i = 0; i < BUTTON_NUM; i++)
	{
		ansBtns[i]->addTouchEventListener(CC_CALLBACK_2(GameScene::touchEvent, this));
		ansLabel[i]->setName("label");

		ansBtns[i]->addChild(ansLabel[i]);
		ansBtns[i]->setName("answer button");
		ansBtns[i]->setTag(i);
		ansBtns[i]->setZoomScale(0.0f);

		addChild(ansBtns[i]);
	}

	update();

	//////////////////////////////////
	clearNum = 0;

	scheduleUpdate();

	//////////////////////////
	return true;
}
void GameScene::touchEvent(Ref* pSender, Widget::TouchEventType type)
{
	auto clickedButton = (Button*)pSender;
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
		if (clickedButton->getTag() == currentAnsIndex)
			correct();
		else
			uncorrect();
		
		break;
	}
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
}

void GameScene::correct()
{
	ScoreManager::getInstance()->setScore(ScoreManager::getInstance()->getScore() + 10);
	scoreLabel->setString(StringUtils::format("%d", ScoreManager::getInstance()->getScore()));

	update();
	setTimerPercent(timer->getPercentage() + 10.0f);
}

void GameScene::uncorrect()
{
	setTimerPercent(timer->getPercentage() - 10.0f);
	Device::vibrate(0.1f);
}

void GameScene::update()
{
	size_t currentDataIndex = random(0, dataManager.getDataSize() - 1);	//현재 낸 문제의 인덱스 값
	int questionType = random(0, 1);	//if(questionType == 0), question = Chinese;

	currentAnsIndex = random(0, BUTTON_NUM-1);

	MirrorData md = dataManager.getDataByIndex(currentDataIndex);

	if (questionType == 0)
	{
		questionLabel->setString(md.chinese);
		pinLabel->setString(md.pinyin);

		//////// set answer
		ansLabel[currentAnsIndex]->setString(md.kor);
		for (int i = 0; i < BUTTON_NUM; i++)
			if (i != currentAnsIndex)
			{
				int r_index = dataManager.getRandomIndexExceptParam(currentDataIndex);
				ansLabel[i]->setString(dataManager.getKorByIndex(r_index));
			}
	}
	else
	{
		questionLabel->setString(md.kor);
		pinLabel->setString("");
		
		//////// set answer
		ansLabel[currentAnsIndex]->setString(md.chinese);
		for (int i = 0; i < BUTTON_NUM; i++)
			if (i != currentAnsIndex)
			{
				int r_index = dataManager.getRandomIndexExceptParam(currentDataIndex);
				ansLabel[i]->setString(dataManager.getChineseByIndex(r_index));
			}
	}
	//updateQuestion();
	//updateAnswer();
}
void GameScene::setTimerPercent(float percent)
{
	timer->stopAllActions();

	timer->setPercentage(percent);

	auto *progressToZero = ProgressFromTo::create(fTime*(percent / 100.0f), percent, 0);
	auto gameOverAction = CallFuncN::create(CC_CALLBACK_0(GameScene::gameOver, this));

	timer->runAction(Sequence::create(progressToZero, gameOverAction, NULL));
}

void GameScene::pressPause()
{
	if (Director::getInstance()->isPaused())
	{
		Director::getInstance()->resume();
		_eventDispatcher->setEnabled(true);
	}
	else
	{
		Director::getInstance()->pause();
		_eventDispatcher->setEnabled(false);
	}
}

void GameScene::update(float dt)
{
}

void GameScene::goHome(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
}

void GameScene::gameOver()
{
	Director::getInstance()->replaceScene(TransitionZoomFlipX::create(2.0f, GameOverScene::createScene(),
		TransitionScene::Orientation::LEFT_OVER));
}
