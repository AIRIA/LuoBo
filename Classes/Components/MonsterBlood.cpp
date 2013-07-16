#include "MonsterBlood.h"

MonsterBlood* MonsterBlood::createMonsterBlood(){
	MonsterBlood* mb = new MonsterBlood();
	if(mb&&mb->initWithSpriteFrameName("MonsterHP01.png")){
		mb->autorelease();
		CCSprite* bg = CCSprite::createWithSpriteFrameName("MonsterHP02.png");
		bg->setAnchorPoint(ccp(0,0));
		mb->addChild(bg);
		mb->scheduleUpdate();
	}
	return mb;
}

void MonsterBlood::update(float dt){
	if(monster->getParent()!=NULL){
		CCPoint monsterPos = monster->getPosition();
		setPosition(ccp(monsterPos.x,monsterPos.y+100));
	}else{
		getParent()->removeChild(this);
	}
}