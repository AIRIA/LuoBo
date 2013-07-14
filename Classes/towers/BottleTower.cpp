#include "BottleTower.h"
int times = 0;
void BottleTower::fire(float dt){
	if(isFinded){
		CCString* animateName = CCString::createWithFormat((towerType+"%d").c_str(),towerLevel);
		CCAnimation* fireAnimation = animateCache->animationByName(animateName->getCString());
		CCAnimate* fireAnimate = CCAnimate::create(fireAnimation);
		CCCallFuncN* cfn = CCCallFuncN::create(this,callfuncN_selector(BottleTower::creatBullte));
		runAction(CCSequence::create(fireAnimate,cfn,NULL));
	}
}

void BottleTower::creatBullte(CCNode* node){
	BottleTower* bt = (BottleTower*)node;
	CCString* firstFrame = CCString::createWithFormat((bt->towerType+"%d1.png").c_str(),bt->towerLevel);
	bt->setDisplayFrame(frameCache->spriteFrameByName(firstFrame->getCString()));
	CCAnimation* bulletAnimation = animateCache->animationByName(bulletName.c_str());
	CCString* firstBullet = CCString::createWithFormat("PBottle%d1.png",towerLevel);
	CCAnimate* bulletAnimate = CCAnimate::create(bulletAnimation);
	CCActionInterval* moveTo = CCMoveTo::create(0.2,targetMonster->getPosition());
	CCSpawn* shoot = CCSpawn::createWithTwoActions(CCRepeatForever::create(bulletAnimate),moveTo);
	bullet = CCSprite::createWithSpriteFrameName(firstBullet->getCString());
	bullet->setContentSize(getContentSize());
	bullet->setRotation(getRotation());
	int radius = 40;
	int x = radius*cos(getRotation());
	int y = radius*sin(getRotation());
	int temp = x;
	x = radius*cos(getRotation()+x);
	y = radius*sin(getRotation()+x);
	bullet->setPosition(ccp(getPosition().x+x,getPosition().y+y));
	bullet->runAction(shoot);
	getParent()->addChild(bullet,-1);
}

void BottleTower::bulletSchedule(float dt){
	
}

void BottleTower::bangEffect(){

}

void BottleTower::initTower(){
	bulletName = CCString::createWithFormat("PBottle%d",towerLevel)->getCString();
	animateManager->createAnimation(bulletName.c_str(),"PBottle",towerLevel*10+1,towerLevel*10+3,8);
}