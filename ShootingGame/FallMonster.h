#pragma once
#include "Enemy.h"

class FallMonster : public Enemy
{
private:
	float _fallMonsterCount;
public:
	void release(void);
	void update(void);
	void render(void);

	void setInfo(tagEnemy enemy);
	void move(void);
	RECT location(void);
	void draw(void);
	void animation(void);

	FallMonster() {}
	~FallMonster() {}
};

