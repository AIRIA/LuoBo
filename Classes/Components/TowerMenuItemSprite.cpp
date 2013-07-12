#include "TowerMenuItemSprite.h"
#include "../manager/TowerManager.h"
#include "../ShareManager.h"

TowerMenuItemSprite* TowerMenuItemSprite::createTower(CCNode* normalSprite, CCNode* selectedSprite){
	TowerMenuItemSprite* tmis = new TowerMenuItemSprite();
	if(tmis&&tmis->initWithNormalSprite(normalSprite,selectedSprite,NULL,tmis,menu_selector(TowerMenuItemSprite::createSelectTower))){
		tmis->autorelease();
	}
	return tmis;
}

void TowerMenuItemSprite::createSelectTower(CCObject* pSender){
	TowerManager::createSelectTower(towerType.c_str());
	ShareManager::getInstance()->towerLayer->hideTowerMenu();
}