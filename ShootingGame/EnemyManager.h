#pragma once
#include "GameNode.h"
#include "Enemy.h"
#include "AirMonster.h"
#include "FallMonster.h"
#include "Bullets.h"
#include "Boss.h"

class Player;

enum eMonster
{
	AIR,
	FALL,
};

class EnemyManager : public GameNode
{
private:
	typedef vector<Enemy*> vEnemy;
	typedef vector<Enemy*>::iterator viEnemy;

	float _setTime, _worldTime;

private:
	vEnemy _vMonster, _vFallMonster;
	viEnemy _viMonster, _viFallMonster;

	Player* _player;
	Bullet* _bullet;
	Bullet_air* _bulletAir;
	Bullet_fall* _bulletFall;
	Bullet_spin* _bulletSpin;

	int _cnt;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setMinion();
	void removeMinion(int monster, int arrNum);

	void enemyBulletFire(void);
	void collision(void);

	vector<Enemy*> getMinions(void) { return _vMonster; }
	vector<Enemy*> getFallMonster(void) { return _vFallMonster; }

	Bullet* getBullet(void) { return _bullet; }
	void setRocketMemoryAddress(Player* pl) { _player = pl; }

	EnemyManager();
	~EnemyManager();
};