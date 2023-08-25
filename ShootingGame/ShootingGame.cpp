#include "Stdafx.h"
#include "ShootingGame.h"

HRESULT ShootingGame::init(void)
{
    _bg = IMAGEMANAGER->addImage("bg", "Resources/Image/BackGround/Stage1.bmp", WINSIZE_X, 18164);
    _bgSpeed = { 0.0f, 0.0f };

    _f22 = new Player;
    _f22->init();

    return S_OK;
}

void ShootingGame::release(void)
{
    SAFE_DELETE(_bg);
    SAFE_DELETE(_f22);
}

void ShootingGame::update(void)
{
    _bgSpeed.y -= 1.5f;

    _f22->update();
}

void ShootingGame::render(void)
{
    RECT _rc = { 0, 0, WINSIZE_X, WINSIZE_Y };
    _bg->loopRender(getMemDC(),&_rc, _bgSpeed.x, _bgSpeed.y);
    _f22->render();
}
