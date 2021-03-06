﻿#include "MonsterSpriteBatch.h"
#include "../Model/Monster.h"
#include "../ShareManager.h"
#include "../Model/RouteInfo.h"


MonsterSpriteBatch* MonsterSpriteBatch::createBatchNodeWithTexture(CCTexture2D* texture2D){
	MonsterSpriteBatch* msb = new MonsterSpriteBatch();
	msb->initWithTexture(texture2D,kDefaultSpriteBatchCapacity);
	msb->autorelease();
	msb->schedule(schedule_selector(MonsterSpriteBatch::freshMonster));
	return msb;
}

#define MOVE_SPEED ShareManager::getInstance()->moveSpeed

void MonsterSpriteBatch::removeAirCarrot(CCNode* pSender){
	pSender->getParent()->removeChild(pSender);
}

void MonsterSpriteBatch::freshMonster(float dt){
	int childCount = getChildrenCount();
	CCArray* children = getChildren();
	CCObject* child = NULL;
	ShareManager* sm = ShareManager::getInstance();
	int currentIdx = 0;
	int pointCount = sm->getRouteInfo()->count();
	CCARRAY_FOREACH(children,child){
		
		if(currentIdx==childCount){
			break;
		}
		currentIdx++;
		Monster* monsterSpr = (Monster*)child;
		int currentPointIdx = monsterSpr->currentPointIdx;
		int nextPointIdx = monsterSpr->nextPointIdx;
		//判断是不是碰到了萝卜
		if(currentPointIdx==(pointCount-2)){
			CCSprite* air = AnimateManager::shareAnimateManager()->createAnimate_RunOnce("air01.png","air_carrot");
			air->setAnchorPoint(ccp(0.5,0.25));
			air->setPosition(monsterSpr->getPosition());
			ShareManager::getInstance()->cloudBatchNode->addChild(air);
			ShareManager::getInstance()->monsters->fastRemoveObject(monsterSpr);
			monsterSpr->getParent()->removeChild(monsterSpr);
			sm->carrot->showHP();
			continue;
		}

		CCPoint monsterPos = monsterSpr->getPosition();
		
		CCPoint currentPoint = ((RouteInfo*)(sm->getRouteInfo()->objectAtIndex(monsterSpr->currentPointIdx)))->routePoint;
		CCPoint nextPoint = ((RouteInfo*)(sm->getRouteInfo()->objectAtIndex(monsterSpr->nextPointIdx)))->routePoint;
		if(nextPoint.x == currentPoint.x){//垂直方向移动
			if(nextPoint.y > currentPoint.y){
				monsterPos.y += MOVE_SPEED;
				if(monsterPos.y >= nextPoint.y){
					monsterSpr->currentPointIdx++;
					monsterSpr->nextPointIdx++;
				}
			}else{
				monsterPos.y -= MOVE_SPEED;
				if(monsterPos.y<=nextPoint.y){
					monsterSpr->currentPointIdx++;
					monsterSpr->nextPointIdx++;
				}
			}
		
		}else{//水平方向
			if(nextPoint.x > currentPoint.x){
				monsterPos.x += MOVE_SPEED;
				if(monsterPos.x >= nextPoint.x ){
					monsterSpr->currentPointIdx++;
					monsterSpr->nextPointIdx++;
				}
			}else{
				monsterPos.x -= MOVE_SPEED;
				if(monsterPos.x <= nextPoint.x){
					monsterSpr->currentPointIdx++;
					monsterSpr->nextPointIdx++;
				}
			}
		
		}
		monsterSpr->setPosition(monsterPos);
	}
	
}