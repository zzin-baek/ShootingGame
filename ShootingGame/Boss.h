#pragma once
#include "GameNode.h"
#include "Bullets.h"
#include "Effect.h"

class Player;

class Boss : public GameNode
{
private:
	GImage* _image;
	Player* _player;
	Bullet_spin* _bulletSpin;
	Bullet_fall* _bulletFall;
	Effect* _effect;

	float _x, _y;
	RECT _rc;
	int _pattern, _currentFrameX, _currentFrameY;
	float _bulletAngle, _bossMonster, _patternTime, _delay;
	float _hp;

public:
	HRESULT init(void);
	HRESULT init(const char* imageName, float x, float y);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);
	void animation(void);
	void Pattern(void);
	void hitDamage(float hp) { _hp -= hp; }
	float getHp() { return _hp; }

	void collision(void);
	void setRocketMemoryAddress(Player* pl) { _player = pl; }

	RECT getRect() { return _rc; }

	Boss() {}
	~Boss() {}
};