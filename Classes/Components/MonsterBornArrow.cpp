#include "MonsterBornArrow.h"
#include "../Model/RouteInfo.h"
#include "../Assets.h"
#include "../VisibleRect.h"

#define FADE_TIME 0.3

void MonsterBornArrow::onEnter(){
	CCNode::onEnter();
	CCActionInterval* fadeIn = CCFadeIn::create(FADE_TIME);
	CCActionInterval* fadeOut = CCFadeOut::create(FADE_TIME);
	CCSequence* fadeSeq = CCSequence::create(fadeIn,CCDelayTime::create(0.2),fadeOut,NULL);
	CCNode* arrowNode = CCNode::create();
	
	CCSprite* arrow1 = SPRITE(arrow.png);
	CCSprite* arrow2 = SPRITE(arrow.png);
	CCSprite* arrow3 = SPRITE(arrow.png);
	
	
	int direction = getArrowDirection();
	switch(direction){
	case 1:
		arrow1->setPosition(ccp(10,0));
		arrowNode->setRotation(90);
		break;
	case 2:
		arrow1->setPosition(ccp(60,0));
		arrowNode->setRotation(-90);
		break;
	case 3:
		arrow1->setPosition(ccp(10,10));
		arrowNode->setRotation(-180);
		break;
	default:
		arrow1->setPosition(ccp(10,10));
		break;
	}
	CCPoint a1Point = arrow1->getPosition();
	CCSize size = arrow1->getContentSize();
	arrowNode->addChild(arrow1);
	arrowNode->addChild(arrow2);
	arrowNode->addChild(arrow3);
	arrow2->setPosition(ccp(a1Point.x+size.width,a1Point.y));
	arrow3->setPosition(ccp(a1Point.x+size.width*2,a1Point.y));
	addChild(arrowNode);
	arrow1->runAction(CCRepeat::create(CCSequence::create(fadeSeq,CCDelayTime::create(0.4),NULL),3));
	arrow2->runAction(CCRepeat::create(CCSequence::create(CCDelayTime::create(0.2),fadeSeq->copy(),CCDelayTime::create(0.2),NULL),3));
	arrow3->runAction(CCRepeat::create(CCSequence::create(CCDelayTime::create(0.4),fadeSeq->copy(),NULL),3));

}

bool MonsterBornArrow::init(){

	return true;
}

//获取怪物出现的方向
int MonsterBornArrow::getArrowDirection(){
	
	CCPoint ri1 = ((RouteInfo*)ShareManager::getInstance()->getRouteInfo()->objectAtIndex(0))->routePoint;
	CCPoint ri2 = ((RouteInfo*)ShareManager::getInstance()->getRouteInfo()->objectAtIndex(1))->routePoint;
	if(ri1.x == ri2.x){
		if(ri1.y > ri2.y){
			return 1;//down
		}
		return 2;//up
	}else{
		if(ri1.x > ri2.x){
			return 3;//left
		}
		return 4;//right
	}
	return 0;
}