#include "TowerManager.h"

CCMenu* TowerManager::createTowerList(string towerTypes[]){
	string towerName[] = {"Bottle","Fan","Shit"};
	CCMenu* towerMenu = CCMenu::create();
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
	return towerMenu;
}


BaseTower* TowerManager::createSelectTower(const char* towerType){

	return 0;
}