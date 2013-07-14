#ifndef _BASETOWER_H_
#define _BASETOWER_H_

#include "../Components/GiantSprite.h"

using namespace std;

#define CREATE_TOWER(className) \
	static className* className::createTower(const char* tower){ \
		string towerName = tower; \
		towerName = towerName+"11.png"; \
		className* instance = new className(); \
		if(instance&&instance->initWithSpriteFrameName(towerName.c_str())){ \
			instance->autorelease(); \
		} \
		instance->schedule(schedule_selector(className::fire)); \
		return instance; \
	} 

class BaseTower:public GiantSprite{
protected:
	/**
	是否寻找到了怪物
	*/
	bool isFinded;

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
	BaseTower():attackDistance(160),isFinded(false){};
	virtual void attack();
	virtual void findMonster();
	virtual void fire(float dt = 0) = 0;
	virtual void upgrade();
	virtual bool ccTouchBegan(CCTouch* touch,CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch,CCEvent* event);
};

#endif