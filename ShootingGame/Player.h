#pragma once
#include "GameNode.h"
#include "Animation.h"
#include "EnemyManager.h"
#include "Bullets.h"
#include "Effect.h"
#include "ProgressBar.h"

class Boss;

class Player : public GameNode
{
private:
	   GImage* _f22;
	   Animation* _anim;
	   Bullet* _bullet;
	   EnemyManager* _em;
	   Effect* _effect;
	   Boss* _boss;

	   ProgressBar* _hpBar;

	   POINT _plPos;
	   RECT _plRect;

	   int _cnt, _score, _scoreCopy;
	   float _currentHp, _maxHp;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void collision(void);
	void setEnemyManagerMemoryAddress(EnemyManager* em) { _em = em; }
	void setBossMemoryAddress(Boss* boss) { _boss = boss; }

	inline void upScore(int score) { _score += score; }
	inline void hitDamage(float damage)
	{
		if (_currentHp <= 0)
		{
			_currentHp = 0;
			return;
		}
		_currentHp -= damage;
	}

	POINT getPosition(void) { return _plPos; }
	RECT getRect(void) { return _plRect; }

	void removeMissile(int arrNum);

	Player() {}
	~Player() {}
};

