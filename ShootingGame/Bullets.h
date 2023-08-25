#pragma once
#include "GameNode.h"

struct tagBullet
{
	GImage* img;
	RECT rc;
	int radius;
	int count;
	float x, y;
	float fireX, fireY;
	float angle;
	float speed;
	bool fire;
};

class Bullet : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	int _bulletMax;
	float _bulletTick;

public:
	HRESULT init(const char* imageName, int bulletMax);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed);
	void draw(void);
	void move(void);

	void removeBullet(int arrNum);
	vector<tagBullet> getBullet(void) { return _vBullet; }

	Bullet(void) {}
	virtual ~Bullet(void) {}
};

