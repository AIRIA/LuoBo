#include "BaseTower.h"
#include "../ShareManager.h"
#include "../Model/Monster.h"

BaseTower* BaseTower::createBaseTower(const char* tower){
	BaseTower* bt = new BaseTower();
	if(bt&&bt->initWithSpriteFrameName(tower)){
		bt->autorelease();
	}
	bt->schedule(schedule_selector(BaseTower::attack));
	return bt;
}

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
			setRotation(angle);
		}
	}
}

void BaseTower::fire(){

}

void BaseTower::upgrade(){

}

void BaseTower::attack(float dt){
	findMonster();
	fire();
}

bool BaseTower::init(){
	if(!GiantSprite::init()){
		return false;
	}
	
	return true;
}