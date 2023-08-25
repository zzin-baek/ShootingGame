#pragma once
#include "GameNode.h"
#include "Animation.h"

class Player : public GameNode
{
private:;
	   GImage* _f22;
	   Animation* _anim;

	   POINT _plPos;
	   RECT _plRect;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Player() {}
	~Player() {}
};

