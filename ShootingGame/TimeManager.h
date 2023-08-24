#pragma once
#include "SingletonBase.h"
#include "Timer.h"

class TimeManager : public SingletonBase <TimeManager>
{
private:
	Timer* _timer;

public:
	HRESULT init(void);
	void release(void);
	void update(float lock = 0.0f);
	void render(HDC hdc);

	inline float getWolrdTime(void) const { return _timer->getWorldTime(); }
	inline float getElpasedTime(void) const { return _timer->getElapsedTime(); }


	TimeManager() {}
	~TimeManager() {}
};

