#pragma once
#include "GameNode.h"

struct tagEffect
{
	GImage* img;
	RECT rc;
	POINT idx;
	float x, y;
	int count;
	bool fire = false;
};

class Effect : public GameNode
{
private:
	vector<tagEffect> _vEffect;
	vector<tagEffect>::iterator _viEffect;

	float _effectTick;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void fire(const char* fileName, float x, float y);
	void draw(void);
	void animation(void);

	Effect() {}
	~Effect() {}
};

