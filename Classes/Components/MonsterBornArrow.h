#ifndef _MONSTERBORNARROW_H_
#define _MONSTERBORNARROW_H_

#include "cocos2d.h"
#include "../ShareManager.h"
USING_NS_CC;

class MonsterBornArrow:public CCNode{
public:
	virtual bool init();
	virtual void onEnter();
	CREATE_FUNC(MonsterBornArrow);
	int getArrowDirection();
};

#endif