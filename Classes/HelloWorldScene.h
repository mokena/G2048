#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Number.h"
USING_NS_CC;

class HelloWorld : public cocos2d::LayerColor
{
private:
	static const int DIRECT_UP = 1;
	static const int DIRECT_DOWN = 2;
	static const int DIRECT_LEFT = 3;
	static const int DIRECT_RIGHT = 4;
	static const int LINE_NUMBER_COUNT = 4;

	Vec2 touchStart;
	Vec2 touchEnd;
	Number* numbers[LINE_NUMBER_COUNT][LINE_NUMBER_COUNT];
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	bool onTouchBegan(Touch* t, Event* e);
	void onTouchEnded(Touch* t, Event* e);

	void doMove(int direction);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void createNumbers(Size screenSize);
	void randomCreateNumber();
	boolean isGameOver();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
