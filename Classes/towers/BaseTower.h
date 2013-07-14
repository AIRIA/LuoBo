#ifndef _BASETOWER_H_
#define _BASETOWER_H_

#include "../Components/GiantSprite.h"
#include "../manager/AnimateManager.h"
#include "../Model/Monster.h"

using namespace std;

#define CREATE_TOWER(className) \
	static className* className::createTower(const char* tower){ \
		string towerName = tower; \
		towerName = towerName+"11.png"; \
		className* instance = new className(); \
		if(instance&&instance->initWithSpriteFrameName(towerName.c_str())){ \
			instance->autorelease(); \
			instance->schedule(schedule_selector(className::fire),1.0f); \
			instance->schedule(schedule_selector(className::bulletSchedule)); \
			instance->initTower(); \
		} \
		return instance; \
	} 

class BaseTower:public GiantSprite{
protected:
	/**
	是否寻找到了怪物
	*/
	bool isFinded;
	/**
	子弹的名字
	*/
	string bulletName;
	CCSprite* bullet;

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

	/**
	瞄准的怪物
	*/
	Monster* targetMonster;

	
	/**

	*/
	CCAnimationCache* animateCache;
	CCSpriteFrameCache* frameCache;
	AnimateManager* animateManager;
public:
	BaseTower():attackDistance(160),isFinded(false),towerLevel(1),targetMonster(NULL){
		animateCache = CCAnimationCache::sharedAnimationCache();
		frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
		animateManager = AnimateManager::shareAnimateManager();
	};
	virtual void attack();
	virtual void findMonster();
	virtual void fire(float dt = 0) = 0;
	virtual void upgrade();
	/**
	子弹的移动和侦测
	*/
	virtual void bulletSchedule(float dt) = 0;
	/**
	子弹碰到怪物显示的效果
	*/
	virtual void bangEffect() = 0;
	virtual bool ccTouchBegan(CCTouch* touch,CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch,CCEvent* event);
	virtual void initTower() = 0;
};

#endif