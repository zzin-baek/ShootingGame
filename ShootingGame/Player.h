#pragma once
#include "GameNode.h"
#include "Animation.h"

#include "Bullets.h"

class Player : public GameNode
{
private:;
	   GImage* _f22;
	   Animation* _anim;
	   Bullet* _bullet;

	   POINT _plPos;
	   RECT _plRect;

	   int _cnt;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Player() {}
	~Player() {}
};

