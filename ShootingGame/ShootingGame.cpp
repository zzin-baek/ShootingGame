#include "Stdafx.h"
#include "ShootingGame.h"

HRESULT ShootingGame::init(void)
{
    _bg = IMAGEMANAGER->addImage("bg", "Resources/Image/BackGround/Stage1.bmp", WINSIZE_X, 18164);
    _bgSpeed = { 0.0f, 0.0f };

    _f22 = new Player;
    _f22->init();

    _em = new EnemyManager;
    _em->init();

    _f22->setEnemyManagerMemoryAddress(_em);
    _em->setRocketMemoryAddress(_f22);

    _once = false;
    return S_OK;
}

void ShootingGame::release(void)
{
    SAFE_DELETE(_bg);
    SAFE_DELETE(_f22);
    SAFE_DELETE(_em);
    for (_viBoss = _vBoss.begin(); _viBoss != _vBoss.end(); ++_viBoss)
    {
        (*_viBoss)->release();
    }
}

void ShootingGame::update(void)
{
    _bgSpeed.y -= 2.5f;

    if (TIMEMANAGER->getWolrdTime() > 35.0f && _vBoss.empty())
    {
        Boss* boss = new Boss;
        boss->init();
        boss->init("Boss", WINSIZE_X / 2, -100);

        _f22->setBossMemoryAddress(boss);
        boss->setRocketMemoryAddress(_f22);

        _vBoss.push_back(boss);
    }

    for (_viBoss = _vBoss.begin(); _viBoss != _vBoss.end();++_viBoss)
    {
        (*_viBoss)->update();
    }

    _f22->update();
    _em->update();
}

void ShootingGame::render(void)
{
    RECT _rc = { 0, 0, WINSIZE_X, WINSIZE_Y };
    _bg->loopRender(getMemDC(),&_rc, _bgSpeed.x, _bgSpeed.y);
    _em->render();
    for (_viBoss = _vBoss.begin(); _viBoss != _vBoss.end(); ++_viBoss)
    {
        (*_viBoss)->render();
    }
    _f22->render();
}
