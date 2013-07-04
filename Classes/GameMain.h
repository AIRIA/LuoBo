#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

#include "cocos2d.h"

USING_NS_CC;

class GameMain:public CCLayer{
private:
	CCNode* carrotNode;
public:
	virtual ~GameMain(){
	//	carrotNode->release();
		carrotNode = NULL;
	};

	/*props*/
	CCSize winSize;
	/*methods*/
	GameMain();
	static CCScene* scene();
	CREATE_FUNC(GameMain);
	virtual bool init();
	void shakeLeaf();
};

#endif