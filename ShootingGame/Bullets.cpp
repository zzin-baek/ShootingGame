#include "Stdafx.h"
#include "Bullets.h"

HRESULT Bullet::init(const char* imageName, int bulletMax)
{
    _imageName = imageName;
    _bulletMax = bulletMax;

    for (int i = 0; i < _bulletMax; i++)
    {
        tagBullet bullet;
        ZeroMemory(&bullet, sizeof(tagBullet));

        bullet.img = IMAGEMANAGER->findImage(_imageName);
        bullet.fire = false;

        _vBullet.push_back(bullet);
    }

    return S_OK;
}

void Bullet::release(void)
{
    _vBullet.clear();
}

void Bullet::update(void)
{
    move();
}

void Bullet::render(void)
{
    draw();
}

void Bullet::fire(float x, float y, float angle, float speed)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        if (_viBullet->fire) continue;

        _viBullet->fire = true;
        _viBullet->speed = speed;
        _viBullet->x = _viBullet->fireX = x;
        _viBullet->y = _viBullet->fireY = y;

        _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
            _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

        break;
    }
}

void Bullet::draw(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        if (!_viBullet->fire) continue;

        _viBullet->img->frameRender(getMemDC(), _viBullet->rc.left - _viBullet->img->getFrameWidth() / 2, 
            _viBullet->rc.top - _viBullet->img->getFrameHeight() / 2,
            _viBullet->img->getFrameWidth() * 2, _viBullet->img->getFrameHeight() * 2,
            _viBullet->img->getFrameX(), _viBullet->img->getFrameY());
    }
}

void Bullet::move(void)
{

    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        if (!_viBullet->fire) continue;

        _viBullet->count++;
        _viBullet->y -= _viBullet->speed;

        _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
            _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

        if (_viBullet->y < 0)
        {
            _viBullet->fire = false;
        }

        if (_viBullet->count % 2 == 0)
        {
            if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
            {
                _viBullet->img->setFrameX(0);
            }
            _viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);

        }
    }
}

void Bullet::removeBullet(int arrNum)
{
}
