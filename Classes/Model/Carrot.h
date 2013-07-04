#ifndef _CARROT_H_
#define _CARROT_H_

#include "cocos2d.h"
#include "../manager/AnimateManager.h"
USING_NS_CC;

class Carrot:public CCNode{

public:
	CCArray* actions;
	CCSprite* carrot;
	CCSprite* carrotShade;
	AnimateManager* animateManager;
	CCAnimationCache* animationCache;
public:
	CREATE_FUNC(Carrot);
	virtual bool init();
	void doRandomAction(float dt);
	void resetToOrigin();
};

#endif