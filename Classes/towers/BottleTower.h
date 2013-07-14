#ifndef _BOTTLETOWER_H_
#define _BOTTLETOWER_H_

#include "BaseTower.h"

class BottleTower:public BaseTower{
public:
	virtual void fire(float dt=0);
	CREATE_TOWER(BottleTower);
};

#endif