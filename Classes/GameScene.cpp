#include "GameScene.h"
#include "CSVParser.h"
#include "base\ccUTF8.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "ScoreManager.h"

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
	if(!Layer::init())
		return false;

	ssize_t bufferSize = 0;
	string getData = FileUtils::getInstance()->getStringFromFile("english_db.csv");

	if (getData != "")
	{
		CSVParser::getInstance()->convertToMap(getData.substr(0,10000));
	}

	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto game_back = Sprite::create("game_background.png");
	game_back->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(game_back,-10);

	toggle = Sprite::create("toggle.png");

	toggle->setPosition(Vec2(240,visibleSize.height-570));
	
	toggleOriginVec = toggle->getPosition();

	
	addChild(toggle, 1);
	

	/////////////////////////////////////////////////
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

	for (int i = 0; i < 4; i++)
	{
		crossLabels[i] = LabelTTF::create("", "fonts/font.ttf", 20);
	}
	updateCross();

	crossLabels[mDirection::TOP]->setPosition(690, 540 - 100);
	
	crossLabels[mDirection::LEFT]->setPosition(545, 540 - 250);

	crossLabels[mDirection::BOTTOM]->setPosition(690, 540 - 438);
	
	crossLabels[mDirection::RIGHT]->setPosition(845, 540 - 250);

	for (int i = 0; i < 4; i++)
		addChild(crossLabels[i],3);
	
	////////////////////////////////// score setting
	scoreLabel = LabelTTF::create("0", "fonts/font.ttf", 50);

	scoreLabel->setPosition(Vec2(800, 540 - 40));
	scoreLabel->setColor(Color3B::BLACK);

	addChild(scoreLabel);

	///////////////////////////////////// timer

	timer = ProgressTimer::create(Sprite::create("timer.png"));

	
	timer->setPercentage(100.0f);
	timer->setType(ProgressTimer::Type::BAR);
	timer->setBarChangeRate(Vec2(1,0));
	timer->setMidpoint(Vec2(0, 1));
	timer->setPosition(visibleSize.width*0.5, 500.0f);

	fTime = 20.0f;			//제한시간 30초

	setTimerPercent(100.0f);

	addChild(timer, 5);

	///////////////////////////////////// pause_button

	auto pauseBtn = Button::create("pause.png");

	pauseBtn->setZoomScale(0.7f);
	pauseBtn->setPosition(Vec2(890, 540 - 474));

	//addChild(pauseBtn);
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
	
	//////////////////////////////////
	clearNum = 0;

	scheduleUpdate();
	return true;
}
void GameScene::touchEvent(Ref* pSender, Widget::TouchEventType type)
{
	auto toggle = ((GameScene*)pSender)->toggle;

	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;

	case Widget::TouchEventType::MOVED:
		break;

	case Widget::TouchEventType::ENDED:
		break;

	case Widget::TouchEventType::CANCELED:
		break;

	default:
		break;
	}
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode,Event * event)
{
}

void GameScene::updateCross()
{
	int r = RandomHelper::random_int<int>(0, 3);

	crossLabels[r]->setString(currentCorrect);

	correctDir = r;

	CSVParser* inst = CSVParser::getInstance();

	for (int i = 0; i < 4; i++)
	{
		if (i != r)
		{
			if (currentCorrectType == 0) //정답이 현재 영어면
				crossLabels[i]->setString(inst->getRandomKorExceptParam(currentCorrect).c_str());
			else                       //한국어면
				crossLabels[i]->setString(inst->getRandomEngExceptParam(currentCorrect).c_str());
		}
	}
}

void GameScene::update()
{
	
	if (++clearNum % 3 == 0)
	{
		fTime -= 0.5f;
	}
	ScoreManager::getInstance()->setScore(ScoreManager::getInstance()->getScore() + 10);
	scoreLabel->setString(StringUtils::format("%d", ScoreManager::getInstance()->getScore()));

	//if (listView->getChildren().empty()) return;

	//listViewUpdate();

	updateCross();
}

void GameScene::listViewUpdate()
{
	/*
	auto p = CSVParser::getInstance()->getRandomPair();

	auto item = (listView->getItem(0));

	LabelTTF* label = static_cast<LabelTTF*>(item->getChildByName("target"));
	
	listView->removeItem(0);

	item = (listView->getItem(0));

	label = static_cast<LabelTTF*>(item->getChildByName("target"));

	label->setOpacity(255);

	if (label->getTag() == 0) //현재 문제가 영어면
	{
		currentCorrect = CSVParser::getInstance()->getKorAnswer(label->getString());
		currentCorrectType = 0;
	}
	else                     //문제가 한국어면
	{
		currentCorrect = CSVParser::getInstance()->getEngAnswer(label->getString());
		currentCorrectType = 1;
	}
	addRandomStringInListView();
	*/
}

void GameScene::addRandomStringInListView(bool isTop)
{
	auto parserInst = CSVParser::getInstance();
	Layout *custom_item = Layout::create();

	auto p = parserInst->getRandomPair();

	int r = RandomHelper::random_int<int>(0, 1);

	LabelTTF* label;

	if (r == 0)
	{
		label = LabelTTF::create(p.first, "fonts/font.ttf", 50);
		label->setTag(0);	//영어면 라벨에 0을태그
	}
	else
	{
		label = LabelTTF::create(p.second, "fonts/font.ttf", 50);
		label->setTag(1);
	}
	if (isTop)
	{
		if (r == 0)
		{
			currentCorrect = p.second;
			currentCorrectType = 0;
		}
		else
		{
			currentCorrect = p.first;
			currentCorrectType = 1;
		}
	}
	else
	{
		label->setOpacity(50);
	}
	label->setColor(Color3B::BLACK);
	label->setName("target");

	custom_item->setContentSize(label->getContentSize());
	label->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, custom_item->getContentSize().height / 2.0f));

	custom_item->addChild(label);

	//listView->addChild(custom_item);
}

void GameScene::completePush(mDirection d)
{
	if (bUpdateOnce) return;

	if (d == correctDir)	//정답일 경우
	{
		update();
		setTimerPercent(timer->getPercentage() + 5.0f);
	}
	else
	{
			setTimerPercent(timer->getPercentage() - 10.0f);
			Device::vibrate(0.1f);
	}
	bUpdateOnce = true;
}
void GameScene::setTimerPercent(float percent)
{
	timer->stopAllActions();

	timer->setPercentage(percent);

	auto *progressToZero = ProgressFromTo::create(fTime*(percent/100.0f), percent, 0);
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
	if (timer->getPercentage() <= 0)
	{
		gameOver();
		unscheduleUpdate();
	}
}

void GameScene::goHome(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
}

void GameScene::gameOver()
{
	Director::getInstance()->replaceScene(TransitionZoomFlipX::create(2.0f, GameOverScene::createScene(),
		TransitionScene::Orientation::LEFT_OVER));
}
