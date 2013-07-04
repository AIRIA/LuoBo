#ifndef _TOWERINFO_H_
#define  _TOWERINFO_H_
#include "cocos2d.h"

USING_NS_CC;

class TowerInfo:public CCObject{
public:
	CCPoint location;
	virtual bool init();
	CREATE_FUNC(TowerInfo);
};

#endif