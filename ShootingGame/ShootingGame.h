#pragma once
#include "GameNode.h"
#include "Player.h"

struct POINTF
{
	float x, y;
};

class ShootingGame : public GameNode
{
private:
	GImage* _bg;
	Player* _f22;

	POINTF _bgSpeed;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	ShootingGame() {}
	~ShootingGame() {}
};

