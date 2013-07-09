#include "Carrot.h"
#include "../ShareManager.h"

#define GET_ANIMATE(name) CCAnimate::create(animationCache->animationByName(#name))

bool Carrot::init(){
	carrotNum = 10;
	actions = CCArray::create();
	carrot = CCSprite::createWithSpriteFrameName("hlb10.png");
	carrotShade = CCSprite::createWithSpriteFrameName("hlb0.png");
	animationCache = CCAnimationCache::sharedAnimationCache();
	animateManager = AnimateManager::shareAnimateManager();
	CCCallFunc* reset = CCCallFunc::create(this,callfunc_selector(Carrot::resetToOrigin));
	animateManager->createAnimation("carrot_shake","hlb",10,18,5);
	animateManager->createAnimation("carrot_blink","hlb",21,23,5);
	CCActionInterval* rotate1 = CCRotateBy::create(0.3,10);
	CCActionInterval* rotate2 = rotate1->reverse();
	CCActionInterval* rotate3 = CCRotateBy::create(0.3,-10);
	CCActionInterval* rotate4 = rotate3->reverse();

	CCSequence* action1 = CCSequence::create(rotate1,rotate2,rotate3,rotate4,NULL);
	CCSequence* action2 = CCSequence::create(GET_ANIMATE(carrot_shake),reset,NULL);
	CCSequence* action3 = CCSequence::create(GET_ANIMATE(carrot_blink),GET_ANIMATE(carrot_blink),reset,NULL);
	CCSpawn* spawn = CCSpawn::createWithTwoActions(action1,GET_ANIMATE(carrot_blink));
	CCSequence* action4 = CCSequence::create(spawn,reset,NULL);

	
	actions->addObject(action1);
	actions->addObject(action2);
	actions->addObject(action3);
	actions->addObject(action4);

	actions->retain();
	schedule(schedule_selector(Carrot::doRandomAction),5);
	carrot->setAnchorPoint(ccp(0.4,0));
	addChild(carrotShade);
	addChild(carrot);
	CCSize carrotSize = carrot->getContentSize();
	return true;
}

void Carrot::doRandomAction(float dt){
	//CCAssert(ShareManager::getInstance()->carrot!=this,"throw error");
	srand(time(NULL));
	int actionsLen = ShareManager::getInstance()->carrot->actions->count();
	int idx = rand()%actionsLen;
	CCAnimate* selectAction = (CCAnimate*)actions->objectAtIndex(idx);
	carrot->runAction(selectAction);
}

void Carrot::resetToOrigin(){
	CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	carrot->setDisplayFrame(frameCache->spriteFrameByName("hlb10.png"));
}

//显示萝卜当前剩下的个数
void Carrot::showHP(){
	carrot->stopAllActions();
	if(carrotNum==3){
		unschedule(schedule_selector(Carrot::doRandomAction));
	}
	while(actions->count()>1){
		actions->removeLastObject();
	}
	carrotNum--;
	if(carrotNum==0){
		carrotNum = 10;
		ShareManager::getInstance()->bossHp->getParent()->removeChild(ShareManager::getInstance()->bossHp);
		//显示失败窗口
		return;
	}
	CCString* bossHpSpr = CCString::createWithFormat("BossHP0%d.png",carrotNum);
	CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCSpriteFrame* targetFrame = frameCache->spriteFrameByName(bossHpSpr->getCString());
	CCSprite* bossHP = ShareManager::getInstance()->bossHp;
	bossHP->setDisplayFrame(targetFrame);
	CCSpriteFrame* carrotSpr;
	
	if(carrotNum!=5&&carrotNum!=7){
		CCString* carrotStatusName = CCString::createWithFormat("hlb%d.png",carrotNum);
		carrotSpr = frameCache->spriteFrameByName(carrotStatusName->getCString());
		carrot->setDisplayFrame(carrotSpr);
	}
}