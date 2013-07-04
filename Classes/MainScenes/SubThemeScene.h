#ifndef _SUBTHEMESCEEN_H_
#define _SUBTHEMESCEEN_H_


#include "../BaseScene.h"
#include "../Assets.h"
class SubThemeScene:public BaseScene{
public:
	unsigned int idx;
public:
	static SubThemeScene* createWithSceneIdx(unsigned int idx);
	CREATE_FUNC(SubThemeScene);
	virtual bool init();
	void toSelectMap(CCObject* pSender);
	virtual void onEnter();
}; 

#endif 