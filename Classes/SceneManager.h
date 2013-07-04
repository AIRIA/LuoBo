#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "cocos2d.h"
USING_NS_CC;

class SceneManager:public CCObject{
private:
	static SceneManager* _smInstance;
public:
	static SceneManager* shareSceneManager();
	void toHomeSceneFromAdv(CCObject* pSender);
	void toHomeSceneFromSet(CCObject* pSender);
	void toHomeSceneFromHelp(CCObject* pSender);
	void toSettingScene(CCObject* pSender);
	void toHelpScene(CCObject* pSender);
	void toAdventureScene(CCObject* pSender);
	void toAdventureSceneFromBack(CCObject* pSender);
	void toSubThemeScene(CCObject* pSender);
};


#endif