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
	int len = (screenSize.width - 20) / LINE_NUMBER_COUNT - 10;
	int startY = ((screenSize.height - len * LINE_NUMBER_COUNT) - 10) / 2;

	for (int i = 0; i < LINE_NUMBER_COUNT; i++) {
		for (int j = 0; j < LINE_NUMBER_COUNT; j++) {
			auto number = Number::create(2, Size(len, len), Point(Vec2(20 + i*(len + 10), startY + j*(len + 10))), Color3B::MAGENTA);
			number->setPosition(Vec2(10 + i*(len + 10), startY + j*(len + 10)));

			numbers[i][j] = number;
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
	switch (direction) {
	case DIRECT_RIGHT:
		moveRight();
		break;
	case DIRECT_LEFT:
		moveLeft();
		break;
	case DIRECT_UP:
		moveUp();
		break;
	case DIRECT_DOWN:
		moveDown();
		break;
	default:
		break;
	}
}

void HelloWorld::moveLeft() {
	//move every number to the most left, until get combined or the end
	for (int j = 0; j < LINE_NUMBER_COUNT; j++) {
		int end = 0;
		for (int i = 0; i < LINE_NUMBER_COUNT; i++) {
			for (int n = i; n > end; n--) {
				if (numbers[n - 1][j]->getNumber() == 0) {
					numbers[n - 1][j]->setNumber(numbers[n][j]->getNumber());
					numbers[n][j]->setNumber(0);
				}
				else if (numbers[n - 1][j]->getNumber() == numbers[n][j]->getNumber()) {
					numbers[n - 1][j]->setNumber(numbers[n - 1][j]->getNumber() + numbers[n][j]->getNumber());
					numbers[n][j]->setNumber(0);
					end = i;
					break;
				}
			}
		}
	}
}
void HelloWorld::moveRight() {
	//move every number to the most right, until get combined or the end
	for (int j = 0; j < LINE_NUMBER_COUNT; j++) {
		int end = LINE_NUMBER_COUNT - 1;
		for (int i = LINE_NUMBER_COUNT - 1; i >= 0; i--) {
			for (int n = i; n < end; n++) {
				if (numbers[n + 1][j]->getNumber() == 0) {
					numbers[n + 1][j]->setNumber(numbers[n][j]->getNumber());
					numbers[n][j]->setNumber(0);
				}
				else if (numbers[n + 1][j]->getNumber() == numbers[n][j]->getNumber()) {
					numbers[n + 1][j]->setNumber(numbers[n + 1][j]->getNumber() + numbers[n][j]->getNumber());
					numbers[n][j]->setNumber(0);
					end = i;
					break;
				}
			}
		}
	}
}
void HelloWorld::moveUp() {
	//move every number to the most up, until get combined or the end
	for (int i = 0; i < LINE_NUMBER_COUNT; i++) {
		int end = LINE_NUMBER_COUNT - 1;
		for (int j = LINE_NUMBER_COUNT - 1; j >= 0; j--) {
			for (int n = j; n < end; n++) {
				if (numbers[i][n + 1]->getNumber() == 0) {
					numbers[i][n + 1]->setNumber(numbers[i][n]->getNumber());
					numbers[i][n]->setNumber(0);
				}
				else if (numbers[i][n + 1]->getNumber() == numbers[i][n]->getNumber()) {
					numbers[i][n + 1]->setNumber(numbers[i][n + 1]->getNumber() + numbers[i][n]->getNumber());
					numbers[i][n]->setNumber(0);
					end = j;
					break;
				}
			}
		}
	}
}
void HelloWorld::moveDown() {
	//move every number to the most down, until get combined or the end
	for (int i = 0; i < LINE_NUMBER_COUNT; i++) {
		int end = 0;
		for (int j = 0; j < LINE_NUMBER_COUNT; j++) {
			for (int n = j; n > end; n--) {
				if (numbers[i][n - 1]->getNumber() == 0) {
					numbers[i][n - 1]->setNumber(numbers[i][n]->getNumber());
					numbers[i][n]->setNumber(0);
				}
				else if (numbers[i][n - 1]->getNumber() == numbers[i][n]->getNumber()) {
					numbers[i][n - 1]->setNumber(numbers[i][n - 1]->getNumber() + numbers[i][n]->getNumber());
					numbers[i][n]->setNumber(0);
					end = j;
					break;
				}
			}
		}
	}
}