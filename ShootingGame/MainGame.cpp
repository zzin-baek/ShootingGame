#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

	_sc = new StartScene;
	_sc->init();


	_sp = new SelectPlayer;
	_sp->init();

	_sg = new ShootingGame;
	_sg->init();
	SOUNDMANAGER->CheckAndReplayWithKey("Loading");

	_current = _sc;

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

	_sg->release();
	SAFE_DELETE(_sg);
	_sc->release();
	SAFE_DELETE(_sc);
}

void MainGame::update(void)
{
	GameNode::update();
	
	if (_sc->getNext())
	{
		_current = _sp;
	}
	if (_sp->getNext())
	{
		SOUNDMANAGER->stopMp3WithKey("Loading");
		SOUNDMANAGER->CheckAndReplayWithKey("Stage1");
		_current = _sg;
	}

	_current->update();
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	_current->render();

	//TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC());
}
