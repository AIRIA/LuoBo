#ifndef _BATTLESCENE_H_
#define _BATTLESCENE_H_
#include "../BaseScene.h"
#include "../Assets.h"
#include "../Model/RouteInfo.h"

class BattleScene:public BaseScene{
public:
	CCArray* towersInfo;
	CCArray* routeInfo;
	CCLayer* battleLayer;
public:
	virtual void onEnter();
	static BattleScene* createWithThemeIdx();
	CREATE_FUNC(BattleScene);
	virtual bool init();
	void setTopBar();
	void setControlMenu();
	void start();
	void playeGuide();
	void loadMap();
	void openGameMenu(CCObject* pSender);
	void cutSpeed(CCObject* pSender);
	void setTowerLayer();
	void initAnimations();
	void showTowerLocation();
	void countDown(CCObject* pSender,void* sprname);
	void removeTarget(CCObject* pSender,void* obj);
	void removeStartLayer(CCObject* pSender,void* obj);
	void initBatchNodeLayers();
	void startMonsterThread(float dt);
};

#endif