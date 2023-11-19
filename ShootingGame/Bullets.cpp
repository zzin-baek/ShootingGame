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
    (_vBullet.begin() + arrNum)->fire = false;
}

HRESULT Bullet_air::init(const char* imageName, int bulletMax, float range)
{
    _imageName = imageName;
    _range = range;
    _bulletMax = bulletMax;

    return S_OK;
}

void Bullet_air::release(void)
{
    _vBullet.clear();
}

void Bullet_air::update(void)
{
    move();
}

void Bullet_air::render(void)
{
    draw();
}

void Bullet_air::fire(float x, float y, float angle, float speed)
{
    if (_bulletMax <= _vBullet.size()) return;


    tagBullet bullet;
    ZeroMemory(&bullet, sizeof(tagBullet));

    bullet.img = IMAGEMANAGER->findImage(_imageName);
    bullet.speed = speed;
    bullet.angle = angle;

    bullet.x = bullet.fireX = x;
    bullet.y = bullet.fireY = y;
    bullet.rc = RectMakeCenter(bullet.x, bullet.y,
        bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

    _vBullet.push_back(bullet);
}

void Bullet_air::draw(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        _viBullet->img->frameRender(getMemDC(), _viBullet->rc.left - _viBullet->img->getFrameWidth() / 2,
            _viBullet->rc.top - _viBullet->img->getFrameHeight() / 2,
            _viBullet->img->getFrameWidth() * 2, _viBullet->img->getFrameHeight() * 2,
            _viBullet->img->getFrameX(), _viBullet->img->getFrameY());
    }
}

void Bullet_air::move(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
    {
        _viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
        _viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

        _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
            _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

        _viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
        if (_viBullet->img->getFrameX() > 7)
            _viBullet->img->setFrameX(0);

        if (MY_UTIL::getDistance(_viBullet->fireX, _viBullet->fireY,
            _viBullet->x, _viBullet->y) > _range)
        {
            // SAFE_DELETE(_viBullet->img);
            _viBullet = _vBullet.erase(_viBullet);
        }
        else
        {
            ++_viBullet;
        }

    }
}

void Bullet_air::removeBullet(int arrNum)
{
    _vBullet.erase(_vBullet.begin() + arrNum);
}

/// ///////////////////

HRESULT Bullet_fall::init(const char* imageName, int bulletMax, float range)
{
    _imageName = imageName;
    _range = range;
    _bulletMax = bulletMax;

    return S_OK;
}

void Bullet_fall::release(void)
{
    _vBullet.clear();
}

void Bullet_fall::update(void)
{
    move();
}

void Bullet_fall::render(void)
{
    draw();
}

void Bullet_fall::fire(float x, float y, float angle, float speed)
{
    if (_bulletMax <= _vBullet.size()) return;

    for (int i = 0; i < 18; i++)
    {
        tagBullet bullet;
        ZeroMemory(&bullet, sizeof(tagBullet));

        bullet.img = IMAGEMANAGER->findImage(_imageName);
        bullet.speed = speed;
        bullet.angle = 20 * i;

        bullet.x = bullet.fireX = x;
        bullet.y = bullet.fireY = y;
        bullet.rc = RectMakeCenter(bullet.x, bullet.y,
            bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

        _vBullet.push_back(bullet);
    }
}

void Bullet_fall::draw(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        _viBullet->img->frameRender(getMemDC(), _viBullet->rc.left - _viBullet->img->getFrameWidth() / 2,
            _viBullet->rc.top - _viBullet->img->getFrameHeight() / 2,
            _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight(),
            _viBullet->img->getFrameX(), _viBullet->img->getFrameY());
    }
}

void Bullet_fall::move(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
    {
        _viBullet->x += cosf(_viBullet->angle * PI / 180) * _viBullet->speed;
        _viBullet->y += -sinf(_viBullet->angle * PI / 180) * _viBullet->speed;

        _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
            _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

        _viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
        if (_viBullet->img->getFrameX() > 7)
            _viBullet->img->setFrameX(0);

        if (MY_UTIL::getDistance(_viBullet->fireX, _viBullet->fireY,
            _viBullet->x, _viBullet->y) > _range)
        {
            // SAFE_DELETE(_viBullet->img);
            _viBullet = _vBullet.erase(_viBullet);
        }
        else
        {
            ++_viBullet;
        }

    }
}

void Bullet_fall::removeBullet(int arrNum)
{
    _vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT Bullet_spin::init(const char* imageName, int bulletMax, float range)
{
    _imageName = imageName;
    _range = range;
    _bulletMax = bulletMax;

    return S_OK;
}

void Bullet_spin::release(void)
{
    _vBullet.clear();
}

void Bullet_spin::update(void)
{
    move();
}

void Bullet_spin::render(void)
{
    draw();
}

void Bullet_spin::fire(float x, float y, float angle, float speed)
{
    tagBullet bullet;
    ZeroMemory(&bullet, sizeof(tagBullet));

    bullet.img = IMAGEMANAGER->findImage(_imageName);
    bullet.speed = speed;
    bullet.angle = angle;

    bullet.x = bullet.fireX = x;
    bullet.y = bullet.fireY = y;
    bullet.rc = RectMakeCenter(bullet.x, bullet.y,
        bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

    _vBullet.push_back(bullet);
}

void Bullet_spin::draw(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        _viBullet->img->frameRender(getMemDC(), _viBullet->rc.left - _viBullet->img->getFrameWidth() / 2,
            _viBullet->rc.top - _viBullet->img->getFrameHeight() / 2,
            _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight(),
            _viBullet->img->getFrameX(), _viBullet->img->getFrameY());
    }
}

void Bullet_spin::move(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
    {
        _viBullet->x += cosf(_viBullet->angle * PI / 180) * _viBullet->speed;
        _viBullet->y += -sinf(_viBullet->angle * PI / 180) * _viBullet->speed;

        _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
            _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

        _viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
        if (_viBullet->img->getFrameX() > 7)
            _viBullet->img->setFrameX(0);

        if (MY_UTIL::getDistance(_viBullet->fireX, _viBullet->fireY,
            _viBullet->x, _viBullet->y) > _range)
        {
            // SAFE_DELETE(_viBullet->img);
            _viBullet = _vBullet.erase(_viBullet);
        }
        else
        {
            ++_viBullet;
        }
    }
}

void Bullet_spin::removeBullet(int arrNum)
{
    _vBullet.erase(_vBullet.begin() + arrNum);
}
