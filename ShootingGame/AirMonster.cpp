#include "Stdafx.h"
#include "AirMonster.h"

void AirMonster::release(void)
{
}

void AirMonster::update(void)
{
    move();
}

void AirMonster::render(void)
{
    draw();
    animation();
}

void AirMonster::setInfo(tagEnemy enemy)
{
    _sEnemy = enemy;
}

void AirMonster::move(void)
{
    int dir;
    float angle, centerX, centerY;

    switch (_patternNum)
    {
    case 0:
        dir = RND->getInt(4);

        if (dir == 0)
        {
            _rc.left += 2;
            _rc.right += 2;
            _x += 2;
        }
        else if (dir == 1)
        {
            _rc.left -= 2;
            _rc.right -= 2;
            _x -= 2;
        }
        else if (dir == 2)
        {
            _rc.top += 2;
            _rc.bottom += 2;
            _y += 2;
        }
        else
        {
            _rc.top -= 2;
            _rc.bottom -= 2;
            _y -= 2;
        }

        break;
    case 1:
        if (0.006 + _enemyTime <= TIMEMANAGER->getWolrdTime())
        {
            _enemyTime = TIMEMANAGER->getWolrdTime();
            _sEnemy.angle -= 3;
            _sEnemy.center.x += 5 * cosf(_sEnemy.angle * PI / 180);
            _sEnemy.center.y -= 5 * sinf(_sEnemy.angle * PI / 180);
        }
        _rc = RectMakeCenter(_sEnemy.center.x, _sEnemy.center.y, _image->getFrameWidth(), _image->getFrameHeight());

        _x = (_rc.left + _rc.right) / 2;
        _y = (_rc.top + _rc.bottom) / 2;

        break;
    }
}

RECT AirMonster::location(void)
{
	return RECT();
}

void AirMonster::draw(void)
{
	_image->frameRender(getMemDC(), _rc.left - _image->getFrameWidth() / 2, 
        _rc.top - _image->getFrameHeight() / 2, 
        _image->getFrameWidth() * 2, _image->getFrameHeight() * 2,
		_currentFrameX, _currentFrameY);
}

void AirMonster::animation(void)
{
    if (0.12 + _airMonsterCount <= TIMEMANAGER->getWolrdTime())
    {
        _airMonsterCount = TIMEMANAGER->getWolrdTime();
        _currentFrameX++;

        if (_image->getMaxFrameX() < _currentFrameX)
        {
            _currentFrameX = 0;
        }
    }
}

AirMonster::AirMonster() : _enemyTime(0.0f),
                           _airMonsterCount(0.0f)
{
}
