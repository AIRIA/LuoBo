#ifndef _TOWERMENUITEMSPRITE_H_
#define _TOWERMENUITEMSPRITE_H_

#include "cocos2d.h"

USING_NS_CC;
using namespace std;
class TowerMenuItemSprite:public CCMenuItemSprite{
public:
	string towerType;
public:
	static TowerMenuItemSprite* createTower(CCNode* normalSprite, CCNode* selectedSprite);
	void createSelectTower(CCObject* pSender);
};

#endif