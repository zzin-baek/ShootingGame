#include "Stdafx.h"
#include "Enemy.h"


Enemy::Enemy() : _rc(RectMake(0, 0, 0, 0)),
                 _currentFrameX(0),
                 _currentFrameY(0),
                 _x(0.0f),
                 _y(0.0f),
                 _hp(100),
                 _rndTimeCount(0.0f),
                 _worldTimeCount(0.0f),
                 _rndFireCount(0.0f),
                 _bulletFireCount(0.0f)
{
}

HRESULT Enemy::init(void)
{
    // DO NOTHING!
    return S_OK;
}

HRESULT Enemy::init(const char* imageName, int pattern, float x, float y)
{
    _worldTimeCount = GetTickCount();
    _rndTimeCount = RND->getFromFloatTo(50, 150);
    _patternNum = pattern;

    _x = x;
    _y = y;

    _rndFireCount = RND->getFromFloatTo(4.5f, 5.0f);

    _image = IMAGEMANAGER->findImage(imageName);
    _rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

    return S_OK;
}

void Enemy::release(void)
{
}

void Enemy::update(void)
{
    move();
}

void Enemy::render(void)
{
    draw();
    animation();
}

void Enemy::setInfo(tagEnemy enemy)
{
}

void Enemy::move(void)
{
}

RECT Enemy::location(void)
{
    return RECT();
}

void Enemy::draw(void)
{
    _image->frameRender(getMemDC(), _rc.left, _rc.top,
        _currentFrameX, _currentFrameY);
}

void Enemy::animation(void)
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

bool Enemy::bulletCountFire(void)
{
    if (_rndFireCount + _bulletFireCount <= TIMEMANAGER->getWolrdTime())
    {
        _bulletFireCount = TIMEMANAGER->getWolrdTime();
        _rndFireCount = RND->getFromFloatTo(2.0f, 6.0f);

        return true;
    }
    return false;
}
