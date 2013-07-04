#ifndef _MAPMENU_H_
#define _MAPMENU_H_

#include "cocos2d.h"
USING_NS_CC;

class MapMenu:public CCLayer{
public:
	CREATE_FUNC(MapMenu);
	virtual bool init();
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch* touch,CCEvent* event);
};

#endif