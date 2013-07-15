#ifndef _MONSTERBLOOD_H_
#define _MONSTERBLOOD_H_

#include "GiantSprite.h"
#include "../Model/Monster.h"

class MonsterBlood:public GiantSprite{
public:
	Monster* monster;
	static MonsterBlood* createMonsterBlood();
	virtual void update(float dt);
};

#endif