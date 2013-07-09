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
	bool upgradble;
	/**
		攻击力
	*/
	int atk;
	/**
	攻击速度
	*/
	int attackSpeed;
public:
	
};

#endif