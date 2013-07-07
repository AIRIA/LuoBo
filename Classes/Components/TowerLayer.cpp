#include "TowerLayer.h"
#include "../Assets.h"
#include "../VisibleRect.h"
#include "../ShareManager.h"

void TowerLayer::registerWithTouchDispatcher(){
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);
}

bool TowerLayer::init(){
	do{
		CC_BREAK_IF(!CCLayer::init());
		setTouchEnabled(true);
	}while(0);
	return true;
}

CCPoint TowerLayer::convertToTouchInfo(CCTouch* touch){
	CCPoint touchPoint = touch->getLocation();

	float cellPosX = int(touchPoint.x) % 80;
	float cellPosY = int(touchPoint.y) % 80;
	int row = touchPoint.y / 80;
	int col = touchPoint.x / 80;
	if(cellPosX!=0){
		row++;
	}
	if(cellPosY!=0){
		col++;
	}
	return ccp(col*80-40,row*80-40);
}

bool TowerLayer::ccTouchBegan(CCTouch* touch,CCEvent* event){
	removeAllChildren();
	CCPoint touchPoint = convertToTouchInfo(touch);
	if(ShareManager::getInstance()->containTouchPoint(touchPoint)){
		CCSprite* addTowerSpr = SPRITE(select_00.png);
		addTowerSpr->setPosition(touchPoint);
		addChild(addTowerSpr);
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName("addTower");
		CCAnimate* animate = CCAnimate::create(animation);
		addTowerSpr->runAction(CCRepeatForever::create(animate));
	}else{
		CCSprite* forbidden = SPRITE(forbidden.png);
		forbidden->setPosition(touchPoint);
		CCActionInterval* fadeOut = CCFadeOut::create(0.5);
		forbidden->runAction(fadeOut);
		addChild(forbidden);
	}
	
	return true;
}

void TowerLayer::addTower(CCPoint &point){

}

void TowerLayer::ccTouchEnded(CCTouch* touch,CCEvent* event){

}

void TowerLayer::ccTouchMoved(CCTouch* touch,CCEvent* event){

}