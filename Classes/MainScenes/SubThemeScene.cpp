#include "SubThemeScene.h"
#include "../VisibleRect.h"
#include "../SceneManager.h"
#include "../Components/GiantPageScrollView.h"
#include "BattleScene.h"
#include "../ShareManager.h"

enum{
	kPsv
};

void SubThemeScene::onEnter(){
	BaseScene::onEnter();
	GiantPageScrollView* pageScroll = (GiantPageScrollView*)getChildByTag(kPsv);
	pageScroll->showCellByInx(ShareManager::getInstance()->mapId-1,false);
}

SubThemeScene* SubThemeScene::createWithSceneIdx(unsigned int idx){
	idx++;
	if(idx==4){
		idx=6;
	}
	ShareManager::getInstance()->currentThemeId = idx;
	SubThemeScene* themeScene = SubThemeScene::create();
	return themeScene;
}

bool SubThemeScene::init(){
	if(!BaseScene::init()){
		return false;
	}
	CCString* themSprites = CCString::createWithFormat("Themes/scene/stages_theme%d-hd.plist",ShareManager::getInstance()->currentThemeId);
	frameCache->addSpriteFramesWithFile("Themes/scene/stages_bg-hd.plist");
	frameCache->addSpriteFramesWithFile(themSprites->getCString());
	//场景背景图片
	CCSprite* sceneBg = SPRITE(ss_bg.png);
	CCSprite* sceneBgCN = SPRITE(ss_bg_CN.png);
	sceneBg->setPosition(VisibleRect::center());
	sceneBgCN->setPosition(VisibleRect::center());
	addChild(sceneBg);
	addChild(sceneBgCN);	
	//底部云彩
	CCSprite* cloudBg = SPRITE(ss_cloud.png);
	cloudBg->setPosition(VisibleRect::center());
	addChild(cloudBg);


	//back help菜单
	CCMenuItemSprite* homeBtn = CCMenuItemSprite::create(SPRITE(ss_back_normal.png),SPRITE(ss_back_pressed.png),
		SceneManager::shareSceneManager(),menu_selector(SceneManager::toAdventureSceneFromBack));
	CCMenuItemSprite* helpBtn = CCMenuItemSprite::create(SPRITE(ss_help_normal.png),SPRITE(ss_help_pressed.png),
		SceneManager::shareSceneManager(),menu_selector(SceneManager::toHelpScene));
	CCMenu* topMenu = CCMenu::create(homeBtn,helpBtn,NULL);
	topMenu->alignItemsHorizontallyWithPadding(800);
	topMenu->setPosition(ccp(VisibleRect::top().x,VisibleRect::top().y-30));
	addChild(topMenu);

	//滚动table
	GiantPageScrollView* psv = GiantPageScrollView::create();
	psv->tableSize = CCDirector::sharedDirector()->getWinSize();
	psv->cellSize = psv ->tableSize;
	psv->cellNum = 12;
	psv->cells = CCArray::createWithCapacity(12);
	
	for(int i=0;i<12;i++){
		CCString* mapUrl;
		CCString* towerUrl;
		if(i<9){
			mapUrl = CCString::createWithFormat("ss_map0%d.png",i+1);
			towerUrl = CCString::createWithFormat("ss_towers_0%d.png",i+1);
		}else{
			mapUrl = CCString::createWithFormat("ss_map%d.png",i+1);
			towerUrl = CCString::createWithFormat("ss_towers_%d.png",i+1);
		}
		CCLayer* layer = CCLayer::create();
		CCSprite* theme = CCSprite::createWithSpriteFrameName(mapUrl->getCString());
		CCSprite* tower = CCSprite::createWithSpriteFrameName(towerUrl->getCString());
		theme->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y+40));
		tower->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y-160));
		layer->addChild(theme);
		layer->addChild(tower);

		psv->cells->addObject(layer);
	}
	psv->setPosition(VisibleRect::center());
	psv->setTouchTarget(this,menu_selector(SubThemeScene::toSelectMap));
	psv->setTag(kPsv);
	psv->cells->retain();
	addChild(psv);

	CCMenuItemSprite* playBtn =CCMenuItemSprite::create(SPRITE(ss_play_normal_CN.png),SPRITE(ss_play_pressed_CN.png));
	CCMenu* playMenu = CCMenu::create(playBtn,NULL);
	playMenu->setPosition(ccp(VisibleRect::center().x,90));
	addChild(playMenu);

	return true;
}

void SubThemeScene::toSelectMap(CCObject* pSender){
	GiantPageScrollView* psv = (GiantPageScrollView*)getChildByTag(kPsv);
	ShareManager::getInstance()->mapId = (psv->getCurrentIdx())+1;
	BattleScene* bs = BattleScene::createWithThemeIdx();
	CCDirector::sharedDirector()->replaceScene(CCTransitionSplitRows::create(0.5,bs));
}