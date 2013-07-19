#include "BattleScene.h"
#include "../VisibleRect.h"
#include "../Components/MapMenu.h"
#include "../ShareManager.h"
#include "../Model/TowerInfo.h"
#include "../manager/AnimateManager.h"
#include "../Model/Carrot.h"
#include "../Components/MonsterBornArrow.h"
#include "../Model/Monster.h"
#include "../manager/MonsterManager.h"

using namespace std;

#define CREATE_ANIMATE(name,pre,start,end,fps) \
	AnimateManager::shareAnimateManager()->createAnimation(#name,#pre,start,end,fps)

void BattleScene::countDown(CCObject* pSender,void* sprname){
	char* sprName = (char*)sprname;
	if(sprName=="stop")
		return;
	CCSprite* spr = CCSprite::createWithSpriteFrameName((char*)sprname);
	CCActionInterval* scaleAct = CCScaleTo::create(1,0);
	CCCallFuncND* countdown = CCCallFuncND::create(this,callfuncND_selector(BattleScene::countDown),sprname);

}

void BattleScene::removeTarget(CCObject* pSender,void* obj){
	CCSprite* node = (CCSprite*)pSender;
	
	//node->setDisplayFrame(frameCache->spriteFrameByName());
	CCNode* parent = node->getParent();
	parent->removeChild(node,true);

	CCNode* count = (CCNode*)obj;
	if(count==NULL){
		return;
	}
	count->setPosition(VisibleRect::center());
	count->setScale(0);
	parent->addChild(count);
}

#define T_DELAY 0.8
#define T_SCALE 0.2

void BattleScene::start(){
	//开始倒计时
	CCLayer* startLayer = CCLayer::create();
	CCSprite* countBg = SPRITE(countdown_11.png);
	CCSprite* rotateFire = SPRITE(countdown_12.png);
	CCSprite* count1 = SPRITE(countdown_01.png);
	CCSprite* count2 = SPRITE(countdown_02.png);
	CCSprite* count3 = SPRITE(countdown_03.png);
	CCSprite* go = SPRITE(countdown_13.png);
	count1->setPosition(VisibleRect::center());
	count1->setScale(0);
	CCActionInterval* scaleAct = CCScaleTo::create(T_SCALE,1);
	CCCallFuncND* scaleCall = CCCallFuncND::create(this,callfuncND_selector(BattleScene::removeTarget),count2);
	CCSequence* scaleSeq = CCSequence::create(scaleAct,CCDelayTime::create(T_DELAY),scaleCall,NULL);
	CCActionInterval* rotate = CCRotateBy::create(1,-360);
	addChild(startLayer);
	
	rotateFire->setPosition(VisibleRect::center());
	countBg->setPosition(VisibleRect::center());
	startLayer->addChild(countBg);
	startLayer->addChild(rotateFire);
	startLayer->addChild(count1);
	rotateFire->runAction(CCRepeat::create(rotate,3));
	count1->runAction(scaleSeq);
	CCCallFuncND* count2Call = CCCallFuncND::create(this,callfuncND_selector(BattleScene::removeTarget),count3);
	CCCallFuncND* count3Call = CCCallFuncND::create(this,callfuncND_selector(BattleScene::removeTarget),go);
	
	count2->runAction(CCSequence::create(CCScaleTo::create(T_SCALE,1),CCDelayTime::create(T_DELAY),count2Call,NULL));
	count3->runAction(CCSequence::create(CCScaleTo::create(T_SCALE,1),CCDelayTime::create(T_DELAY),count3Call,NULL));
	CCSpawn* rotateScale = CCSpawn::create(CCScaleTo::create(T_SCALE,1),CCRotateBy::create(T_SCALE,-360),NULL);
	CCCallFuncND* goCall = CCCallFuncND::create(this,callfuncND_selector(BattleScene::removeStartLayer),startLayer);
	go->runAction(CCSequence::create(rotateScale,goCall,NULL));
}

void BattleScene::removeStartLayer(CCObject* pSender,void* obj){
	CCLayer* layer = (CCLayer*)obj;
	CCCallFunc* cf = CCCallFunc::create(this,callfunc_selector(BattleScene::showTowerLocation));
	layer->runAction(CCSequence::create(CCDelayTime::create(0.3),CCScaleTo::create(0.2,2,0),cf,NULL));
}
#define FADE_TIME 0.5
//添加可放置tower的提示位置
void BattleScene::showTowerLocation(){
	CCSpriteBatchNode* towerLoc = CCSpriteBatchNode::createWithTexture(SPRITE(select_00.png)->getTexture());
	ccBlendFunc cbf = {GL_ONE,GL_ONE_MINUS_SRC_ALPHA}; 
	towerLoc->setBlendFunc(cbf);
	CCObject* towerObj = NULL;
	addChild(towerLoc);
	CCARRAY_FOREACH(towersInfo,towerObj){
		TowerInfo* towerInfo = (TowerInfo*)towerObj;
		CCActionInterval* tintTo = CCTintTo::create(FADE_TIME,0,0,0);
		CCSprite* towerTip = SPRITE(select_00.png);
		towerTip->setColor(ccWHITE);
		towerTip->setPosition(towerInfo->location);
		towerLoc->addChild(towerTip);
		CCActionInterval* delay = CCDelayTime::create(FADE_TIME);
		CCActionInterval* fadeOut = CCFadeOut::create(FADE_TIME);
		CCActionInterval* fadeIn = CCFadeIn::create(FADE_TIME);
		CCSpawn* outScene = CCSpawn::createWithTwoActions(tintTo,fadeOut);
		CCSpawn* inScene = CCSpawn::createWithTwoActions(CCTintTo::create(FADE_TIME,255,255,255),fadeIn);
		
		/*CCSequence* fadeSeq = CCSequence::create(delay,,NULL);*/
		towerTip->runAction(CCRepeat::create(CCSequence::create(inScene,outScene,NULL),5));
	}
	schedule(schedule_selector(BattleScene::startMonsterThread),1.5);
}
int monsterNum = 0;
void BattleScene::startMonsterThread(float dt){
	if(monsterNum<10){
		monsterNum++;
		Monster::createWithMonsterName("fly_blue02.png","fat_green");
	}else{
		monsterNum = 0;
		unschedule(schedule_selector(BattleScene::startMonsterThread));
	}
	
}

void BattleScene::onEnter(){
	BaseScene::onEnter();
	start();
}

int mapId;
int themeId;
int blockSize = 80;

BattleScene* BattleScene::createWithThemeIdx(){
	themeId = ShareManager::getInstance()->currentThemeId;
	mapId = ShareManager::getInstance()->mapId;
	BattleScene* bs = BattleScene::create();
	return bs;
}

bool BattleScene::init(){
	if(!BaseScene::init()){
		return false;
	}
	ShareManager::getInstance()->battleScene = this;
	CCString* mapUrl = CCString::createWithFormat("Themes/Theme%d/",themeId);
	CCString* route = CCString::createWithFormat("Themes/Theme%d/BG%d/BG-hd.plist",themeId,mapId);
	frameCache->addSpriteFramesWithFile("Themes/scene/gamemenu-hd.plist");
	frameCache->addSpriteFramesWithFile("Themes/Items/Items02-hd.plist");
	frameCache->addSpriteFramesWithFile("Themes/Items/Items01-hd.plist");
	frameCache->addSpriteFramesWithFile("Themes/Items/Items00-hd.plist");
	frameCache->addSpriteFramesWithFile("Themes/scene/darkbg-hd.plist");
	frameCache->addSpriteFramesWithFile("Themes/scene/weibo-hd.plist");
	frameCache->addSpriteFramesWithFile(route->getCString());
	loadMap();
	initAnimations();
	//顶层菜单背景
	setTopBar();
	setControlMenu();
	setTowerLayer();
	initBatchNodeLayers();
	return true;
}

void BattleScene::setTopBar(){
	CCSprite* menuBg = SPRITE(MenuBG.png);
	menuBg->setPosition(ccp(VisibleRect::top().x,VisibleRect::top().y-40));
	addChild(menuBg);
}
//设置控件菜单
void BattleScene::setControlMenu(){
	//打开菜单选择
	CCMenuItemSprite* list = CCMenuItemSprite::create(SPRITE(menu01.png),SPRITE(menu02.png),
		this,menu_selector(BattleScene::openGameMenu));
	//暂停和开始
	CCMenuItemSprite* pause = CCMenuItemSprite::create(SPRITE(pause01.png),SPRITE(pause02.png));
	CCMenuItemSprite* play = CCMenuItemSprite::create(SPRITE(pause11.png),SPRITE(pause12.png));
	CCMenuItemToggle* control = CCMenuItemToggle::createWithTarget(this,menu_selector(BattleScene::cutSpeed),pause,play,NULL);
	//游戏速度
	CCMenuItemSprite* speed1 = CCMenuItemSprite::create(SPRITE(speed11.png),SPRITE(speed12.png));
	CCMenuItemSprite* speed2 = CCMenuItemSprite::create(SPRITE(speed21.png),SPRITE(speed22.png));
	CCMenuItemToggle* cutSpeed = CCMenuItemToggle::createWithTarget(this,menu_selector(BattleScene::cutSpeed),speed1,speed2,NULL);

	CCMenu* gameMenu = CCMenu::create(cutSpeed,control,list,NULL);
	gameMenu->alignItemsHorizontallyWithPadding(0);
	gameMenu->setPosition(ccp(VisibleRect::rightTop().x-150,VisibleRect::top().y - 40));
	addChild(gameMenu);
	CCSprite* monsterCN = SPRITE(MenuCenter_01_CN.png);
	monsterCN->setPosition(ccp(VisibleRect::top().x,VisibleRect::top().y-40));
	addChild(monsterCN);

	//当前round all round标签
	CCLabelAtlas* allRound = CCLabelAtlas::create("./0123456789","Themes/Items/numwhite-hd.png",20,40,'.');
	CCLabelAtlas* currentRound = CCLabelAtlas::create("./0123456789","Themes/Items/clock_num-hd.png",18,30,'.');
	currentRound->setString("0 1");
	allRound->setString("15");
	currentRound->setPosition(ccp(VisibleRect::top().x-110,VisibleRect::top().y - 45));
	allRound->setPosition(ccp(VisibleRect::top().x-15,VisibleRect::top().y - 50));
	addChild(currentRound);
	addChild(allRound);

}

//设置tower所在的层
void BattleScene::setTowerLayer(){
	
}

void BattleScene::cutSpeed(CCObject* pSender){
	CCScheduler* timeSchedule = CCDirector::sharedDirector()->getScheduler();
	CCMenuItemToggle* speedCut = (CCMenuItemToggle*)pSender;
	if(speedCut->getSelectedIndex()==0){
		timeSchedule->setTimeScale(1);
		ShareManager::getInstance()->moveSpeed /= 1.5;
	}else{
		timeSchedule->setTimeScale(1.5);
		ShareManager::getInstance()->moveSpeed *= 1.5;
	}
}

void BattleScene::loadMap(){
	
	towersInfo = CCArray::create();
	routeInfo = CCArray::create();
	ShareManager::getInstance()->setRouteInfo(routeInfo);
	//load tmx file for tile map
	CCString* mapUrl = CCString::createWithFormat("Themes/Theme%d/BG%d/BGPath.tmx",themeId,mapId);
	CCTMXTiledMap* gameMap = CCTMXTiledMap::create(mapUrl->getCString());
	CCDictionary* props = gameMap->getProperties();
	//base on style property to choose which background to load and show
	int type = ((CCString*)props->objectForKey("style"))->intValue();
	CCString* mapBg = CCString::createWithFormat("Themes/Theme%d/BG0/BG%d-hd.plist",themeId,type);
	frameCache->addSpriteFramesWithFile(mapBg->getCString());
	CCSprite* bgSpr;
	if(type==1){
		bgSpr = SPRITE(BG1.png);
	}else{
		bgSpr = SPRITE(BG2.png);
	}
	bgSpr->setPosition(VisibleRect::center());
	addChild(bgSpr);

	//load route background image
	ccBlendFunc bf = {GL_ONE, GL_ONE_MINUS_SRC_ALPHA};
	CCSprite* routeSpr = SPRITE(Path.png);
	routeSpr->setPosition(VisibleRect::center());
	routeSpr->setBlendFunc(bf);
	addChild(routeSpr);
	
	CCString* items = CCString::createWithFormat("Themes/Theme%d/Items/Object0%d-hd.plist",themeId,type);
	CCString* monster = CCString::createWithFormat("Themes/Theme%d/Items/Monsters0%d-hd.plist",themeId,type);
	
	frameCache->addSpriteFramesWithFile(items->getCString());
	frameCache->addSpriteFramesWithFile(monster->getCString());
	CCSpriteBatchNode* cloudSpriteBatch = CCSpriteBatchNode::createWithTexture(SPRITE(cloud01.png)->getTexture());
	addChild(cloudSpriteBatch);
	//analyse objgroup to get detail info and set items and tower placeholder
	CCTMXObjectGroup* objGroup = gameMap->objectGroupNamed("PATH");
	CCDictionary* dicInfo = NULL;
	CCObject* obj = NULL;
	CCArray* objs = objGroup->getObjects();
	CCARRAY_FOREACH(objs,obj){
		dicInfo = (CCDictionary*)obj;
		if(!dicInfo){
			break;
		}
		int x,y,width,height;
		x = ((CCString*)dicInfo->objectForKey("x"))->intValue();
		y = ((CCString*)dicInfo->objectForKey("y"))->intValue();
		width = ((CCString*)dicInfo->objectForKey("width"))->intValue();
		height = ((CCString*)dicInfo->objectForKey("height"))->intValue();
		string objName = ((CCString*)dicInfo->objectForKey("name"))->getCString();
		//在此处放置障碍物
		if(objName[1] == 'O'){
			char sprId = objName[0];
			std::string spr(1,sprId);
			std::string sprName = "cloud0"+spr+".png";
			CCSprite* sprItem = CCSprite::createWithSpriteFrameName(sprName.c_str());
			sprItem->setPosition(ccp(x+width/2,y+height/2));
			cloudSpriteBatch->addChild(sprItem);
		}else if(objName[0] == 'O'){//load tower place infomation
			int col = width/blockSize;
			int row = height/blockSize;
			for(int i=0;i<row;i++){
				for(int j=0;j<col;j++){
					int ix = x+j*blockSize;
					int iy = y+i*blockSize;
					TowerInfo* ti = TowerInfo::create();
					ti->location = ccp(ix+blockSize/2,iy+blockSize/2);
					towersInfo->addObject(ti);
				}
			}
		}else if(objName[0] == 'P'){
			//get route infomation
			RouteInfo* ri = RouteInfo::create();
			ri->pointName = objName;
			ri->routePoint = ccp(x+blockSize/2,y-blockSize/2);
			routeInfo->addObject(ri);
		}
	}
	addChild(gameMap);
	towersInfo->retain();
	ShareManager::getInstance()->setTowersInfo(towersInfo);
	ShareManager::getInstance()->orderRouteInfo();
	routeInfo = ShareManager::getInstance()->getRouteInfo();
	//monster born place
	CCObject* routeObj = NULL;
	int routeCount = routeInfo->count();
	CCString* lastCountPtName = CCString::createWithFormat("PT%d",routeCount-1);
	CCString* numPoint = CCString::createWithFormat("PT%d",routeCount);
	CCARRAY_FOREACH(routeInfo,routeObj){
		RouteInfo* currentRI = (RouteInfo*)routeObj;
		if(currentRI->pointName == "PT1"){
			MonsterBornArrow* mba = MonsterBornArrow::create();
			mba->getArrowDirection();
			mba->setPosition(currentRI->routePoint);
			addChild(mba);
			CCSprite* startLoc = SPRITE(start01.png);
			startLoc->setAnchorPoint(ccp(0.5,0));
			startLoc->setPosition(currentRI->routePoint);
			addChild(startLoc);
			
			
		}else if(currentRI->pointName == lastCountPtName->getCString()){
			ShareManager::getInstance()->carrot = Carrot::create();
			ShareManager::getInstance()->carrot->ignoreAnchorPointForPosition(false);
			ShareManager::getInstance()->carrot->setPosition(currentRI->routePoint);
			addChild(ShareManager::getInstance()->carrot);
		}else if(currentRI->pointName == numPoint->getCString()){
			CCSprite* bossHp = SPRITE(BossHP10.png);
			ShareManager::getInstance()->bossHp = bossHp;
			bossHp->setPosition(ccp(currentRI->routePoint.x,currentRI->routePoint.y+40));
			addChild(bossHp);
		}
	}
	

}
//open game menu contains resume restart and quit
void BattleScene::openGameMenu(CCObject* pSender){
	MapMenu* mm = MapMenu::create();
	
	addChild(mm);
}
#define MONSTER_FPS 4

//initial animations
void BattleScene::initAnimations(){
	CREATE_ANIMATE(air_monster,air,11,15,10);
	CREATE_ANIMATE(air_carrot,air,21,25,10);
	CREATE_ANIMATE(air_tower,air,11,15,10);
	CREATE_ANIMATE(air_tower,air,11,15,10);
	CREATE_ANIMATE(addTower,select_,1,4,8);
	CREATE_ANIMATE(boss_big,boss_big,1,2,MONSTER_FPS);
	CREATE_ANIMATE(fat_boss_green,fat_boss_green,1,2,MONSTER_FPS);
	CREATE_ANIMATE(fat_green,fat_green,1,2,MONSTER_FPS);
	CREATE_ANIMATE(fly_blue,fly_blue,1,2,MONSTER_FPS);
	CREATE_ANIMATE(fly_boss_blue,fly_boss_blue,1,2,MONSTER_FPS);
	CREATE_ANIMATE(fly_boss_yellow,fly_boss_yellow,1,2,MONSTER_FPS);
	CREATE_ANIMATE(fly_yellow,fly_yellow,1,2,MONSTER_FPS);
	CREATE_ANIMATE(land_boss_nima,land_boss_nima,1,2,MONSTER_FPS);
	CREATE_ANIMATE(land_boss_pink,land_boss_pink,1,2,MONSTER_FPS);
	CREATE_ANIMATE(land_boss_star,land_boss_star,1,2,MONSTER_FPS);
	CREATE_ANIMATE(land_nima,land_nima,1,2,MONSTER_FPS);
	CREATE_ANIMATE(land_pink,land_pink,1,2,MONSTER_FPS);
	CREATE_ANIMATE(land_star,land_star,1,2,MONSTER_FPS);
	
}

void BattleScene::initBatchNodeLayers(){
	ShareManager* sm = ShareManager::getInstance();
	battleLayer = CCLayer::create();
	//sm->bulletBatchNode = CCSpriteBatchNode::createWithTexture(frameCache->spriteFrameByName());
	sm->monsterBatchNode = MonsterSpriteBatch::createBatchNodeWithTexture(frameCache->spriteFrameByName("fly_blue01.png")->getTexture());
	sm->cloudBatchNode = CCSpriteBatchNode::createWithTexture(frameCache->spriteFrameByName("air01.png")->getTexture());
	sm->towerLayer = TowerLayer::create();
	sm->bloodSpriteNode = CCSpriteBatchNode::createWithTexture(frameCache->spriteFrameByName("MonsterHP01.png")->getTexture());
	addChild(battleLayer);
	addChild(sm->monsterBatchNode);
	ccBlendFunc bf = {GL_ONE, GL_ONE_MINUS_SRC_ALPHA};
	sm->bloodSpriteNode->setBlendFunc(bf);
	addChild(sm->bloodSpriteNode);
	addChild(sm->cloudBatchNode);
	addChild(sm->towerLayer);
	CCLog("retainCount%d",sm->getRouteInfo()->retainCount());
}