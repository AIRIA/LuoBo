#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "cocos2d.h"
#include "../ShareManager.h"

USING_NS_CC;
class Monster:public CCSprite{
public:
	int currentPointIdx;
	int nextPointIdx;
	bool isShowHP;
public:
	
	CCSprite* monsterSpr;
	virtual bool init();
	Monster():isShowHP(false){};
	static void createWithMonsterName(const char* initFrame,const char* monsterName);
};

#endif