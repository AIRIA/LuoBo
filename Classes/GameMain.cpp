#include "GameMain.h"
#include "Assets.h"
#include "VisibleRect.h"
#include "BaseScene.h"
#include "MainScenes\SettingScene.h"
#include "MainScenes\HelpScene.h"
#include "SceneManager.h"

enum{
	kLeaf2
};

CCScene* GameMain::scene(){
	CCScene* mainScene = CCScene::create();
	GameMain* game = GameMain::create();
	mainScene->addChild(game);
	return mainScene;
}

GameMain::GameMain(){
	winSize = CCDirector::sharedDirector()->getWinSize();
}

bool GameMain::init(){
	if(!CCLayer::init()){
		return false;
	}
	CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	frameCache->addSpriteFramesWithFile((sceneDir+"mainscene1-hd.plist").c_str());
	CCSpriteBatchNode* mainSceneBatch = CCSpriteBatchNode::createWithTexture(SPRITE(mainbg.png)->getTexture());
	
	addChild(mainSceneBatch);
	//背景图片
	CCSprite* mainBg = SPRITE(mainbg.png);
	CCPoint centerPoint = ccp(winSize.width/2,winSize.height/2);
	mainBg->setPosition(centerPoint);
	mainSceneBatch->addChild(mainBg);

	//云彩
	CCSprite* cloud1 = SPRITE(cloud1.png);
	CCSprite* cloud2 = SPRITE(cloud2.png);
	cloud1->setPosition(ccp(-100,winSize.height-100));
	cloud2->setPosition(ccp(-500,winSize.height-200));
	CCActionInterval* cloud1Move = CCMoveTo::create(70,ccp(1700,winSize.height-100));
	CCActionInterval* cloud2Move = CCMoveTo::create(70,ccp(1300,winSize.height-200));
	cloud1->runAction(cloud1Move);
	cloud2->runAction(cloud2Move);
	cloud1->setColor(ccWHITE);
	cloud2->setColor(ccWHITE);
	ccBlendFunc bf = {GL_ONE, GL_ONE_MINUS_SRC_ALPHA};
	mainSceneBatch->setBlendFunc(bf);
	cloud1->setBlendFunc(bf);
	cloud2->setBlendFunc(bf);
	mainSceneBatch->addChild(cloud1);
	mainSceneBatch->addChild(cloud2);
	carrotNode = CCNode::create();

	//萝卜
	CCSprite* carrot = SPRITE(carrot.png);
	carrot->setAnchorPoint(ccp(0.5,0));
	carrot->setPosition(CCPointZero);
	CCPoint leafPoint = ccp(0,carrot->getContentSize().height-50);
	//leaf
	CCSprite* carrotLeaf1 = SPRITE(leaf-1.png);
	CCSprite* carrotLeaf2 = SPRITE(leaf-2.png);
	CCSprite* carrotLeaf3 = SPRITE(leaf-3.png);
	carrotLeaf1->setAnchorPoint(ccp(1,0));
	carrotLeaf2->setAnchorPoint(ccp(0.5,0));
	carrotLeaf3->setAnchorPoint(ccp(0,0));

	carrotLeaf1->setPosition(leafPoint);
	carrotLeaf2->setPosition(leafPoint);
	carrotLeaf3->setPosition(leafPoint);
	carrotNode->addChild(carrotLeaf1);
	carrotNode->addChild(carrotLeaf3);
	carrotNode->addChild(carrotLeaf2);
	carrotNode->addChild(carrot);
	carrotNode->setPosition(ccp(centerPoint.x,centerPoint.y-50));
	carrotNode->setScale(0);
	CCActionInterval* scaleAction = CCScaleTo::create(0.3,1,1);
	CCActionInterval* delayRun = CCDelayTime::create(0.3);
	CCSequence* carrotNodeSeq = CCSequence::create(delayRun,scaleAction,NULL);
	
	addChild(carrotNode);
	//Logo图片
	CCSprite* mainBg_CN = SPRITE(mainbg_CN.png);
	mainBg_CN->setPosition(centerPoint);
	addChild(mainBg_CN);
	CCSprite* bird = SPRITE(bird.png);
	bird->setPosition(ccp(VisibleRect::leftTop().x+200,VisibleRect::leftTop().y-150));
	CCActionInterval* birdUp = CCMoveBy::create(2,ccp(0,35));
	CCActionInterval* birdDown = birdUp->reverse();
	CCSequence* birdAction = CCSequence::create(birdUp,birdDown,NULL);
	bird->runAction(CCRepeatForever::create(birdAction));
	mainSceneBatch->addChild(bird);
	
	//冒险模式 Boss模式 宠物窝
	CCMenuItemSprite* adventureMode = CCMenuItemSprite::create(SPRITE(btn_adventure_normal_CN.png),
		SPRITE(btn_adventure_pressed_CN.png),SceneManager::shareSceneManager(),menu_selector(SceneManager::toAdventureScene));
	CCMenuItemSprite* bossMode = CCMenuItemSprite::create(SPRITE(btn_boss_normal_CN.png),
		SPRITE(btn_boss_pressed_CN.png));
	CCMenuItemSprite* nest = CCMenuItemSprite::create(SPRITE(btn_nest_normal_CN.png),
		SPRITE(btn_nest_pressed_CN.png));

	CCMenu* mainMenu = CCMenu::create(adventureMode,bossMode,nest,NULL);
	mainMenu->alignItemsHorizontallyWithPadding(20);
	mainMenu->setPosition(ccp(VisibleRect::center().x,VisibleRect::bottom().y+100));
	addChild(mainMenu);

	
	//设置和帮助菜单
	CCMenuItemSprite* settingBtn = CCMenuItemSprite::create(SPRITE(btn_setting_normal.png),SPRITE(btn_setting_pressed.png),
		SceneManager::shareSceneManager(),menu_selector(SceneManager::toSettingScene));
	CCMenuItemSprite* helpBtn = CCMenuItemSprite::create(SPRITE(btn_help_normal.png),SPRITE(btn_help_pressed.png),
		SceneManager::shareSceneManager(),menu_selector(SceneManager::toHelpScene));
	CCMenu* setMenu = CCMenu::create(settingBtn,helpBtn,NULL);
	setMenu->alignItemsHorizontallyWithPadding(450);
	setMenu->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y-95));
	addChild(setMenu);
	//萝卜叶子的动画
	CCActionInterval* shake = CCRotateBy::create(0.1,10);
	CCActionInterval* shakeBack = shake->reverse();
	CCActionInterval* nextDelay = CCDelayTime::create(3);
	CCActionInterval* repeatDelay = CCDelayTime::create(1);
	CCCallFunc* callBack = CCCallFunc::create(this,callfunc_selector(GameMain::shakeLeaf));
	CCSequence* shakeSeq = CCSequence::create(shake,shakeBack,shake,shakeBack,nextDelay,callBack,repeatDelay,NULL);
	carrotLeaf2->setTag(kLeaf2);
	carrotNode->runAction(carrotNodeSeq);
	carrotLeaf3->runAction(CCRepeatForever::create(shakeSeq));

	BaseScene* bs = BaseScene::create();

	return true;
}

void GameMain::shakeLeaf(){
	CCActionInterval* shake = CCRotateBy::create(0.1,10);
	CCActionInterval* shakeBack = shake->reverse();
	CCSprite* carrotLeaf2 = (CCSprite*)carrotNode->getChildByTag(kLeaf2);
	carrotLeaf2->runAction(CCSequence::create(shake,shakeBack,shake,shakeBack,NULL));
}