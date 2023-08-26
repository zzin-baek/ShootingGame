#include "Stdafx.h"
#include "EnemyManager.h"
#include "Player.h"

// cpp�� ������ �ϰ� �Ѿ��. ����? �ش�Ǵ� ��� ���Ϸ�
// �ش��ϴ� ��� ���Ϸ� �Ѿ�� ���� ������ϰ� cpp�� �����Ѵ�.
// �����ϳ� �����ϰ� �Ѿ���� ���� -> ���簡 �Ͼ�� ������ .h�� �ø��� x

HRESULT EnemyManager::init(void)
{
    IMAGEMANAGER->addFrameImage("AirMonster", "Resources/Image/Enemy/air_Monster3.bmp",
        0.0f, 0.0f, 512, 32, 16, 1, true, RGB(255, 0, 255));

    IMAGEMANAGER->addFrameImage("BasicBullet", "Resources/Image/Enemy/MBasic_Bullet.bmp",
        64, 10, 8, 1, true, RGB(255, 0, 255));

    _setTime = RND->getFromFloatTo(50, 120);
    _worldTime = GetTickCount();

    setMinion();
    _bullet = new Bullet;
    _bullet->init("BasicBullet", 200);

    return S_OK;
}

void EnemyManager::release(void)
{
    for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
    {
        (*_viMonster)->release();
        SAFE_DELETE(*_viMonster);
    }
}

void EnemyManager::update(void)
{
    for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
    {
        (*_viMonster)->update();
    }

    minionBulletFire();
    _bullet->update();
    collision();
}

void EnemyManager::render(void)
{
    for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
    {
        (*_viMonster)->render();
    }
    _bullet->render();
}

void EnemyManager::setMinion()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            Enemy* air;
            air = new AirMonster;
            air->init("AirMonster", 0, (float)(250 + j * 200), (float)(250 + i * 100));
            air->setInfo({ 0, { (float)250 + j * 200, (float)250 + i * 100 } });
            
            _vMonster.push_back(air);
        }
    }
}

void EnemyManager::removeMinion(int arrNum)
{
    SAFE_DELETE(_vMonster[arrNum]);
    _vMonster.erase(_vMonster.begin() + arrNum);
}

void EnemyManager::minionBulletFire(void)
{
    for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
    {
        if ((*_viMonster)->bulletCountFire())
        {
            RECT rc = (*_viMonster)->getRect();

            _bullet->fire(rc.left + (rc.left - rc.right) / 2,
                rc.bottom + (rc.bottom - rc.top) / 2 + 30,
                MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2,
                    rc.bottom + (rc.top - rc.bottom) / 2, _player->getPosition().x,
                    _player ->getPosition().y), RND->getFromFloatTo(2.0f, 4.0f));
        }
    }
}

void EnemyManager::collision(void)
{
    for (int i = 0; i < _bullet->getBullet().size(); i++)
    {
        RECT rc;

        if (IntersectRect(&rc, &_bullet->getBullet()[i].rc, &_player->getRect()))
        {
            _bullet->removeBullet(i);
        }

    }
}

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}