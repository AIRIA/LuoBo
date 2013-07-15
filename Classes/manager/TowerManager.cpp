#include "TowerManager.h"
#include "../Components/TowerMenuItemSprite.h"
#include "../Components/BaseTowerSpriteBatchNode.h"
#include "../ShareManager.h"
#include "../towers/BaseTower.h"
#include "../manager/AnimateManager.h"

#include "../towers/BottleTower.h"
#include "../towers/ShitTower.h"

CCPoint TowerManager::towerPoint = CCPointZero;
CCArray* TowerManager::towerBatches = CCArray::createWithCapacity(5);

#define TOWER_FPS 12

void TowerManager::loadAnimation(const char* towerName){
	AnimateManager* am = AnimateManager::shareAnimateManager();
	string lv = towerName;
	string lv1 = lv+"1";
	string lv2 = lv+"2";
	string lv3 = lv+"3";
	am->createAnimation(lv1.c_str(),towerName,11,13,TOWER_FPS);
	am->createAnimation(lv2.c_str(),towerName,21,23,TOWER_FPS);
	am->createAnimation(lv3.c_str(),towerName,31,33,TOWER_FPS);
}

CCMenu* TowerManager::createTowerList(string towerTypes[]){
	
	string towerName[] = {"Bottle","Fan","Shit","Rocket"};
	CCMenu* towerMenu = CCMenu::create();
	towerMenu->ignoreAnchorPointForPosition(true);
	CCArray* batches = CCArray::create();
	towerBatches = batches;
	//在这里加载炮塔信息 
	CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	string itemName;
	string towerType;
	for(int i=0;i<4;i++){
		
		towerType = towerName[i];
		itemName = towerName[i]+"01.png";
		towerName[i] = "T"+towerName[i]+"-hd.plist";
		towerName[i] = "Themes/Towers/"+towerName[i];
		frameCache->addSpriteFramesWithFile(towerName[i].c_str());
		loadAnimation(towerType.c_str());
		CCSprite* towerNormal = CCSprite::createWithSpriteFrameName(itemName.c_str());
		BaseTowerSpriteBatchNode* btsbn = BaseTowerSpriteBatchNode::createBatchNode(towerNormal->getTexture());
		btsbn->towerType = towerType;
		towerBatches->addObject(btsbn);
		ShareManager::getInstance()->battleScene->battleLayer->addChild(btsbn);
		TowerMenuItemSprite* towerItem = TowerMenuItemSprite::createTower(towerNormal,towerNormal);
		towerItem->towerType = towerType;
		towerMenu->addChild(towerItem);
	}
	towerMenu->alignItemsHorizontallyWithPadding(0);
	towerMenu->retain();
	towerMenu->setContentSize(CCSizeMake(240,80));
	towerBatches->retain();
	return towerMenu;
}


BaseTower* TowerManager::createSelectTower(const char* towerType){
	CCObject* batchNode = NULL;
	BaseTower* tower = NULL;
	CCARRAY_FOREACH(towerBatches,batchNode){
		BaseTowerSpriteBatchNode* btsbn = (BaseTowerSpriteBatchNode*)batchNode;
		string targetType = btsbn->towerType;
		string selectType = towerType;
		if(targetType == selectType){
			//炮塔底座
			CCSprite* base = CCSprite::createWithSpriteFrameName((targetType+"-11.png").c_str());
			tower = getTower(targetType.c_str());
			tower->towerType = targetType;
			base->setPosition(towerPoint);
			tower->setPosition(towerPoint);
			btsbn->addChild(base);
			btsbn->addChild(tower);
			tower->setTouchPriority(-130);
			CCSprite* air = AnimateManager::shareAnimateManager()->createAnimate_RunOnce("air11.png","air_tower");
			ShareManager::getInstance()->cloudBatchNode->addChild(air);
			air->setPosition(towerPoint);
		}
	}
	return tower;
}
#include "../towers/FanTower.h"
#include "../towers/RoketTower.h"
BaseTower* TowerManager::getTower(const char* towerType){
	string tt = towerType;
	BaseTower* bt = NULL;
	if(tt=="Bottle"){
		bt = BottleTower::createTower(towerType);
	}else if(tt=="Shit"){
		bt = ShitTower::createTower(towerType);
	}else if(tt=="Fan"){
		bt = FanTower::createTower(towerType);
	}else if(tt=="Rocket"){
		bt = RoketTower::createTower(towerType);
	}
	return bt;
}