#include "SceneManager.h"
#include "MainScenes\HelpScene.h"
#include "MainScenes\SettingScene.h"
#include "GameMain.h"
#include "MainScenes\AdventureScene.h"
#include "MainScenes\SubThemeScene.h"

SceneManager* SceneManager::_smInstance = NULL;

SceneManager* SceneManager::shareSceneManager(){
	if(!_smInstance){
		_smInstance = new SceneManager();
	}
	return _smInstance;
}

void SceneManager::toHomeSceneFromAdv(CCObject* pSender){
	CCDirector::sharedDirector()->replaceScene(CCTransitionShrinkGrow::create(0.5,GameMain::scene()));
}

void SceneManager::toHomeSceneFromSet(CCObject* pSender){
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInB::create(0.3,GameMain::scene()));
}

void SceneManager::toHomeSceneFromHelp(CCObject* pSender){
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.3,GameMain::scene()));
}

void SceneManager::toAdventureScene(CCObject* pSender){
	AdventureScene* advScene = AdventureScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionShrinkGrow::create(0.5,advScene));
}

void SceneManager::toHelpScene(CCObject* pSender){
	HelpScene* helpScene = HelpScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInB::create(0.5,helpScene));
}

void SceneManager::toSettingScene(CCObject* pSender){
	SettingScene* settingScene = SettingScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.5,settingScene));
}

void SceneManager::toAdventureSceneFromBack(CCObject* pSender){
	AdventureScene* advScene = AdventureScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionSplitCols::create(0.5,advScene));
}

void SceneManager::toSubThemeScene(CCObject* pSender){
	SubThemeScene* sts = SubThemeScene::create();
	CCDirector::sharedDirector()->replaceScene(sts);
}