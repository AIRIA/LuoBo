#include "MapMenu.h"
#include "../Assets.h"
#include "../VisibleRect.h"
#include "../SceneManager.h"

void MapMenu::registerWithTouchDispatcher(){
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,kCCMenuHandlerPriority-1,true);
}

bool MapMenu::ccTouchBegan(CCTouch* touch,CCEvent* event){
	CCLog("besdfasfafafd");
	return true;
}

bool MapMenu::init(){
	do{
		CC_BREAK_IF(!CCLayer::init());
		setContentSize(CCDirector::sharedDirector()->getWinSize());
		setTouchEnabled(true);
		CCSprite* menuBg = SPRITE(menu_bg.png);
		menuBg->setPosition(VisibleRect::center());
		addChild(menuBg);
		
		CCMenuItemSprite* quit = CCMenuItemSprite::create(SPRITE(menu_quit_normal_CN.png),SPRITE(menu_quit_pressed_CN.png),
			SceneManager::shareSceneManager(),menu_selector(SceneManager::toSubThemeScene));
		CCMenuItemSprite* restart = CCMenuItemSprite::create(SPRITE(menu_restart_normal_CN.png),SPRITE(menu_restart_pressed_CN.png));
		CCMenuItemSprite* resume = CCMenuItemSprite::create(SPRITE(menu_resume_normal_CN.png),SPRITE(menu_resume_pressed_CN.png));
		CCMenu* gameMenu = CCMenu::create(resume,restart,quit,NULL);
		gameMenu->alignItemsVerticallyWithPadding(15);
		gameMenu->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y+2));
		addChild(gameMenu);
		gameMenu->setTouchPriority(kCCMenuHandlerPriority-2);
	}while(0);
	return true;
}