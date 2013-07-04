#include "MonsterSpriteBatch.h"
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

#define MOVE_SPEED 1

void MonsterSpriteBatch::freshMonster(float dt){
	int childCount = getChildrenCount();
	CCArray* children = getChildren();
	CCObject* child = NULL;
	ShareManager* sm = ShareManager::getInstance();
	int currentIdx = 0;
	CCARRAY_FOREACH(children,child){
		
		if(currentIdx==childCount){
			break;
		}
		currentIdx++;
		Monster* monsterSpr = (Monster*)child;
		CCPoint monsterPos = monsterSpr->getPosition();
		CCLog("Count:%d",sm->getRouteInfo()->count());
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