#ifndef _ADDTOWERSPRITE_H_
#define _ADDTOWERSPRITE_H_

#include "../Components/GiantSprite.h"

class AddTowerSprite:public GiantSprite{
public:
	static AddTowerSprite* createATSWithSpriteFrameName(const char* name);
	virtual bool ccTouchBegan(CCTouch* touch,CCEvent* event);
};

#endif