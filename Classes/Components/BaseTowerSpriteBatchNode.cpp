#include "BaseTowerSpriteBatchNode.h"

BaseTowerSpriteBatchNode* BaseTowerSpriteBatchNode::createBatchNode(CCTexture2D* texture){
	BaseTowerSpriteBatchNode* btsbn = new BaseTowerSpriteBatchNode();
	if(btsbn&&btsbn->initWithTexture(texture,kDefaultSpriteBatchCapacity)){
		btsbn->autorelease();
	}
	return btsbn;
}