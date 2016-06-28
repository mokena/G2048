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
    if ( !Layer::init() )
    {
        return false;
    }

	auto number = Number::create(2, Size(100, 100), Point(Vec2(50, 50)), Color3B::MAGENTA);
	addChild(number);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
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