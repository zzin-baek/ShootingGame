#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

	_sg = new ShootingGame;
	_sg->init();

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

	_sg->release();
	SAFE_DELETE(_sg);
}

void MainGame::update(void)
{
	GameNode::update();
	_sg->update();
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	_sg->render();

	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC());
}
