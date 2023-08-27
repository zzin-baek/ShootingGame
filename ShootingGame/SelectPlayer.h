#pragma once
#include "GameNode.h"

class SelectPlayer : public GameNode
{
private:
	int _select;
	bool _next;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	bool getNext() { return _next; }

	SelectPlayer() {}
	~SelectPlayer() {}
};

