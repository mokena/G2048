#include "Number.h"

Number* Number::create(int num, Size size, Point pos, Color3B color) {
	Number* number = new Number();

	if (number && number->init()) {
		number->initWithArgs(num, size, pos, color);
		number->autorelease();
		return number;
	}
	CC_SAFE_DELETE(number);
	return NULL;
}

bool Number::init() {
	return Sprite::init();
}

bool Number::initWithArgs(int num, Size size, Point pos, Color3B color) {
	number = num;

	setContentSize(size);
	setAnchorPoint(Point::ZERO);
	
	//draw background
	setTextureRect(Rect(0, 0, size.width, size.height));
	setColor(color);
	
	//draw number
	std::string str = "";
	if (number > 0) { str = __String::createWithFormat("%i", number)->getCString(); }
	
	numberLabel = Label::createWithSystemFont(str, "HiraKakuProN-W3", 100);
	numberLabel->setPosition(Vec2(size.width / 2, size.height / 2));
	addChild(numberLabel);

	return true;
}

int Number::getNumber() {
	return number;
}

void Number::setNumber(int num) {
	number = num;

	if (number > 0 && numberLabel) {
		numberLabel->setString(__String::createWithFormat("%i", number)->getCString());
	}
	else if (number <= 0) {
		numberLabel->setString(__String::createWithFormat("")->getCString());
	}
}

