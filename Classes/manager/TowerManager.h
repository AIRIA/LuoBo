#ifndef _TOWERMANAGER_H_
#define _TOWERMANAGER_H_

#include "../towers/BaseTower.h"

class TowerManager{
public:
	static CCPoint towerPoint;
	static CCArray* towerBatches;
public:
	
	/**
	创建可以供玩家选择的炮塔
	*/
	static CCMenu* createTowerList(string towerTypes[]);

	/**
	选择了炮塔类型后 创建一个炮塔在地图上
	*/
	static BaseTower* createSelectTower(const char* towerType);

	/**
	初始化炮塔需要的动画
	*/
	static void loadAnimation(const char* towerName);

	/**
	根据类型创建炮塔
	*/
	static BaseTower* getTower(const char* towerType);
};

#endif