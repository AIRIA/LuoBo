#ifndef _GIANTSPRITE_H_
#define _GIANTSPRITE_H_

#include "cocos2d.h"

USING_NS_CC;
class GiantSprite:public CCSprite,public CCTargetedTouchDelegate{
protected:
	CCObject* beganTarget;
	SEL_MenuHandler beganSelector;
	CCObject* endTarget;
	SEL_MenuHandler endSelector;

public:
	GiantSprite():beganTarget(NULL),endTarget(NULL){};
	static GiantSprite* creatGSWithSpriteFrameName(const char* name);
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch* touch,CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch,CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch,CCEvent* event);
	
	bool isContainPoint(CCTouch* touch);
	void setTargetBegan(CCObject* target,SEL_MenuHandler selector){
		beganTarget = target;
		beganSelector = selector;
	};

	void setTargetEnd(CCObject* target,SEL_MenuHandler selector){
		endTarget = target;
		endSelector = selector;
	};

};

#endif