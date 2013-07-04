#ifndef _HELPSCENE_H_
#define _HELPSCENE_H_

#include "../BaseScene.h"

class HelpScene:public BaseScene{
private:
	CCMenuItemSprite *helpBtn,*monsterBtn,*towerBtn;
public:
	CCLayerMultiplex* helpLayers;
	virtual bool init();
	virtual ~HelpScene(){
		/*helpBtn->release();
		monsterBtn->release();
		towerBtn->release();
		helpLayers->release();
		helpBtn = NULL;
		monsterBtn = NULL;
		towerBtn = NULL;*/
	};
	CREATE_FUNC(HelpScene);
	void tabMenuHandler(CCObject* pSender);
	void setTipLayer(CCLayer* tipLayer);
	void setMonsterLayer(CCLayer* monsterLayer);
	void setTowerLayer(CCLayer* towerLayer);

};

#endif