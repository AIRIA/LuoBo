#ifndef _BOTTLETOWER_H_
#define _BOTTLETOWER_H_

#include "BaseTower.h"

class BottleTower:public BaseTower{
public:
	BottleTower(){
		BaseTower::atk = 13;
	};
	virtual void fire(float dt=0);
	CREATE_TOWER(BottleTower);
	virtual void creatBullte(CCNode* node);
	virtual void initTower();
	virtual void bulletSchedule(float dt);
	virtual void bangEffect();
};

#endif