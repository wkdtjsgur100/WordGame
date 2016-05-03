#include "GameOverScene.h"
#include "ScoreManager.h"
#include "HelloWorldScene.h"

USING_NS_CC;
using namespace ui;

Scene * GameOverScene::createScene()
{
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameOverScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GameOverScene::init()
{
	if(!Layer::init())
		return false;

	auto back = Sprite::create("gameover_background.png");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	back->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));

	addChild(back,-10);

	auto label = Label::createWithTTF(StringUtils::format("%d", ScoreManager::getInstance()->getScore()).c_str(), "fonts/font.ttf", 50);

	label->setPosition(369, 400);
	label->setColor(Color3B::BLACK);

	this->addChild(label);

	auto homeBtn = Button::create("home.png");

	homeBtn->setZoomScale(0.7f);
	homeBtn->addTouchEventListener(CC_CALLBACK_2(GameOverScene::goHome, this));
	homeBtn->setPosition(Vec2(855, 540-455));

	this->addChild(homeBtn);

	return true;
}
void GameOverScene::goHome(Ref* pSender, Widget::TouchEventType type)
{
	ScoreManager::getInstance()->end();

	if (type == Widget::TouchEventType::ENDED) {
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	}
}
