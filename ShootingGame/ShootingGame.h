#pragma once
#include "GameNode.h"
#include "Player.h"
#include "EnemyManager.h"

class ShootingGame : public GameNode
{
private:
	GImage* _bg;
	Player* _f22;
	EnemyManager* _em;

	POINTF _bgSpeed;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	ShootingGame() {}
	~ShootingGame() {}
};

