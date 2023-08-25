#include "Stdafx.h"
#include "Bullets.h"

HRESULT Bullet::init(const char* imageName, int bulletMax)
{
    _imageName = imageName;
    _bulletMax = bulletMax;

    return S_OK;
}

void Bullet::release(void)
{
    _vBullet.clear();
}

void Bullet::update(void)
{
}

void Bullet::render(void)
{
}

void Bullet::fire(float x, float y, float angle, float speed)
{
    if (_bulletMax <= _vBullet.size()) return;


    tagBullet bullet;
    ZeroMemory(&bullet, sizeof(tagBullet));

    bullet.img = new GImage;
    bullet.img->init("Resources/Images/Object/missile.bmp", 0.0f, 0.0f,
        208, 32, 13, 1, true, RGB(255, 0, 255));
    bullet.speed = 4.0f;

    bullet.fire = true;
    bullet.x = bullet.fireX = x;
    bullet.y = bullet.fireY = y;

    bullet.rc = RectMakeCenter(bullet.x, bullet.y,
        bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

    _vBullet.push_back(bullet);
}

void Bullet::draw(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        if (!_viBullet->fire) continue;

        _viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top,
            _viBullet->img->getFrameX(), _viBullet->img->getFrameY());
    }
}

void Bullet::move(void)
{

    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        if (!_viBullet->fire)
        _viBullet->count++;
        _viBullet->y -= _viBullet->speed;

        _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
            _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());


        /*if (_viBullet->count % _bulletTick == 0)
        {
            if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
            {
                _viBullet->img->setFrameX(0);
            }
            _viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);

        }*/
    }
}

void Bullet::removeBullet(int arrNum)
{
}
