#ifndef _ASSETS_H_
#define _ASSETS_H_
#include "cocos2d.h"
USING_NS_CC;
#define SPRITE(url) CCSprite::createWithSpriteFrameName(#url)
#define GET_ANIMATE(name) CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName(#name))

#include <string>
using namespace std;

static const string sceneDir = "Themes/scene/";
static const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
static int selectThemeId;


#endif