#pragma once
#include "GameNode.h"

struct POINTF
{
	float x;
	float y;
};

struct tagEnemy
{
	float angle;
	POINTF center;
};

class Enemy : public GameNode
{
protected:
	GImage* _image;
	tagEnemy _sEnemy;
	RECT _rc;

	int _currentFrameX;
	int _currentFrameY;

	float _x, _y;
	int _patternNum, _hp;

	float _rndTimeCount;
	float _worldTimeCount;

	float _rndFireCount;
	float _bulletFireCount;

public:
	HRESULT init(void);
	HRESULT init(const char* imageName, int pattern, float x, float y);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void setPattern(int type);
	virtual void setInfo(tagEnemy enemy);
	virtual void move(void);
	virtual RECT location(void);
	virtual void draw(void);
	virtual void animation(void);

	bool bulletCountFire(void);

	RECT getRect(void) { return _rc; }

	Enemy();
	~Enemy() {}
};
