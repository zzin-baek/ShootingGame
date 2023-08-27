#pragma once
#include "GameNode.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Boss.h"

class ShootingGame : public GameNode
{
private:
	GImage* _bg;
	Player* _f22;
	EnemyManager* _em;

	vector<Boss*> _vBoss;
	vector<Boss*>::iterator _viBoss;

	POINTF _bgSpeed;
	bool _once;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	ShootingGame() {}
	~ShootingGame() {}
};

