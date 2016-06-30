#include "HelloWorldScene.h"

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(180, 170, 160, 255)))
    {
        return false;
    }

	auto visibleSize = Director::getInstance()->getVisibleSize();
	createNumbers(visibleSize);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void HelloWorld::createNumbers(Size screenSize) {
	int len = (screenSize.width - 20) / 4 - 10;
	int startY = ((screenSize.height - len * 4) - 10) / 2;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			auto number = Number::create(2, Size(len, len), Point(Vec2(20 + i*(len + 10), startY + j*(len + 10))), Color3B::MAGENTA);
			number->setPosition(Vec2(10 + i*(len + 10), startY + j*(len + 10)));

			addChild(number);
		}
	}
}

bool HelloWorld::onTouchBegan(Touch* t, Event* e) {
	touchStart = t->getLocation();
	return true;
}

void HelloWorld::onTouchEnded(Touch* t, Event* e) {
	touchEnd = t->getLocation();
	float disX = touchEnd.x - touchStart.x;
	float disY = touchEnd.y - touchStart.y;

	if (abs(disX) > abs(disY)) {
		this->doMove(disX > 0 ? DIRECT_RIGHT : DIRECT_LEFT);
	}
	else {
		this->doMove(disY > 0 ? DIRECT_UP : DIRECT_DOWN);
	}

}

void HelloWorld::doMove(int direction) {
	log("direction %d", direction);
}