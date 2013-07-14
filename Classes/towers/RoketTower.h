#ifndef _ROKETTOWER_H_
#define _ROKETTOWER_H_
#include "BaseTower.h"

class RoketTower:public BaseTower{
public:
	CREATE_TOWER(RoketTower);
	virtual void fire(float dt);
}; 

#endif