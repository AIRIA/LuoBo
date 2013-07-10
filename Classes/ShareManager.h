#ifndef _SHAREMANAGER_H_
#define _SHAREMANAGER_H_
#include "cocos2d.h"
#include "Components\MonsterSpriteBatch.h"
#include "Model\Carrot.h"
#include "Components\TowerLayer.h"
#include "MainScenes\BattleScene.h"

USING_NS_CC;

class ShareManager{
protected:
	static ShareManager* _instance;
	CCArray* routeInfo;
	CCArray* towerInfo;
public:
	int currentThemeId;
	int mapId;
	ShareManager():currentThemeId(1),mapId(1){};
	static ShareManager* getInstance();
	MonsterSpriteBatch* monsterBatchNode;
	CCSpriteBatchNode* cloudBatchNode;
	CCSpriteBatchNode* bulletBatchNode;
	TowerLayer* towerLayer;
	Carrot* carrot;
	BattleScene* battleScene;
	CCSprite* bossHp;
	
	CCArray* getRouteInfo();
	void setTowersInfo(CCArray* towersInfo);
	CCArray* getTowersInfo();
	void setRouteInfo(CCArray* routeInfo);
	void orderRouteInfo();
	bool containTouchPoint(CCPoint &point);
};

#endif