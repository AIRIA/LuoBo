#ifndef _ADVENTURESCENE_H_
#define _ADVENTURESCENE_H_

#include "../BaseScene.h"

class AdventureScene:public BaseScene{
public:
	CCMenuItemSprite *rightArrow,*leftArrow;
public:
	virtual bool init();
	virtual ~AdventureScene(){
		
	};
	CREATE_FUNC(AdventureScene);
	void toSelectTheme(CCObject* pSender);
	void showNextTheme(CCObject* pSender);
	void showPrevTheme(CCObject* pSender);
};

#endif