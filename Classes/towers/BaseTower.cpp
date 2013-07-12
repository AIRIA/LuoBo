#include "BaseTower.h"
#include "../ShareManager.h"
#include "../Model/Monster.h"
//创建炮塔
BaseTower* BaseTower::createBaseTower(const char* tower){
	BaseTower* bt = new BaseTower();
	if(bt&&bt->initWithSpriteFrameName(tower)){
		bt->autorelease();
	}
	return bt;
}
//寻找怪物
void BaseTower::findMonster(){
	CCObject* obj = NULL;
	CCArray* monsters = ShareManager::getInstance()->monsters;
	CCPoint pos = getPosition();
	CCARRAY_FOREACH(monsters,obj){
		Monster* monster = (Monster*)obj;
		CCPoint monsterPos = monster->getPosition();
		float distance = ccpDistance(monsterPos,pos);
		CCPoint vectorPoint = ccpSub(monsterPos,pos);
		if(distance<=attackDistance){
			float angle = ccpToAngle(vectorPoint);
			float degree = CC_RADIANS_TO_DEGREES(angle);
			CCActionInterval* rotate = CCRotateTo::create(0.3,-degree+90);
			runAction(CCSequence::create(rotate,NULL));
			break;
		}
	}
}

void BaseTower::fire(){

}

void BaseTower::upgrade(){

}

void BaseTower::attack(){
	findMonster();
	fire();
}

bool BaseTower::ccTouchBegan(CCTouch* touch,CCEvent* event){
	if(isContainPoint(touch)){
		ShareManager::getInstance()->isTower = true;
	}else{
		ShareManager::getInstance()->isTower = false;
	}
	
	return true;
}