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
		CCSprite* dargBg = SPRITE(darkbg.png);
		dargBg->setPosition(VisibleRect::center());
		addChild(dargBg);
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
		//微博
		CCNode* weiboNode = CCNode::create();
		weiboNode->setAnchorPoint(ccp(0.5,0));
		CCSprite* weiboBg = SPRITE(share_bg.png);
		CCSprite* weiboCN = SPRITE(share_bg_CN.png);
		CCMenuItemSprite* tencent = CCMenuItemSprite::create(SPRITE(share_tweibo_normal.png),SPRITE(share_tweibo_press.png));
		CCMenuItemSprite* sina = CCMenuItemSprite::create(SPRITE(share_weibo_normal.png),SPRITE(share_weibo_press.png));
		CCMenuItemSprite* wechat = CCMenuItemSprite::create(SPRITE(share_wechat_normal.png),SPRITE(share_wechat_press.png));
		CCMenu* weiboMenu = CCMenu::create(sina,wechat,tencent,NULL);
		weiboMenu->alignItemsHorizontallyWithPadding(0);
		weiboNode->addChild(weiboBg);
		weiboNode->addChild(weiboCN);
		weiboNode->addChild(weiboMenu);
		weiboMenu->setTouchPriority(kCCMenuHandlerPriority-3);
		weiboNode->setPosition(ccp(VisibleRect::center().x,VisibleRect::bottom().y+52));
		weiboMenu->setPosition(ccp(VisibleRect::leftBottom().x,VisibleRect::leftBottom().y-18));
		addChild(weiboNode);
		
	}while(0);
	return true;
}