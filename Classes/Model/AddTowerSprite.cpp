#include "AddTowerSprite.h"

AddTowerSprite* AddTowerSprite::createATSWithSpriteFrameName(const char* name){
	AddTowerSprite* ats = new AddTowerSprite();
	if(ats&&ats->initWithSpriteFrameName(name)){
		ats->autorelease();
	}
	return ats;
}

bool AddTowerSprite::ccTouchBegan(CCTouch* touch,CCEvent* event){
	(beganTarget->*beganSelector)(this);
	this->getParent()->removeChild(this);
	return false;
}