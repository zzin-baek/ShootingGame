#pragma once
#include "GameNode.h"
#include "Animation.h"
#include "EnemyManager.h"
#include "Bullets.h"

class Player : public GameNode
{
private:;
	   GImage* _f22;
	   Animation* _anim;
	   Bullet* _bullet;
	   EnemyManager* _em;

	   POINT _plPos;
	   RECT _plRect;

	   int _cnt;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setEnemyManagerMemoryAddress(EnemyManager* em) { _em = em; }

	POINT getPosition(void) { return _plPos; }
	RECT getRect(void) { return _plRect; }

	Player() {}
	~Player() {}
};

