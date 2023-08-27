#include "Stdafx.h"
#include "FallMonster.h"

void FallMonster::release(void)
{
}

void FallMonster::update(void)
{
    move();
}

void FallMonster::render(void)
{
    draw();
    animation();
}

void FallMonster::setInfo(tagEnemy enemy)
{
    _sEnemy = enemy;
}

void FallMonster::move(void)
{
    if (_sEnemy.center.y < 200)
    {
        _sEnemy.center.y += 1;

        _rc = RectMakeCenter(_sEnemy.center.x, _sEnemy.center.y, 
            _image->getFrameWidth(), _image->getFrameHeight());

        _x = (_rc.left + _rc.right) / 2;
        _y = (_rc.top + _rc.bottom) / 2;
    }
}

RECT FallMonster::location(void)
{
    return _rc;
}

void FallMonster::draw(void)
{
    _image->frameRender(getMemDC(), _rc.left - _image->getFrameWidth() / 2,
        _rc.top - _image->getFrameHeight() / 2,
        _image->getFrameWidth() * 2, _image->getFrameHeight() * 2,
        _currentFrameX, _currentFrameY);
}

void FallMonster::animation(void)
{
    if (0.1 + _fallMonsterCount <= TIMEMANAGER->getWolrdTime())
    {
        _fallMonsterCount = TIMEMANAGER->getWolrdTime();
        _currentFrameX++;

        if (_image->getMaxFrameX() < _currentFrameX)
        {
            _currentFrameX = 0;
        }
    }
}