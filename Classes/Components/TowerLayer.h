#ifndef _TOWERLAYER_H_
#define _TOWERLAYER_H_
#include "cocos2d.h"

USING_NS_CC;
class TowerLayer:public CCLayer{
public:
	virtual void registerWithTouchDispatcher();
	virtual bool init();
	CREATE_FUNC(TowerLayer);
	virtual bool ccTouchBegan(CCTouch* touch,CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch,CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch,CCEvent* event);
	CCPoint convertToTouchInfo(CCTouch* touch);
	void addTower(CCPoint &point);
};

#endif