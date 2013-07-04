#include "HelpScene.h"
#include "../Assets.h"
#include "../VisibleRect.h"
#include "../GameMain.h"
#include "../Components/GiantPageScrollView.h"
#include "../SceneManager.h"

void HelpScene::tabMenuHandler(CCObject* pSender){
	CCMenuItemSprite* sprMenu = (CCMenuItemSprite*)pSender;
	int zOrder = sprMenu->getZOrder();
	helpLayers->switchTo(zOrder);
	helpBtn->setEnabled(true);
	monsterBtn->setEnabled(true);
	towerBtn->setEnabled(true);
	sprMenu->setEnabled(false);
}

bool HelpScene::init(){
	if(BaseScene::init()){
		frameCache->addSpriteFramesWithFile("Themes/scene/help_1-hd.plist");
		frameCache->addSpriteFramesWithFile("Themes/scene/help_2-hd.plist");
		frameCache->addSpriteFramesWithFile("Themes/scene/help_3-hd.plist");
		//背景图片
		CCSprite* helpBg = SPRITE(help_bg.png);
		helpBg->setPosition(VisibleRect::center());
		addChild(helpBg);

		//菜单 Home
		CCMenuItemSprite* homeBtn = CCMenuItemSprite::create(SPRITE(help_home_normal.png),
			SPRITE(help_home_pressed.png),SceneManager::shareSceneManager(),menu_selector(SceneManager::toHomeSceneFromHelp));
		CCMenu* homeMenu = CCMenu::create(homeBtn,NULL);
		homeMenu->setPosition(ccp(VisibleRect::leftTop().x+70,VisibleRect::leftTop().y-60));
		addChild(homeMenu);

		//切换菜单
		helpBtn = CCMenuItemSprite::create(SPRITE(tips_normal_CN.png),SPRITE(tips_normal_CN.png),
			SPRITE(tips_selected_CN.png),this,menu_selector(HelpScene::tabMenuHandler));
		monsterBtn = CCMenuItemSprite::create(SPRITE(monster_normal_CN.png),SPRITE(monster_normal_CN.png),
			SPRITE(monster_selected_CN.png),this,menu_selector(HelpScene::tabMenuHandler));
		towerBtn = CCMenuItemSprite::create(SPRITE(tower_normal_CN.png),SPRITE(tower_normal_CN.png),
			SPRITE(tower_selected_CN.png),this,menu_selector(HelpScene::tabMenuHandler));
		CCMenu* tabMenu = CCMenu::create(helpBtn,monsterBtn,towerBtn,NULL);
		helpBtn->setEnabled(false);
		tabMenu->alignItemsHorizontallyWithPadding(0);
		tabMenu->setPosition(ccp(VisibleRect::top().x,VisibleRect::top().y-50));
		addChild(tabMenu);

		CCLayer* tipLayer = CCLayer::create();
		CCLayer* monsterLayer = CCLayer::create();
		CCLayer* towerLayer = CCLayer::create();
		helpLayers = CCLayerMultiplex::create(tipLayer,monsterLayer,towerLayer,NULL);
		addChild(helpLayers);
		setTipLayer(tipLayer);
		setMonsterLayer(monsterLayer);
		setTowerLayer(towerLayer);
		return true;
	}
	return false;
}

void HelpScene::setTipLayer(CCLayer* tipLayer){
	CCSprite* bottom = SPRITE(bottom.png);
	bottom->setPosition(ccp(VisibleRect::bottom().x,VisibleRect::bottom().y+35));
	tipLayer->addChild(bottom);
	GiantPageScrollView* tipsScrollView = GiantPageScrollView::create();
	tipsScrollView->setPosition(VisibleRect::center());
	tipsScrollView->cellSize = CCDirector::sharedDirector()->getWinSize();
	tipsScrollView->tableSize = CCDirector::sharedDirector()->getWinSize();
	tipsScrollView->cellNum = 4;
	tipsScrollView->cells = CCArray::createWithCapacity(4);
	for(int i=0;i<4;i++){
		CCLayer* tipItem = CCLayer::create();
		CCString* sprName = CCString::createWithFormat("tips_%d.png",i+1);
		CCString* tipName = CCString::createWithFormat("tips_text_%d_CN.png",i+1);
		CCSprite* tipStr = CCSprite::createWithSpriteFrameName(tipName->getCString());
		CCSprite* tip = CCSprite::createWithSpriteFrameName(sprName->getCString());
		tip->setPosition(VisibleRect::center());
		tipStr->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y-200));
		tipItem->ignoreAnchorPointForPosition(false);
		tipItem->setPosition(VisibleRect::center());
		tipItem->addChild(tip);
		tipItem->addChild(tipStr);
		tipsScrollView->cells->addObject(tipItem);
	}
	tipsScrollView->cells->retain();
	tipLayer->addChild(tipsScrollView);
}

void HelpScene::setMonsterLayer(CCLayer* monsterLayer){
	CCSprite* monster = SPRITE(help_monster.png);
	CCSprite* monsterTxt = SPRITE(help_monster_CN.png);
	monster->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y-50));
	monsterTxt->setPosition(monster->getPosition());
	monsterLayer->addChild(monster);
	monsterLayer->addChild(monsterTxt);
}

void HelpScene::setTowerLayer(CCLayer* towerLayer){
	CCSprite* bottom = SPRITE(bottom.png);
	bottom->setPosition(ccp(VisibleRect::bottom().x,VisibleRect::bottom().y+35));
	towerLayer->addChild(bottom);
	GiantPageScrollView* towerPageScroll = GiantPageScrollView::create();
	towerPageScroll->setPosition(VisibleRect::center());
	towerPageScroll->cellSize = CCDirector::sharedDirector()->getWinSize();
	towerPageScroll->tableSize = CCDirector::sharedDirector()->getWinSize();
	towerPageScroll->cellNum = 18;
	towerPageScroll->cells = CCArray::createWithCapacity(18);

	for(int i=0;i<18;i++){
		CCString* towerUrl;
		CCString* towerInfo;
		if(i<9){
			towerUrl = CCString::createWithFormat("tower_0%d.png",i+1);
			towerInfo = CCString::createWithFormat("tower_0%d_CN.png",i+1);
		}else{
			towerUrl = CCString::createWithFormat("tower_%d.png",i+1);
			towerInfo = CCString::createWithFormat("tower_%d_CN.png",i+1);
		}
		
		CCLayer* towerLayer = CCLayer::create();
		CCSprite* towerTxt = CCSprite::createWithSpriteFrameName(towerInfo->getCString());
		CCSprite* tower = CCSprite::createWithSpriteFrameName(towerUrl->getCString());
		tower->setPosition(VisibleRect::center());
		towerTxt->setPosition(VisibleRect::center());
		towerLayer->ignoreAnchorPointForPosition(false);
		towerLayer->setPosition(VisibleRect::center());
		towerLayer->addChild(tower);
		towerLayer->addChild(towerTxt);
		
		towerPageScroll->cells->addObject(towerLayer);

	}
	towerPageScroll->cells->retain();
	towerLayer->addChild(towerPageScroll);
}