#include "MonsterBlood.h"

MonsterBlood* MonsterBlood::createMonsterBlood(){
	MonsterBlood* mb = new MonsterBlood();
	if(mb&&mb->initWithSpriteFrameName("MonsterHP01.png")){
		mb->autorelease();
		mb->bg = CCSprite::createWithSpriteFrameName("MonsterHP02.png");
		mb->bg->setAnchorPoint(ccp(1,0.5));
		mb->bg->setPosition(ccp(mb->getContentSize().width-2,mb->getContentSize().height/2));
		mb->bg->setScaleX(0);
		mb->bg->setTag(1001);
		mb->addChild(mb->bg);
		mb->scheduleUpdate();
	}
	return mb;
}

void MonsterBlood::update(float dt){
	if(monster->getParent()!=NULL){
		float hp = monster->hp;
		if(hp<=0){
			monster->getParent()->removeChild(monster);
		}else{
			bg->setScaleX((100-hp)/100);
		}
		CCPoint monsterPos = monster->getPosition();
		setPosition(ccp(monsterPos.x,monsterPos.y+100));
	}else{
		if(monster->isDead==false){
			CCSprite* air = AnimateManager::shareAnimateManager()->createAnimate_RunOnce("air21.png","air_monster");
			air->setPosition(monster->getPosition());
			ShareManager::getInstance()->cloudBatchNode->addChild(air);
			monster->isDead = true;
		}
		getParent()->removeChild(this);
		ShareManager::getInstance()->monsters->fastRemoveObject(monster);
		monster->release();
	}
}