#ifndef _ROUTEINFO_H_
#define _ROUTEINFO_H_

#include "cocos2d.h"
using namespace std;
USING_NS_CC;

class RouteInfo:public CCObject{
public:
	CCPoint routePoint;
	string pointName;
	CREATE_FUNC(RouteInfo);
	virtual bool init();
};

#endif