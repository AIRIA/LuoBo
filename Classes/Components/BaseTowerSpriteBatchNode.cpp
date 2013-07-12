#include "BaseTowerSpriteBatchNode.h"
#include "../towers/BaseTower.h"

BaseTowerSpriteBatchNode* BaseTowerSpriteBatchNode::createBatchNode(CCTexture2D* texture){
	BaseTowerSpriteBatchNode* btsbn = new BaseTowerSpriteBatchNode();
	btsbn->initWithTexture(texture,kDefaultSpriteBatchCapacity);
	btsbn->autorelease();
	btsbn->schedule(schedule_selector(BaseTowerSpriteBatchNode::fire));
	return btsbn;
}

void BaseTowerSpriteBatchNode::fire(float dt){
	CCObject* child = NULL;
	CCArray* children = getChildren();
	CCARRAY_FOREACH(children,child){
		BaseTower* tower = dynamic_cast<BaseTower*>(child);
		if(tower){
			tower->attack();
		}
		
	}
}
