#include "TowerLayer.h"
#include "../Assets.h"
#include "../VisibleRect.h"
#include "../ShareManager.h"

void TowerLayer::showTowerMenu(CCPoint &point){
	CCActionInterval* scaleIn = CCScaleTo::create(0.3,1);
	CCObject* item = NULL;
	CCArray* items = towerMenu->getChildren();
	CCARRAY_FOREACH(items,item){
		CCMenuItemSprite* mis = (CCMenuItemSprite*)item;
		mis->runAction((CCActionInterval*)scaleIn->copy());
	}
	CCSize size = towerMenu->getContentSize();
	addChild(towerMenu);
}

void TowerLayer::onEnter(){
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
		towerItem->setScale(1);
		towerMenu->addChild(towerItem);
	}
	towerMenu->alignItemsHorizontallyWithPadding(0);
	towerMenu->retain();
	towerMenu->setContentSize(CCSizeMake(240,80));
	addChild(towerMenu);
	CCObject* item = NULL;
	CCArray* items = towerMenu->getChildren();
	CCARRAY_FOREACH(items,item){
		CCMenuItemSprite* mis = (CCMenuItemSprite*)item;
		mis->setScale(0);
	}
	CCLayer::onEnter();
}


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
		showTowerMenu(touchPoint);
	}else{
		CCSprite* forbidden = SPRITE(Fan01.png);
		forbidden->setPosition(touchPoint);
		CCActionInterval* fadeOut = CCFadeOut::create(0.5);
		forbidden->runAction(fadeOut);
		addChild(forbidden);
		//hideTowerMenu();
	}
	
	return true;
}

void TowerLayer::addTower(CCPoint &point){

}

void TowerLayer::ccTouchEnded(CCTouch* touch,CCEvent* event){

}

void TowerLayer::ccTouchMoved(CCTouch* touch,CCEvent* event){

}


void TowerLayer::hideTowerMenu(){
	CCActionInterval* scaleIn = CCScaleTo::create(0.5,0);
	CCObject* item = NULL;
	CCArray* items = towerMenu->getChildren();
	CCARRAY_FOREACH(items,item){
		CCMenuItemSprite* mis = (CCMenuItemSprite*)item;
		mis->runAction((CCActionInterval*)scaleIn->copy());
	}
	CCSize size = towerMenu->getContentSize();
}