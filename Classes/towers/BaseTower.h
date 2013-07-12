#ifndef _BASETOWER_H_
#define _BASETOWER_H_

#include "../Components/GiantSprite.h"

using namespace std;

class BaseTower:public GiantSprite{
public:
	/**
	   炮塔类型
	 */
	string towerType;
	/**
	   炮塔等级
	*/
	int towerLevel;
	/**
	   是否可以升级
	*/
	bool upgradable;
	/**
		攻击力
	*/
	int atk;
	/**
		攻击速度
	*/
	int attackSpeed;
	/**
		攻击范围
	*/
	int attackDistance;
public:
	BaseTower():attackDistance(160){};
	virtual void attack();
	virtual void findMonster();
	virtual void fire();
	virtual void upgrade();
	static BaseTower* createBaseTower(const char* tower);
	virtual bool ccTouchBegan(CCTouch* touch,CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch,CCEvent* event);
};

#endif