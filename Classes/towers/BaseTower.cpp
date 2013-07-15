#include "BaseTower.h"
#include "../ShareManager.h"
#include "../Model/Monster.h"



//寻找怪物
void BaseTower::findMonster(){
	CCObject* obj = NULL;
	CCArray* monsters = ShareManager::getInstance()->monsters;
	CCPoint pos = getPosition();
	CCARRAY_FOREACH(monsters,obj){
		Monster* monster = (Monster*)obj;
		CCPoint monsterPos = monster->getPosition();
		monsterPos = ccp(monsterPos.x,monsterPos.y+40);
		float distance = ccpDistance(monsterPos,pos);
		CCPoint vectorPoint = ccpSub(monsterPos,pos);
		if(distance<=attackDistance){
			targetMonster = monster;
			isFinded = true;
			float angle = ccpToAngle(vectorPoint);
			float degree = CC_RADIANS_TO_DEGREES(angle);
			CCActionInterval* rotate = CCRotateTo::create(0.2,-degree+90);
			runAction(CCSequence::create(rotate,NULL));
			break;
		}else{
			isFinded = false;
		}
	}
}


void BaseTower::upgrade(){

}

void BaseTower::attack(){
	findMonster();
}

bool BaseTower::ccTouchBegan(CCTouch* touch,CCEvent* event){
	if(isContainPoint(touch)){
		ShareManager::getInstance()->isTower = true;
		return true;
	}
	
	return false;
}

void BaseTower::ccTouchEnded(CCTouch* touch,CCEvent* event){
	ShareManager::getInstance()->isTower = false;
}