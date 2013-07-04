#include "SettingScene.h"
#include "../Assets.h"
#include "../VisibleRect.h"
#include "../GameMain.h"
#include "../SceneManager.h"

enum{
	kHome,
	kCreditsMenu,
	kOptionsMenu,
	kStatisticMenu,
	kMenuLayer
};

bool SettingScene::init(){
	if(!BaseScene::init()){
		return false;
	}
	frameCache->addSpriteFramesWithFile("Themes/scene/setting01-hd.plist");
	frameCache->addSpriteFramesWithFile("Themes/scene/setting02-hd.plist");
	
	CCLayer* optionsLayer = CCLayer::create();
	CCLayer* creditsLayer = CCLayer::create();
	CCLayer* statisticsLayer = CCLayer::create();
	//制作方面板
	CCSprite* creditsBg = SPRITE(credits_bg.png);
	creditsLayer->addChild(creditsBg);
	creditsBg->setPosition(VisibleRect::center());
	//数据统计面板
	CCSprite* statisticBg = SPRITE(statistics_bg.png);
	CCSprite* statisticBgCN = SPRITE(statistics_bg_CN.png);
	statisticsLayer->addChild(statisticBg);
	statisticsLayer->addChild(statisticBgCN);
	statisticBgCN->setPosition(VisibleRect::center());
	statisticBg->setPosition(VisibleRect::center());

	//选项面板
	CCSprite* optionsBg = SPRITE(setting_bg.png);
	CCSprite* musicLabel = SPRITE(setting_bg_CN.png);
	optionsLayer->addChild(optionsBg);
	optionsLayer->addChild(musicLabel);
	musicLabel->setPosition(VisibleRect::center());
	optionsBg->setPosition(VisibleRect::center());
	/* 音乐和音效切换菜单 */
	CCMenuItemSprite* soundXOn = CCMenuItemSprite::create(SPRITE(soundfx_on_CN.png),SPRITE(soundfx_on_CN.png));
	CCMenuItemSprite* soundXOff = CCMenuItemSprite::create(SPRITE(soundfx_off_CN.png),SPRITE(soundfx_off_CN.png));
	CCMenuItemSprite* bgMusicOff = CCMenuItemSprite::create(SPRITE(bgmusic_off_CN.png),SPRITE(bgmusic_off_CN.png));
	CCMenuItemSprite* bgMusicOn = CCMenuItemSprite::create(SPRITE(bgmusic_on_CN.png),SPRITE(bgmusic_on_CN.png));
	CCMenuItemToggle* soundX = CCMenuItemToggle::createWithTarget(this,menu_selector(SettingScene::cutSoundX),soundXOn,soundXOff,NULL);
	CCMenuItemToggle* bgMusic = CCMenuItemToggle::createWithTarget(this,menu_selector(SettingScene::cutBgMusic),bgMusicOn,bgMusicOff,NULL);
	CCMenu* musicMenu = CCMenu::create(soundX,bgMusic,NULL);
	musicMenu->alignItemsHorizontallyWithPadding(40);
	musicMenu->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y+70));
	optionsLayer->addChild(musicMenu);
	/* 重置游戏的按钮 */
	CCMenuItemSprite* resetGame = CCMenuItemSprite::create(SPRITE(resetgame_normal_CN.png),SPRITE(resetgame_pressed_CN.png));
	CCMenu* resetMenu = CCMenu::create(resetGame,NULL);
	resetMenu->setPosition(ccp(VisibleRect::bottom().x,VisibleRect::bottom().y+100));
	optionsLayer->addChild(resetMenu);
	//多选面板
	settingLayers = CCLayerMultiplex::create(optionsLayer,statisticsLayer,creditsLayer,NULL);
	settingLayers->switchTo(0);
	
	addChild(settingLayers);
	//菜单层
	CCLayer* menuLayer = CCLayer::create();
	//返回主页的按钮
	CCMenuItemSprite* homeBtn = CCMenuItemSprite::create(SPRITE(setting_home_normal.png),SPRITE(setting_home_pressed.png));
	CCMenu* homeMenu = CCMenu::create(homeBtn,NULL);
	homeMenu->setPosition(ccp(VisibleRect::leftTop().x+80,VisibleRect::leftTop().y-60));
	homeBtn->setTarget(SceneManager::shareSceneManager(),menu_selector(SceneManager::toHomeSceneFromSet));
	//选项 数据统计 制作方 
	statisticsBtn = CCMenuItemSprite::create(SPRITE(statistics_normal_CN.png),SPRITE(statistics_normal_CN.png),SPRITE(statistics_selected_CN.png),this,menu_selector(SettingScene::tabMenuHandler));
	optionsBtn = CCMenuItemSprite::create(SPRITE(options_normal_CN.png),SPRITE(options_normal_CN.png),SPRITE(options_selected_CN.png),this,menu_selector(SettingScene::tabMenuHandler));
	creditsBtn = CCMenuItemSprite::create(SPRITE(credits_normal_CN.png),SPRITE(credits_normal_CN.png),SPRITE(credits_selected_CN.png),this,menu_selector(SettingScene::tabMenuHandler));
	optionsBtn->setEnabled(false);
	CCMenu* tabMenu = CCMenu::create(optionsBtn,statisticsBtn,creditsBtn,NULL);
	optionsBtn->setZOrder(0);
	statisticsBtn->setZOrder(1);
	creditsBtn->setZOrder(2);
	tabMenu->alignItemsHorizontallyWithPadding(0);
	tabMenu->setPosition(ccp(VisibleRect::top().x,VisibleRect::top().y-45));
	menuLayer->addChild(homeMenu);
	menuLayer->addChild(tabMenu);
	addChild(menuLayer);
	
	return true;
}

void SettingScene::tabMenuHandler(CCObject* pSender){
	CCMenuItemSprite* sprMenu = (CCMenuItemSprite*)pSender;
	int zOrder = sprMenu->getZOrder();
	settingLayers->switchTo(zOrder);
	creditsBtn->setEnabled(true);
	statisticsBtn->setEnabled(true);
	optionsBtn->setEnabled(true);
	sprMenu->setEnabled(false);
}

void SettingScene::cutSoundX(CCObject* pSender){

}

void SettingScene::cutBgMusic(CCObject* pSender){

}