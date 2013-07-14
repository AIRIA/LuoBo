#ifndef _FANTOWER_H_
#define _FANTOWER_H_

#include "BaseTower.h"

class FanTower:public BaseTower{
public:
	CREATE_TOWER(FanTower);
	virtual void fire(float dt);
	virtual void initTower();
	virtual void bulletSchedule(float dt);
	virtual void bangEffect();
};

#endif