#include "Stdafx.h"
#include "AirMonster.h"

void AirMonster::release(void)
{
}

void AirMonster::update(void)
{
}

void AirMonster::render(void)
{
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
    }
}

RECT AirMonster::location(void)
{
	return RECT();
}

void AirMonster::draw(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top,
		_currentFrameX, _currentFrameY);
}

void AirMonster::animation(void)
{
    if (_rndTimeCount + _worldTimeCount <= GetTickCount())
    {
        _worldTimeCount = GetTickCount();
        _currentFrameX++;

        if (_image->getMaxFrameX() < _currentFrameX)
        {
            _currentFrameX = 0;
        }
    }
}
