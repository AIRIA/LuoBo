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
	bool isTower;
	//当前主题ID
	int currentThemeId;
	//当前地图ID
	int mapId;
	ShareManager():currentThemeId(1),mapId(1),isTower(false){};
	static ShareManager* getInstance();
	//怪物所在的BatchNode
	MonsterSpriteBatch* monsterBatchNode;
	//空气爆炸效果BatchNode
	CCSpriteBatchNode* cloudBatchNode;
	//子弹BatchNode
	CCSpriteBatchNode* bulletBatchNode;
	//炮塔层
	TowerLayer* towerLayer;
	Carrot* carrot;
	//战斗场景实例
	BattleScene* battleScene;
	CCSprite* bossHp;
	//怪物数组
	CCArray* monsters;

	CCArray* getRouteInfo();
	void setTowersInfo(CCArray* towersInfo);
	CCArray* getTowersInfo();
	void setRouteInfo(CCArray* routeInfo);
	//对路线进行排序
	void orderRouteInfo();
	//
	bool containTouchPoint(CCPoint &point);
};

#endif