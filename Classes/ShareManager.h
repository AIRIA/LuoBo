#ifndef _SHAREMANAGER_H_
#define _SHAREMANAGER_H_
#include "cocos2d.h"
#include "Components\MonsterSpriteBatch.h"
#include "Model\Carrot.h"

USING_NS_CC;

class ShareManager{
protected:
	static ShareManager* _instance;
	CCArray* routeInfo;
public:
	int currentThemeId;
	int mapId;
	ShareManager():currentThemeId(1),mapId(1){};
	static ShareManager* getInstance();
	MonsterSpriteBatch* monsterBatchNode;
	CCSpriteBatchNode* cloudBatchNode;
	CCSpriteBatchNode* bulletBatchNode;
	CCSpriteBatchNode* towerBatchNode;
	Carrot* carrot;
	CCSprite* bossHp;
	
	CCArray* getRouteInfo();
	void setRouteInfo(CCArray* routeInfo);
};

#endif