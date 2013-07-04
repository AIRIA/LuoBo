#include "AnimateManager.h"



AnimateManager* AnimateManager::_instance = NULL;

AnimateManager* AnimateManager::shareAnimateManager(){
	if(!_instance){
		_instance = new AnimateManager();
		_instance->animationCache = CCAnimationCache::sharedAnimationCache();
		_instance->frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	}
	return _instance;
}

void AnimateManager::createAnimation(const char* animateName,string prevStr,int start,int end,float fps){
	CCArray* frames = CCArray::create();
	for(int i=start;i<=end;i++){
		string format;
		if(i<10){
			format = prevStr+"0%d.png";
		}else{
			format = prevStr+"%d.png";
		}
		CCString* sprName = CCString::createWithFormat(format.c_str(),i);
		CCSpriteFrame* spriteFrame = frameCache->spriteFrameByName(sprName->getCString());
		frames->addObject(spriteFrame);
		CCLog(sprName->getCString());
	}
	CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames,1.0/fps);
	animationCache->addAnimation(animation,animateName);
}