#include "AdventureScene.h"
#include "../Assets.h"
#include "../VisibleRect.h"
#include "../Components/GiantPageScrollView.h"
#include "../SceneManager.h"
#include "SubThemeScene.h"

enum{
	kThemeSelect
};

void AdventureScene::showNextTheme(CCObject* pSender){
	GiantPageScrollView* pageScroll = (GiantPageScrollView*)getChildByTag(kThemeSelect);
	int idx = pageScroll->getCurrentIdx();
	int cellNum = pageScroll->cellNum;
	int nextIdx = idx+1;
	if(nextIdx<cellNum){
		pageScroll->showCellByInx(nextIdx);
	}
	
}

void AdventureScene::showPrevTheme(CCObject* pSender){
	GiantPageScrollView* pageScroll = (GiantPageScrollView*)getChildByTag(kThemeSelect);
	int idx = pageScroll->getCurrentIdx();
	int cellNum = pageScroll->cellNum;
	int prevIdx = idx-1;
	if(prevIdx>=0){
		pageScroll->showCellByInx(prevIdx);
	}
	
}

bool AdventureScene::init(){
	if(!BaseScene::init()){
		return false;
	}
	frameCache->addSpriteFramesWithFile("Themes/scene/stages_bg-hd.plist");
	frameCache->addSpriteFramesWithFile("Themes/scene/themescene1-hd.plist");
	frameCache->addSpriteFramesWithFile("Themes/scene/themescene2-hd.plist");
	//场景背景图片
	CCSprite* sceneBg = SPRITE(ss_bg.png);
	CCSprite* sceneBgCN = SPRITE(ss_bg_CN.png);
	sceneBg->setPosition(VisibleRect::center());
	sceneBgCN->setPosition(VisibleRect::center());
	addChild(sceneBg);
	addChild(sceneBgCN);
	//home help菜单
	CCMenuItemSprite* homeBtn = CCMenuItemSprite::create(SPRITE(theme_home_normal.png),SPRITE(theme_home_pressed.png),
		SceneManager::shareSceneManager(),menu_selector(SceneManager::toHomeSceneFromAdv));
	CCMenuItemSprite* helpBtn = CCMenuItemSprite::create(SPRITE(ss_help_normal.png),SPRITE(ss_help_pressed.png),
		SceneManager::shareSceneManager(),menu_selector(SceneManager::toHelpScene));
	CCMenu* topMenu = CCMenu::create(homeBtn,helpBtn,NULL);
	topMenu->alignItemsHorizontallyWithPadding(800);
	topMenu->setPosition(ccp(VisibleRect::top().x,VisibleRect::top().y-30));
	addChild(topMenu);
	//left right 切换场景
	rightArrow = CCMenuItemSprite::create(SPRITE(theme_pointright_normal.png),SPRITE(theme_pointright_pressed.png),
		this,menu_selector(AdventureScene::showNextTheme));
	leftArrow = CCMenuItemSprite::create(SPRITE(theme_pointleft_normal.png),SPRITE(theme_pointleft_pressed.png),
		this,menu_selector(AdventureScene::showPrevTheme));
	CCMenu* cutMenu = CCMenu::create(leftArrow,rightArrow,NULL);
	cutMenu->alignItemsHorizontallyWithPadding(650);
	cutMenu->setPosition(VisibleRect::center());
	addChild(cutMenu);

	//大场景选择预览tablescrollview
	GiantPageScrollView* themeSelect = GiantPageScrollView::create();
	themeSelect->setPosition(VisibleRect::center());
	themeSelect->tableSize = CCDirector::sharedDirector()->getWinSize();
	themeSelect->cellSize = CCDirector::sharedDirector()->getWinSize();
	themeSelect->cellNum = 5;
	themeSelect->cells = CCArray::createWithCapacity(5);
	for(int i=0;i<6;i++){
		if(i==3){
			continue;
		}
		CCLayer* themeLayer = CCLayer::create();
		CCString* sprName = CCString::createWithFormat("theme_pack0%d.png",i+1);
		CCString* sprNameCN = CCString::createWithFormat("theme_pack0%d_CN.png",i+1);
		CCSprite* theme = CCSprite::createWithSpriteFrameName(sprName->getCString());
		CCSprite* themeCN = CCSprite::createWithSpriteFrameName(sprNameCN->getCString());
		theme->setPosition(VisibleRect::center());
		themeCN->setPosition(VisibleRect::center());
		
		themeLayer->addChild(theme);
		themeLayer->addChild(themeCN);
		themeSelect->cells->addObject(themeLayer);
	}
	themeSelect->cells->retain();
	themeSelect->setTouchTarget(this,menu_selector(AdventureScene::toSelectTheme));
	themeSelect->setTag(kThemeSelect);
	addChild(themeSelect);
	return true;
}

void AdventureScene::toSelectTheme(CCObject* pSender){
	GiantPageScrollView* pageScroll = (GiantPageScrollView*)pSender;
	if(pageScroll->getCurrentIdx()==4){
		return;
	}
	SubThemeScene* subTheme = SubThemeScene::createWithSceneIdx(pageScroll->getCurrentIdx());
	CCDirector::sharedDirector()->replaceScene(CCTransitionSplitRows::create(0.5,subTheme));
}