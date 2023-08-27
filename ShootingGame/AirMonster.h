#pragma once
#include "Enemy.h"

class AirMonster : public Enemy
{
private:
	float _breakTime, _angle;
	float _enemyTime, _airMonsterCount;

public:
	void release(void);
	void update(void);
	void render(void);

	void setInfo(tagEnemy enemy);
	void move(void);
	RECT location(void);
	void draw(void);
	void animation(void);

	AirMonster();
	~AirMonster() {}
};

