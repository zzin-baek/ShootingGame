#include "Stdafx.h"
#include "EnemyManager.h"
#include "Player.h"

HRESULT EnemyManager::init(void)
{
    IMAGEMANAGER->addFrameImage("AirMonster", "Resources/Image/Enemy/air_Monster3.bmp",
        0.0f, 0.0f, 512, 32, 16, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("FallMonster", "Resources/Image/Enemy/Monster_4.bmp",
        240, 60, 2, 1, true, RGB(255, 0, 255));

    IMAGEMANAGER->addFrameImage("BasicBullet", "Resources/Image/Enemy/MBasic_Bullet.bmp",
        64, 10, 8, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("BasicBullet2", "Resources/Image/Enemy/enemyBullets2.bmp",
        120, 20, 9, 1, true, RGB(255, 0, 255));

    _setTime = RND->getFromFloatTo(50, 120);
    _worldTime = TIMEMANAGER->getWolrdTime();

    _bullet = new Bullet;
    _bullet->init("BasicBullet", 200);

    _bulletAir = new Bullet_air;
    _bulletAir->init("BasicBullet", 100, WINSIZE_Y);

    _bulletFall = new Bullet_fall;
    _bulletFall->init("BasicBullet2", 100, WINSIZE_Y);

    _cnt = 0;
    return S_OK;
}

void EnemyManager::release(void)
{
    for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
    {
        (*_viMonster)->release();
        SAFE_DELETE(*_viMonster);
    }
    for (_viFallMonster = _vFallMonster.begin(); _viFallMonster != _vFallMonster.end(); ++_viFallMonster)
    {
        (*_viFallMonster)->release();
        SAFE_DELETE(*_viFallMonster);
    }
}

void EnemyManager::update(void)
{
    for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
    {
        (*_viMonster)->update();
    }

    for (_viFallMonster = _vFallMonster.begin(); _viFallMonster != _vFallMonster.end(); ++_viFallMonster)
    {
        (*_viFallMonster)->update();
    }
    _cnt++;
    setMinion();

    if (_cnt % 20 == 0)
        enemyBulletFire();
    _bulletAir->update();
    _bulletFall->update();
    collision();
}

void EnemyManager::render(void)
{
    _bulletAir->render();
    _bulletFall->render();
    
    for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
    {
        (*_viMonster)->render();
    }

    for (_viFallMonster = _vFallMonster.begin(); _viFallMonster != _vFallMonster.end(); ++_viFallMonster)
    {
        (*_viFallMonster)->render();
    }
}

void EnemyManager::setMinion()
{
    if (TIMEMANAGER->getWolrdTime() > 24.0f && _vMonster.empty())
    {
        for (int i = 0; i < 5; i++)
        {
            Enemy* air;
            air = new AirMonster;
            air->init("AirMonster", 1, (float)(100 + i * 100), (float)(200));
            air->setInfo({ 180, { (float)100 + i * 100, (float)200 } });

            _vMonster.push_back(air);
        }
    }

    if (TIMEMANAGER->getWolrdTime() > 28.0f && _vFallMonster.empty())
    {
        for (int i = 0; i < 2; i++)
        {
            Enemy* fall;
            fall = new FallMonster;
            fall->init("FallMonster", 0, 120 + 300 * i, -100);
            fall->setInfo({ 0, (float)120 + 300 * i, -100 });

            _vFallMonster.push_back(fall);
        }
    }
}

void EnemyManager::removeMinion(int monster, int arrNum)
{
    switch (monster)
    {
    case AIR:
        SAFE_DELETE(_vMonster[arrNum]);
        _vMonster.erase(_vMonster.begin() + arrNum);
        break;

    case FALL:
        SAFE_DELETE(_vFallMonster[arrNum]);
        _vFallMonster.erase(_vFallMonster.begin() + arrNum);
        break;
    }
}

void EnemyManager::enemyBulletFire(void)
{
    for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
    {
        if ((*_viMonster)->bulletCountFire())
        {
            RECT rc = (*_viMonster)->getRect();

            _bulletAir->fire(rc.left + (rc.left - rc.right) / 2,
                rc.bottom + (rc.bottom - rc.top) / 2,
                MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2,
                    rc.bottom + (rc.top - rc.bottom) / 2, _player->getPosition().x,
                    _player ->getPosition().y), RND->getFromFloatTo(3.0f, 4.0f));
        }
    }

    for (_viFallMonster = _vFallMonster.begin(); _viFallMonster != _vFallMonster.end(); ++_viFallMonster)
    {
        RECT rc = (*_viFallMonster)->location();

        _bulletFall->fire((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2, 0, 3);
    }
}

void EnemyManager::collision(void)
{
    for (int i = 0; i < _bulletAir->getBullet().size(); i++)
    {
        RECT rc;

        if (IntersectRect(&rc, &_bulletAir->getBullet()[i].rc, 
            &CollisionAreaResizing(_player->getRect(), 40, 60)))
        {
            _bulletAir->removeBullet(i);
            _player->hitDamage(5.0f);
        }

    }
    for (int i = 0; i < _bulletFall->getBullet().size(); i++)
    {
        RECT rc;

        if (IntersectRect(&rc, &_bulletFall->getBullet()[i].rc,
            &CollisionAreaResizing(_player->getRect(), 40, 60)))
        {
            _bulletFall->removeBullet(i);
            _player->hitDamage(5.0f);
        }

    }
}

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}