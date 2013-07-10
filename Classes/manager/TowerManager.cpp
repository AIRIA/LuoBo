#include "TowerManager.h"
#include "../Components/TowerMenuItemSprite.h"
#include "../Components/BaseTowerSpriteBatchNode.h"
#include "../ShareManager.h"

CCPoint TowerManager::towerPoint = CCPointZero;
CCArray* TowerManager::towerBatches = CCArray::createWithCapacity(5);

CCMenu* TowerManager::createTowerList(string towerTypes[]){
	
	string towerName[] = {"Bottle","Fan","Shit"};
	CCMenu* towerMenu = CCMenu::create();
	towerMenu->ignoreAnchorPointForPosition(true);
	CCArray* batches = CCArray::create();
	towerBatches = batches;
	//在这里加载炮塔信息 
	CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	string itemName;
	string towerType;
	for(int i=0;i<3;i++){
		towerType = towerName[i];
		itemName = towerName[i]+"01.png";
		towerName[i] = "T"+towerName[i]+"-hd.plist";
		towerName[i] = "Themes/Towers/"+towerName[i];
		frameCache->addSpriteFramesWithFile(towerName[i].c_str());
		CCSprite* towerNormal = CCSprite::createWithSpriteFrameName(itemName.c_str());
		BaseTowerSpriteBatchNode* btsbn = BaseTowerSpriteBatchNode::createBatchNode(towerNormal->getTexture());
		btsbn->towerType = towerType;
		towerBatches->addObject(btsbn);
		ShareManager::getInstance()->battleScene->addChild(btsbn);
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
	CCARRAY_FOREACH(towerBatches,batchNode){
		BaseTowerSpriteBatchNode* btsbn = (BaseTowerSpriteBatchNode*)batchNode;
		string targetType = btsbn->towerType;
		string selectType = towerType;
		if(targetType == selectType){
			//炮塔底座
			CCSprite* base = CCSprite::createWithSpriteFrameName((targetType+"-11.png").c_str());
			GiantSprite* tower = GiantSprite::creatGSWithSpriteFrameName((targetType+"11.png").c_str());
			base->setPosition(towerPoint);
			tower->setPosition(towerPoint);
			btsbn->addChild(base);
			btsbn->addChild(tower);
		}
	}
	return 0;
}