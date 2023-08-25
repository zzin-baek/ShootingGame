#include "Stdafx.h"
#include "EnemyManager.h"

// cpp는 참조를 하고 넘어간다. 어디로? 해당되는 헤더 파일로
// 해당하는 헤더 파일로 넘어가는 순간 헤더파일과 cpp를 복사한다.
// 참조하냐 참조하고 넘어가냐의 차이 -> 복사가 일어나기 때문에 .h에 올리면 x

HRESULT EnemyManager::init(void)
{
    IMAGEMANAGER->addFrameImage("해파리", "Resources/Images/Object/JellyFish.bmp",
        0.0f, 0.0f, 1140, 47, 19, 1, true, RGB(255, 0, 255));

    IMAGEMANAGER->addImage("적 미사일", "Resources/Images/Object/Bullet.bmp",
        7 * 2, 7 * 2, true, RGB(255, 0, 255));

    _setTime = RND->getFromFloatTo(50, 120);
    _worldTime = GetTickCount();

    setMinion();
    _bullet = new Bullet;
    _bullet->init("적 미사일", 20);

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
            jellyFish->init("해파리", 0, (float)(250 + j * 200), (float)(250 + i * 100));
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