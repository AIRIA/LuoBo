#ifndef _ANIMATEMANAGER_H_
#define _ANIMATEMANAGER_H_

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class AnimateManager{
private:
	static AnimateManager* _instance;
	CCAnimationCache* animationCache;
	CCSpriteFrameCache* frameCache;
public:
	static AnimateManager* shareAnimateManager();
	void createAnimation(const char* animateName,string prevStr,int start,int end,float fps);
};

#endif