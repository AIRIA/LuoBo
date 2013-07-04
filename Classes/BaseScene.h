#ifndef _BASE_SCENE_H_
#define _BASE_SCENE_H_
#include "cocos2d.h"

USING_NS_CC;
class BaseScene:public CCScene{
protected:
	CCSpriteFrameCache* frameCache;
public:
	virtual bool init();
	CREATE_FUNC(BaseScene);
};

#endif