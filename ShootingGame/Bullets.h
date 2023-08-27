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

class Bullet_air : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	int _bulletMax;
	float _range;

public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed);
	void draw(void);
	void move(void);

	void removeBullet(int arrNum);
	vector<tagBullet> getBullet(void) { return _vBullet; }

	Bullet_air(void) {}
	~Bullet_air(void) {}
};

class Bullet_fall : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;


	const char* _imageName;
	int _bulletMax;
	float _range;

public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed);
	void draw(void);
	void move(void);

	void removeBullet(int arrNum);
	vector<tagBullet> getBullet(void) { return _vBullet; }

	Bullet_fall(void) {}
	~Bullet_fall(void) {}
};

class Bullet_spin : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;


	const char* _imageName;
	int _bulletMax;
	float _range;

public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed);
	void draw(void);
	void move(void);

	void removeBullet(int arrNum);
	vector<tagBullet> getBullet(void) { return _vBullet; }

	Bullet_spin(void) {}
	~Bullet_spin(void) {}
};