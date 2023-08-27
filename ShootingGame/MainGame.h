#pragma once
#include "GameNode.h"
#include "StartScene.h"
#include "SelectPlayer.h"
#include "ShootingGame.h"

class MainGame : public GameNode
{
private:
	StartScene* _sc;
	SelectPlayer* _sp;
	ShootingGame* _sg;

	vector<GameNode*> _scene;

	GameNode* _current;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainGame() {}
	~MainGame() {}
};

