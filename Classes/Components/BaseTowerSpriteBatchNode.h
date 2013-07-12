#ifndef _BASETOWERSPRITEBATCHNODE_H_
#define _BASETOWERSPRITEBATCHNODE_H_
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class BaseTowerSpriteBatchNode:public CCSpriteBatchNode{
public:
	string towerType;
	static BaseTowerSpriteBatchNode* createBatchNode(CCTexture2D* texture);
	void fire(float dt);
};

#endif