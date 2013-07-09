#ifndef _GUN_H_
#define _GUN_H_

#include "../Components/GiantSprite.h"

using namespace std;

class Gun:public GiantSprite{
public:
	/**
	  枪式炮塔类型
	 */
	string towerType;

	int towerLevel;
public:
	void attack();
};

#endif