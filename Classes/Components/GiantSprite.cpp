﻿#include "GiantSprite.h"

GiantSprite* GiantSprite::creatGSWithSpriteFrameName(const char* name){
	GiantSprite* gs = new GiantSprite();
	if(gs&&gs->initWithSpriteFrameName(name)){
		gs->autorelease();
	}
	return gs;
}

void GiantSprite::onEnter(){
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-1,true);
	CCSprite::onEnter();
}

void GiantSprite::onExit(){
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}

bool GiantSprite::isContainPoint(CCTouch* touch){
	CCPoint arPoint = getAnchorPointInPoints();
	CCPoint point = convertTouchToNodeSpaceAR(touch);
	CCSize spriteSize = getContentSize();
	CCRect spriteRect = CCRectMake(-arPoint.x,-arPoint.y,spriteSize.width,spriteSize.height);
	return spriteRect.containsPoint(point);
}

bool GiantSprite::ccTouchBegan(CCTouch* touch,CCEvent* event){
	if(isContainPoint(touch)&&beganTarget){
		(beganTarget->*beganSelector)(this);
		return true;
	}
	return false;
}

void GiantSprite::ccTouchMoved(CCTouch* touch,CCEvent* event){

}

void GiantSprite::ccTouchEnded(CCTouch* touch,CCEvent* event){
	if(endTarget){
		(endTarget->*endSelector)(this);
	}
}