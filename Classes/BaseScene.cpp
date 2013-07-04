#include "BaseScene.h"

bool BaseScene::init(){
	CCDirector::sharedDirector()->purgeCachedData();
	if(!CCScene::init()){
		return false;
	}
	frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	frameCache->removeUnusedSpriteFrames();
	return true;
}