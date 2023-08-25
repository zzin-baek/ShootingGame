#include "Stdafx.h"
#include "EnemyManager.h"

// cpp�� ������ �ϰ� �Ѿ��. ����? �ش�Ǵ� ��� ���Ϸ�
// �ش��ϴ� ��� ���Ϸ� �Ѿ�� ���� ������ϰ� cpp�� �����Ѵ�.
// �����ϳ� �����ϰ� �Ѿ���� ���� -> ���簡 �Ͼ�� ������ .h�� �ø��� x

HRESULT EnemyManager::init(void)
{
    IMAGEMANAGER->addFrameImage("���ĸ�", "Resources/Images/Object/JellyFish.bmp",
        0.0f, 0.0f, 1140, 47, 19, 1, true, RGB(255, 0, 255));

    IMAGEMANAGER->addImage("�� �̻���", "Resources/Images/Object/Bullet.bmp",
        7 * 2, 7 * 2, true, RGB(255, 0, 255));

    _setTime = RND->getFromFloatTo(50, 120);
    _worldTime = GetTickCount();

    setMinion();
    _bullet = new Bullet;
    _bullet->init("�� �̻���", 20);

    return S_OK;
}

void EnemyManager::release(void)
{
    for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
    {
        (*_viMinion)->release();
        SAFE_DELETE(*_viMinion);
    }
}

void EnemyManager::update(void)
{
    for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
    {
        (*_viMinion)->update();
    }

    minionBulletFire();
    _bullet->update();
    collision();
}

void EnemyManager::render(void)
{
    for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
    {
        (*_viMinion)->render();
    }
    _bullet->render();
}

void EnemyManager::setMinion()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            Enemy01* jellyFish;
            jellyFish = new Minion;
            jellyFish->init("���ĸ�", 0, (float)(250 + j * 200), (float)(250 + i * 100));
            jellyFish->setInfo({ 0, { (float)250 + j * 200, (float)250 + i * 100 } });
            _vMinion.push_back(jellyFish);
        }
    }
}

void EnemyManager::removeMinion(int arrNum)
{
    SAFE_DELETE(_vMinion[arrNum]);
    _vMinion.erase(_vMinion.begin() + arrNum);
}

void EnemyManager::minionBulletFire(void)
{
    for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
    {
        if ((*_viMinion)->bulletCountFire())
        {
            RECT rc = (*_viMinion)->getRect();

            _bullet->fire(rc.left + (rc.left - rc.right) / 2,
                rc.bottom + (rc.bottom - rc.top) / 2 + 30,
                MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2,
                    rc.bottom + (rc.top - rc.bottom) / 2, _rocket->getPosition().x,
                    _rocket->getPosition().y), RND->getFromFloatTo(2.0f, 4.0f));
        }
    }
}

void EnemyManager::collision(void)
{
    for (int i = 0; i < _bullet->getBullet().size(); i++)
    {
        RECT rc;

        if (IntersectRect(&rc, &_bullet->getBullet()[i].rc, &_rocket->getRect()))
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