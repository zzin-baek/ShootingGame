#pragma once
#include "GameNode.h"
#include "ShootingGame.h"

class MainGame : public GameNode
{
private:
	ShootingGame* _sg;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainGame() {}
	~MainGame() {}
};

