#include "Stdafx.h"
#include "Boss.h"
#include "Player.h"

HRESULT Boss::init(void)
{
    _image = IMAGEMANAGER->addFrameImage("Boss", "Resources/Image/Enemy/boss.bmp",
        6696, 186, 36, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("Boss_bullet", "Resources/Image/Enemy/boss_bullet.bmp",
        585, 45, 13, 1, true, RGB(255, 0, 255));

    _bulletAngle = _bossMonster = 0.0f;
    _patternTime = _delay = 0.0f;
    _hp = 200;
    _rc = RectMakeCenter(0, 0, 10, 10);

    _effect = new Effect;
    _effect->init();

    _bulletSpin = new Bullet_spin;
    _bulletSpin->init("Boss_bullet", 200, WINSIZE_Y);

    _bulletFall = new Bullet_fall;
    _bulletFall->init("Boss_bullet", 200, WINSIZE_Y);

    return S_OK;
}

HRESULT Boss::init(const char* imageName, float x, float y)
{
    _x = x;
    _y = y;

    _rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

    return S_OK;
}

void Boss::release(void)
{
    SAFE_DELETE(_image);
    SAFE_DELETE(_bulletSpin);
}

void Boss::update(void)
{
    move();
    _effect->update();
    if (KEYMANAGER->isOnceKeyDown('Q'))
    {
        _hp = 0;
        _effect->fire("Exp2", RND->getFromIntTo(_rc.left, _rc.right),
            RND->getFromIntTo(_rc.top, _rc.bottom));
        _effect->fire("Exp2", RND->getFromIntTo(_rc.left, _rc.right),
            RND->getFromIntTo(_rc.top, _rc.bottom));
        _effect->fire("Exp2", RND->getFromIntTo(_rc.left, _rc.right),
            RND->getFromIntTo(_rc.top, _rc.bottom));
        _effect->fire("Exp2", RND->getFromIntTo(_rc.left, _rc.right),
            RND->getFromIntTo(_rc.top, _rc.bottom));
        _effect->fire("Exp2", RND->getFromIntTo(_rc.left, _rc.right),
            RND->getFromIntTo(_rc.top, _rc.bottom));
        _effect->fire("Exp2", RND->getFromIntTo(_rc.left, _rc.right),
            RND->getFromIntTo(_rc.top, _rc.bottom));

    }
    Pattern();
    _bulletSpin->update();
    _bulletAngle += 3.0f;
}

void Boss::render(void)
{
    if (_hp > 0)
    {
        draw();
        animation();
        _bulletSpin->render();
    }
    _effect->render();
}

void Boss::move(void)
{
    if (_y < 200)
        _y += 3.0f;

    _rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void Boss::draw(void)
{
    _image->frameRender(getMemDC(), _rc.left - _image->getFrameWidth() / 2,
        _rc.top - _image->getFrameHeight() / 2,
        _image->getFrameWidth() * 2, _image->getFrameHeight() * 2,
        _currentFrameX, _currentFrameY);
}

void Boss::animation(void)
{
    if (0.01 + _bossMonster <= TIMEMANAGER->getWolrdTime())
    {
        _bossMonster = TIMEMANAGER->getWolrdTime();
        _currentFrameX++;

        if (_image->getMaxFrameX() < _currentFrameX)
        {
            _currentFrameX = 0;
        }
    }
}

void Boss::Pattern(void)
{
    if (3.0 + _patternTime <= TIMEMANAGER->getWolrdTime())
    {
        _patternTime = TIMEMANAGER->getWolrdTime();
        _pattern = RND->getFromIntTo(0, 2);
    }
    switch (_pattern)
    {
    case 0:
        if (0.05 + _delay <= TIMEMANAGER->getWolrdTime())
        {
            _delay = TIMEMANAGER->getWolrdTime();
            _bulletSpin->fire((_rc.left + _rc.right) / 2,
                (_rc.bottom + _rc.top) / 2, _bulletAngle, 3.0f);
        }
        break;

    case 1:
        if (0.05 + _delay <= TIMEMANAGER->getWolrdTime())
        {
            _delay = TIMEMANAGER->getWolrdTime();
            _bulletFall->fire((_rc.left + _rc.right) / 2,
                (_rc.bottom + _rc.top) / 2, 0, 3.0f);
        }

        break;

    }
}

void Boss::collision(void)
{
}
