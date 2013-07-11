#include "Monster.h"
#include "../Assets.h"
#include "RouteInfo.h"

void Monster::createWithMonsterName(const char* initFrame,const char* monsterName){
	
	ShareManager* sm = ShareManager::getInstance();
	MonsterSpriteBatch* monsterBatchNode = ShareManager::getInstance()->monsterBatchNode;
	Monster* monsterSpr = new Monster();
	if(monsterSpr && monsterSpr->initWithSpriteFrameName(initFrame)){
		monsterSpr->autorelease();
	}
	monsterSpr->setAnchorPoint(ccp(0.5,0.2));
	monsterSpr->currentPointIdx = 0;
	monsterSpr->nextPointIdx = 1;
	CCAnimate* sprAnimate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName(monsterName));

	monsterBatchNode->addChild(monsterSpr);
	monsterSpr->runAction(CCRepeatForever::create(sprAnimate));
	RouteInfo* startPoint = (RouteInfo*)(sm->getRouteInfo()->objectAtIndex(0));
	monsterSpr->setPosition(startPoint->routePoint);
	ShareManager::getInstance()->monsters->addObject(monsterSpr);
}

bool Monster::init(){
	
	
	return true;
}