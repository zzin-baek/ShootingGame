#pragma once
#include "GameNode.h"

class StartScene : public GameNode
{
private:
	GImage* _startScene;
	GImage* _startButton;

	int _flikering;
	bool _next;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	bool getNext() { return _next; }

	StartScene() {}
	~StartScene() {}
};

