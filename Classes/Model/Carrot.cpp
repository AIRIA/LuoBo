#include "Carrot.h"
#include "../ShareManager.h"

#define GET_ANIMATE(name) CCAnimate::create(animationCache->animationByName(#name))

bool Carrot::init(){
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
	srand(time(NULL));
	int idx = rand()%(actions->count());
	CCAnimate* selectAction = (CCAnimate*)actions->objectAtIndex(idx);
	carrot->runAction(selectAction);
}

void Carrot::resetToOrigin(){
	CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	carrot->setDisplayFrame(frameCache->spriteFrameByName("hlb10.png"));
}
int carrotNum = 10;
//显示萝卜当前剩下的个数
void Carrot::showHP(){
	carrotNum--;
	if(carrotNum==0){
		//显示失败窗口
		return;
	}
	CCString* bossHpSpr = CCString::createWithFormat("BossHP0%d.png",carrotNum);
	CCSpriteFrame* targetFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(bossHpSpr->getCString());
	CCSprite* bossHP = ShareManager::getInstance()->bossHp;
	bossHP->setDisplayFrame(targetFrame);

	
}