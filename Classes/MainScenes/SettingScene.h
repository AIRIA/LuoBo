#ifndef _SETTINGSCENE_H_
#define _SETTINGSCENE_H_

#include "../BaseScene.h"
class SettingScene:public BaseScene{
public:
	CCLayerMultiplex* settingLayers;
	CCMenuItemSprite* statisticsBtn;
	CCMenuItemSprite* optionsBtn;
	CCMenuItemSprite* creditsBtn;
public:
	virtual bool init();
	virtual ~SettingScene(){
		/*settingLayers->release();
		statisticsBtn->release();
		optionsBtn->release();
		creditsBtn->release();*/
	};
	CREATE_FUNC(SettingScene);
	void tabMenuHandler(CCObject* pSender);
	void cutSoundX(CCObject* pSender);
	void cutBgMusic(CCObject* pSender);
	/*void statisticsHandler(CCObject* pSender);*/
};

#endif