﻿#include "TowerLayer.h"
#include "../Assets.h"
#include "../VisibleRect.h"
#include "../ShareManager.h"
#include "../Model/AddTowerSprite.h"

/**
  缩放效果的时间
*/
#define EFF_TIME 0.3
#define TOWER_SIZE 80

void TowerLayer::showTowerMenu(CCPoint &point){
	isShow = true;
	if(towerMenu->isRunning()==false){
		addChild(towerMenu);
	}
	
	CCActionInterval* scaleIn = CCScaleTo::create(EFF_TIME,1);
	CCObject* item = NULL;
	CCArray* items = towerMenu->getChildren();
	int childCount = towerMenu->getChildrenCount();
	CCSize size = CCSizeMake(childCount*TOWER_SIZE,TOWER_SIZE);
	int tx,ty;
	if(point.x==(TOWER_SIZE/2)){
		tx = size.width/2 + TOWER_SIZE/2;
	}else if(point.x==(VisibleRect::right().x-TOWER_SIZE/2)){
		tx = VisibleRect::right().x - size.width/2 - TOWER_SIZE/2;	
	}else{
		tx = point.x;
	}

	if(point.y/TOWER_SIZE <4){
		ty = point.y+TOWER_SIZE;
	}else{
		ty = point.y-TOWER_SIZE;
	}
	towerMenu->setPosition(ccp(tx,ty));

	CCARRAY_FOREACH(items,item){
		CCMenuItemSprite* mis = (CCMenuItemSprite*)item;
		mis->setScale(0);
		mis->runAction((CCActionInterval*)scaleIn->copy());
	}
	
}

void TowerLayer::onEnter(){
	isShow = false;
	string towerName[] = {"Bottle","Fan","Shit"};
	towerMenu = CCMenu::create();
	towerMenu->ignoreAnchorPointForPosition(true);
	//在这里加载炮塔信息
	CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	string itemName;
	for(int i=0;i<3;i++){
		itemName = towerName[i]+"01.png";
		towerName[i] = "T"+towerName[i]+"-hd.plist";
		towerName[i] = "Themes/Towers/"+towerName[i];
		frameCache->addSpriteFramesWithFile(towerName[i].c_str());
		CCMenuItemSprite* towerItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(itemName.c_str()),
			CCSprite::createWithSpriteFrameName(itemName.c_str()));
		towerMenu->addChild(towerItem);
	}
	towerMenu->alignItemsHorizontallyWithPadding(0);
	towerMenu->retain();
	towerMenu->setContentSize(CCSizeMake(240,80));
	CCSize size = towerMenu->getContentSize();
	CCLayer::onEnter();
}


void TowerLayer::registerWithTouchDispatcher(){
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,1,true);
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
	if(isShow){
		hideTowerMenu();
		return false;
	}
	CCPoint touchPoint = convertToTouchInfo(touch);
	if(ShareManager::getInstance()->containTouchPoint(touchPoint)){
		AddTowerSprite* addTowerSpr = AddTowerSprite::createATSWithSpriteFrameName("select_00.png");//SPRITE(select_00.png);
		//addTowerSpr->setTargetBegan(this,menu_selector(TowerLayer::hideTowerMenu));
		addTowerSpr->setPosition(touchPoint);
		addChild(addTowerSpr);
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName("addTower");
		CCAnimate* animate = CCAnimate::create(animation);
		addTowerSpr->runAction(CCRepeatForever::create(animate));
		showTowerMenu(touchPoint);
	}else{
		CCSprite* forbidden = SPRITE(Fan01.png);
		forbidden->setPosition(touchPoint);
		CCActionInterval* fadeOut = CCFadeOut::create(EFF_TIME);
		forbidden->runAction(fadeOut);
		addChild(forbidden);
		hideTowerMenu();
	}
	
	return true;
}

void TowerLayer::addTower(CCPoint &point){

}

void TowerLayer::ccTouchEnded(CCTouch* touch,CCEvent* event){

}

void TowerLayer::ccTouchMoved(CCTouch* touch,CCEvent* event){

}


void TowerLayer::hideTowerMenu(CCObject* pSender){
	isShow = false;
	CCActionInterval* scaleIn = CCScaleTo::create(0.3,0);
	CCObject* item = NULL;
	CCArray* items = towerMenu->getChildren();
	CCARRAY_FOREACH(items,item){
		CCMenuItemSprite* mis = (CCMenuItemSprite*)item;
		mis->runAction((CCActionInterval*)scaleIn->copy());
	}
	CCSize size = towerMenu->getContentSize();
}