#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Number : public Sprite {
public:
	static Number* create(int num, Size size, Point pos, Color3B color);
	virtual bool init();
	
	int getNumber();
	void setNumber(int num);

	CREATE_FUNC(Number);

private:
	int number;
	Label* numberLabel;
	Color3B* bgColor;

	bool initWithArgs(int num, Size size, Point pos, Color3B color);
};
