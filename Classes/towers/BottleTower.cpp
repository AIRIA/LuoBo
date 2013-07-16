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
	CCCallFunc* bangFunc = CCCallFunc::create(this,callfunc_selector(BottleTower::bangEffect));
	CCActionInterval* moveTo = CCMoveTo::create(0.1,ccp(targetMonster->getPosition().x,targetMonster->getPosition().y+30));
	CCSequence* shootSeq = CCSequence::create(moveTo,bangFunc,NULL);
	CCSpawn* shoot = CCSpawn::createWithTwoActions(CCRepeatForever::create(bulletAnimate),shootSeq);
	
	bullet = CCSprite::createWithSpriteFrameName(firstBullet->getCString());
	bullet->setContentSize(getContentSize());
	bullet->setRotation(getRotation());
	float rotate = getRotation();
	CCPoint circlePoint = getPosition();
	float x = circlePoint.x,y=circlePoint.y;
	int r = 1;
	x = x+r*cos(rotate-90);
	y = y+r*sin(rotate-90);
	bullet->setPosition(ccp(x,y));
	bullet->runAction(shoot);
	getParent()->addChild(bullet,-1);
	targetMonster->hp -= atk;
}

void BottleTower::bulletSchedule(float dt){
	
}

void BottleTower::bangEffect(){
	if(!targetMonster->isShowHP){
		MonsterBlood* mb = MonsterBlood::createMonsterBlood();
		mb->monster = targetMonster;
		mb->monster->retain();
		shareManager->bloodSpriteNode->addChild(mb);
	}

	CCSprite* bang = animateManager->createAnimate_RunOnce("PBottle01.png","bangAnimate");
	CCPoint monsterPoint = targetMonster->getPosition();
	bang->setPosition(ccp(monsterPoint.x,monsterPoint.y+40));
	getParent()->addChild(bang);
	bullet->getParent()->removeChild(bullet);
}
//加载子弹的动画和碰到怪物后爆照效果动画
void BottleTower::initTower(){
	bulletName = CCString::createWithFormat("PBottle%d",towerLevel)->getCString();
	animateManager->createAnimation(bulletName.c_str(),"PBottle",towerLevel*10+1,towerLevel*10+3,8);
	animateManager->createAnimation("bangAnimate","PBottle",1,2,8);
}