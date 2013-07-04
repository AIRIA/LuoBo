#ifndef _MONSTERSPRITEBATCH_H_
#define _MONSTERSPRITEBATCH_H_

#include "cocos2d.h"

USING_NS_CC;
class MonsterSpriteBatch:public CCSpriteBatchNode,public CCTargetedTouchDelegate{
public:
	static MonsterSpriteBatch* createBatchNodeWithTexture(CCTexture2D* texture2D);
	void freshMonster(float dt);
	void removeAirCarrot(CCNode* pSender);
	

};

#endif