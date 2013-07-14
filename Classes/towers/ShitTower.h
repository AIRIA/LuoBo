#ifndef _SHITTOWER_H_
#define _SHITTOWER_H_

#include "BaseTower.h"

class ShitTower:public BaseTower{
public:
	CREATE_TOWER(ShitTower);
	virtual void fire(float dt=0);
	virtual void initTower();
	virtual void bulletSchedule(float dt);
	virtual void bangEffect();
};
#endif