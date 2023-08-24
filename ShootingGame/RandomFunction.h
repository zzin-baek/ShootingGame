#pragma once
#include "SingletonBase.h"

class RandomFunction : public SingletonBase <RandomFunction>
{
public:
	RandomFunction()
	{
		srand(GetTickCount());
	}
	~RandomFunction() {}

	HRESULT init(void) { return S_OK; }

	inline int getInt(int num)
	{
		return rand() % num;
	}

	// 0을 조심하자
	inline int getFromIntTo(int fromNum, int toNum)
	{
		// if <- 복잡해지면 inline이 풀릴 수 있음
		return rand() % (toNum - fromNum + 1) + fromNum;
	}

	float getFloat(void)
	{
		return (float)rand() / (float)RAND_MAX;
	}

	float getFloat(float num)
	{
		return (float)rand() / (float)RAND_MAX * num;
	}

	float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (toNum - fromNum) + fromNum);
	}
};